#include <stdio.h>
#include <cmath>
#include <cuda.h>

void random_matrix(float* input, int M, int N) {
  for(int i=0; i<M*N; ++i) {
    input[i] = rand() / (float)RAND_MAX;
  }
}

bool compare(float* input1, float* input2, int M, int N) {
  for(int i=0; i<M*N; ++i) {
    if(input1[i]!=input2[i]) {
      printf("i: %d, input1[%d]: %f, input2[%d]: %f\n", i, i, input1[i], i, input2[i]);
      return false;
    }
  }
  return true;
}

void cpu(float* input, float* output, int M, int N){
  for(int m =0; m< M; m++) {
    for(int n =0; n< N; n++) {
      //output[j][i] = input[i][j]
      output[n*N+m] = input[m*N+n];
    }
  }
}

__global__ void gpu_v1(const float* d_input, float* d_output, int M, int N) {
  int m = blockIdx.y * blockDim.y + threadIdx.y;
  int n = blockIdx.x * blockDim.x + threadIdx.x;

  if (m > M || n > N)
    return;

  d_output[n*N+m] = d_input[m*N+n];
}

#define TILE_SIZE 32
__global__ void gpu_v2(const float* d_input, float* d_output, int M, int N) {
  __shared__ float shm[TILE_SIZE][TILE_SIZE];
  int m = blockIdx.y * TILE_SIZE + threadIdx.y;
  int n = blockIdx.x * TILE_SIZE + threadIdx.x;

  if (m > M || n > N)
    return;

  shm[threadIdx.y][threadIdx.x] = d_input[m * N + n];
  __syncthreads();

  //output_block[blockIdx.x][blockIdx.y] = input_block[blockIdx.y][blockIdx.x]
  //output[y][x] = shm[x][y]
  d_output[(blockIdx.x * TILE_SIZE + threadIdx.y) * N + blockIdx.y * TILE_SIZE + threadIdx.x] = shm[threadIdx.x][threadIdx.y];

}

__global__ void gpu_v3(const float* d_input, float* d_output, int M, int N) {
  __shared__ float shm[TILE_SIZE][TILE_SIZE];
  int m = blockIdx.y * TILE_SIZE + threadIdx.y;
  int n = blockIdx.x * TILE_SIZE + threadIdx.x;

  if (m > M || n > N)
    return;

  shm[threadIdx.y][threadIdx.x ^ threadIdx.y] = d_input[m * N + n];
  __syncthreads();

  //output_block[blockIdx.x][blockIdx.y] = input_block[blockIdx.y][blockIdx.x]
  //output[y][x] = shm[x][y]
  d_output[(blockIdx.x * TILE_SIZE + threadIdx.y) * N + blockIdx.y * TILE_SIZE + threadIdx.x] = shm[threadIdx.x][threadIdx.y ^ threadIdx.x];
}





int main() {
  int M = 1024;
  int N = 1024;
  //int M = 4096;
  //int N = 4096;

  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);

  float* h_input = (float*)malloc(sizeof(float) * M * N);
  float* h_output = (float*)malloc(sizeof(float) * M * N);
  float* d2h_output = (float*)malloc(sizeof(float) * M * N);
  random_matrix(h_input, M, N);
  cpu(h_input, h_output, M, N);

  float* d_input;
  float* d_output;
  cudaMalloc((void**)&d_input, sizeof(float) * M * N);
  cudaMalloc((void**)&d_output, sizeof(float) * M * N);
  cudaMemcpy(d_input, h_input, sizeof(float) * M * N, cudaMemcpyHostToDevice);

  //------------------------------v1
  int BLOCK_SIZE = 32;
  dim3 block_size(BLOCK_SIZE, BLOCK_SIZE);
  dim3 grid_size(ceil(M/BLOCK_SIZE), ceil(N/BLOCK_SIZE));

  cudaEventRecord(start, 0);
  gpu_v1<<<grid_size, block_size>>>(d_input, d_output, M, N);
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_output, d_output, sizeof(float) * M * N, cudaMemcpyDeviceToHost);

  bool result = compare(h_output, d2h_output, M, N);
  if (result)
    printf("gpu_v1 compare pass\n");
  else
    printf("gpu_v1 compare not pass, please check\n");

  float elapsed;
  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v1 cost: %f ms\n\n", elapsed);
  //-------------------------------v1



  //-------------------------------v2
  dim3 block_size2(BLOCK_SIZE, BLOCK_SIZE);
  dim3 grid_size2(ceil(M/BLOCK_SIZE), ceil(N/BLOCK_SIZE));
  
  cudaEventRecord(start, 0);
  gpu_v2<<<grid_size2, block_size2>>>(d_input, d_output, M, N);
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_output, d_output, sizeof(float) * M * N, cudaMemcpyDeviceToHost);

  result = compare(h_output, d2h_output, M, N);
  if (result)
    printf("gpu_v2 compare pass\n");
  else
    printf("gpu_v2 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v2 cost: %f ms\n\n", elapsed);
  //-------------------------------v2
  



  //-------------------------------v3
  dim3 block_size3(BLOCK_SIZE, BLOCK_SIZE);
  dim3 grid_size3(ceil(M/BLOCK_SIZE), ceil(N/BLOCK_SIZE));
  
  cudaEventRecord(start, 0);
  gpu_v3<<<grid_size3, block_size3>>>(d_input, d_output, M, N);
  //cudaError_t cudaerr = cudaDeviceSynchronize();
  //if (cudaerr != cudaSuccess)
  //  printf("kernel launch failed with error \"%s\".\n", cudaGetErrorString(cudaerr));
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_output, d_output, sizeof(float) * M * N, cudaMemcpyDeviceToHost);

  result = compare(h_output, d2h_output, M, N);
  if (result)
    printf("gpu_v3 compare pass\n");
  else
    printf("gpu_v3 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v3 cost: %f ms\n\n", elapsed);
  //-------------------------------v3


  free(h_input);
  free(h_output);
  free(d2h_output);
  cudaFree(d_input);
  cudaFree(d_output);

  cudaEventDestroy(start);
  cudaEventDestroy(stop);
  return 0;
}
