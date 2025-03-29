#include <stdio.h>
#include <cmath>
#include <cuda.h>

void random_matrix(float* input, int M) {
  for(int i=0; i<M; ++i) {
    input[i] = rand() / (float)RAND_MAX;
  }
}

bool compare(float* input1, float* input2, int M) {
  for(int i=0; i<M; ++i) {
    if(input1[i]!=input2[i]) {
      printf("i: %d, input1[%d]: %f, input2[%d]: %f\n", i, i, input1[i], i, input2[i]);
      return false;
    }
  }
  return true;
}

void cpu(float* input1, float* input2, float* output, int M){
  for(int m =0; m < M; m++) {
    output[m] = input1[m] + input2[m];
  }
}

__global__ void gpu_v1(const float* d_input1, const float* d_input2, float* d_output, int M) {
  int m = blockIdx.x * blockDim.x + threadIdx.x;

  if (m >= M)
    return;

  d_output[m] = d_input1[m] + d_input2[m];
}

__global__ void gpu_v2(const float* d_input1, const float* d_input2, float* d_output, int M) {
  int m = blockIdx.x * blockDim.x + threadIdx.x;

  if (m >= M)
    return;

  float4 input1 = ((float4*)&d_input1[4 * m])[0];
  float4 input2 = ((float4*)&d_input2[4 * m])[0];
  float4 output = ((float4*)&d_output[4 * m])[0];
  output.x = input1.x + input2.x;
  output.y = input1.y + input2.y;
  output.z = input1.z + input2.z;
  output.w = input1.w + input2.w;
}


int main() {
  int M = 1024;

  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);

  float* h_input1 = (float*)malloc(sizeof(float) * M);
  float* h_input2 = (float*)malloc(sizeof(float) * M);
  float* h_output = (float*)malloc(sizeof(float) * M);
  float* d2h_output = (float*)malloc(sizeof(float) * M);
  random_matrix(h_input1, M);
  random_matrix(h_input2, M);
  cpu(h_input1, h_input2, h_output, M);

  float* d_input1;
  float* d_input2;
  float* d_output;
  cudaMalloc((void**)&d_input1, sizeof(float) * M);
  cudaMalloc((void**)&d_input2, sizeof(float) * M);
  cudaMalloc((void**)&d_output, sizeof(float) * M);
  cudaMemcpy(d_input1, h_input1, sizeof(float) * M, cudaMemcpyHostToDevice);
  cudaMemcpy(d_input2, h_input2, sizeof(float) * M, cudaMemcpyHostToDevice);

  //------------------------------v1
  int BLOCK_SIZE = 32;
  dim3 block_size(BLOCK_SIZE, 1);
  dim3 grid_size(ceil(M/BLOCK_SIZE), 1);

  cudaEventRecord(start, 0);
  gpu_v1<<<grid_size, block_size>>>(d_input1, d_input2, d_output, M);
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_output, d_output, sizeof(float) * M, cudaMemcpyDeviceToHost);

  bool result = compare(h_output, d2h_output, M);
  if (result)
    printf("gpu_v1 compare pass\n");
  else
    printf("gpu_v1 compare not pass, please check\n");

  float elapsed;
  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v1 cost: %f ms\n\n", elapsed);
  //-------------------------------v1



  //-------------------------------v2
  dim3 block_size2(BLOCK_SIZE, 1);
  dim3 grid_size2(ceil(M/4/BLOCK_SIZE), 1);
  
  cudaEventRecord(start, 0);
  gpu_v2<<<grid_size2, block_size2>>>(d_input1, d_input2, d_output, M);
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_output, d_output, sizeof(float) * M, cudaMemcpyDeviceToHost);

  result = compare(h_output, d2h_output, M);
  if (result)
    printf("gpu_v2 compare pass\n");
  else
    printf("gpu_v2 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v2 cost: %f ms\n\n", elapsed);
  //-------------------------------v2
  
  free(h_input1);
  free(h_input2);
  free(h_output);
  free(d2h_output);
  cudaFree(d_input1);
  cudaFree(d_input2);
  cudaFree(d_output);

  cudaEventDestroy(start);
  cudaEventDestroy(stop);
  return 0;
}
