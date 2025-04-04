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

bool compare2(float* input1, float* input2, int M, float atol = 1e-5, float rtol = 1e-5) {
  for(int i=0; i<M; ++i) {
    //if(input1[i]!=input2[i]) {
    if (std::abs(input1[i] - input2[i]) > atol + rtol * std::abs(input2[i])) {
      printf("i: %d, input1[%d]: %f, input2[%d]: %f\n", i, i, input1[i], i, input2[i]);
      return false;
    }
  }
  return true;
}

void cpu(float* input, float* output, int M){
  float sum = 0.0;
  for(int m =0; m < M; m++) {
    sum += input[m];
  }
  output[0] = sum;
}

__global__ void gpu_v1(float* d_input, float* d_output, int M, int N) {//total len, per block len
  int m = blockIdx.x * N + threadIdx.x;

  if (m >= M)
    return;

  for(int i = N/2; i > 0; i/=2) {
    //if(m+1 < M){
    d_input[m] += d_input[m + i];
    //}
    __syncthreads();
  }

  if(threadIdx.x == 0)
    d_output[blockIdx.x] = d_input[m];
}

__global__ void gpu_v2(float* d_input, float* d_output, int M, int N) {//total len, per block len
  int m = blockIdx.x * N + threadIdx.x;

  if (m >= M)
    return;

  //__shared__ float smem[N];
  __shared__ float smem[64];
  smem[threadIdx.x] = d_input[m];
  smem[threadIdx.x + N/2] = d_input[m + N/2];
  __syncthreads();

  for(int i=N/2; i>0; i/=2) {
    smem[threadIdx.x] += smem[threadIdx.x + i];
    __syncthreads();
  }

  if(threadIdx.x == 0)
    d_output[blockIdx.x] = smem[0];
}

__global__ void gpu_v3(float* d_input, float* d_output, int M, int N) {//total len, per block len
  int m = blockIdx.x * N + threadIdx.x;

  if (m >= M)
    return;

  //__shared__ float smem[N];
  __shared__ float smem[64];
  smem[threadIdx.x] = d_input[m];
  smem[threadIdx.x + N/2] = d_input[m + N/2];
  __syncthreads();

  for(int i=N/2; i>0; i/=2) {
    smem[threadIdx.x] += smem[threadIdx.x + i];
    if(i>32)
      __syncthreads();
  }

  if(threadIdx.x == 0)
    d_output[blockIdx.x] = smem[0];
}

__global__ void gpu_v4(float* d_input, float* d_output, int M, int N) {//total len, per block len
  int m = blockIdx.x * N + threadIdx.x;

  if (m >= M)
    return;

  __shared__ float smem[32];//one block max 1024 thread, aka max 32 wrap

  //float val = m < M ? d_input[m]:0.0;//don't need conside this
  float val = d_input[m];

  for(int offset = 16; offset >0; offset/=2) {
    val += __shfl_down_sync(0xffffffff, val, offset);
  }

  if(threadIdx.x % 32 == 0) {
    smem[threadIdx.x/32] = val;
  }
  __syncthreads();

  if(threadIdx.x/32 == 0) {
    if(threadIdx.x < (blockDim.x + 31) / 32) {//in case blockDim.x not full a whole wrap
      val = smem[threadIdx.x];
    } else {
      val = 0.0;
    }

    for(int offset = 16; offset >0; offset/=2) {
      val += __shfl_down_sync(0xffffffff, val, offset);
    }

    if(threadIdx.x == 0)
      d_output[blockIdx.x] = val;
  }
}

__global__ void gpu_v5(float* d_input, float* d_output, int M, int N) {//total len, per block len
  int m = blockIdx.x * N + threadIdx.x * 4;

  if (m >= M)
    return;

  __shared__ float smem[32];//one block max 1024 thread, aka max 32 wrap

  //float val = m < M ? d_input[m]:0.0;//don't need conside this
  //float val = d_input[m];
  float4 val4 = *(float4*)&d_input[m];
  float val = val4.x + val4.y + val4.z + val4.w;

  for(int offset = 16; offset >0; offset/=2) {
    val += __shfl_down_sync(0xffffffff, val, offset);
  }

  if(threadIdx.x % 32 == 0) {
    smem[threadIdx.x/32] = val;
  }
  __syncthreads();

  if(threadIdx.x/32 == 0) {
    if(threadIdx.x < (blockDim.x + 31) / 32) {//in case blockDim.x not full a whole wrap
      val = smem[threadIdx.x];
    } else {
      val = 0.0;
    }

    for(int offset = 16; offset >0; offset/=2) {
      val += __shfl_down_sync(0xffffffff, val, offset);
    }

    if(threadIdx.x == 0)
      d_output[blockIdx.x] = val;
  }
}

int main() {
  int M = 1024;

  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);

  float* h_input = (float*)malloc(sizeof(float) * M);
  float* h_output = (float*)malloc(sizeof(float) * 1);
  float* d2h_output = (float*)malloc(sizeof(float) * 1);
  random_matrix(h_input, M);
  cpu(h_input, h_output, M);

  float* d_input;
  float* d_output;
  cudaMalloc((void**)&d_input, sizeof(float) * M);
  cudaMalloc((void**)&d_output, sizeof(float) * 1);
  cudaMemcpy(d_input, h_input, sizeof(float) * M, cudaMemcpyHostToDevice);

  //------------------------------v1
  int N = 64;//for block
  int BLOCK_SIZE = N / 2;
  //int block_num = ceil(M/N); 

  float* d_tmp;
  float* d_input_v1;
  cudaMalloc((void**)&d_input_v1, sizeof(float) * M);
  cudaMalloc((void**)&d_tmp, sizeof(float) * ceil(M/N));
  cudaMemcpy(d_input_v1, h_input, sizeof(float) * M, cudaMemcpyHostToDevice);

  dim3 block_size(BLOCK_SIZE, 1);
  dim3 grid_size(ceil(M/N), 1);

  cudaEventRecord(start, 0);
  gpu_v1<<<grid_size, block_size>>>(d_input_v1, d_tmp, M, N);
  gpu_v1<<<dim3(1,1), dim3(ceil(M/N)/2,1)>>>(d_tmp, d_output, ceil(M/N), ceil(M/N));
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_output, d_output, sizeof(float) * 1, cudaMemcpyDeviceToHost);

  bool result = compare(h_output, d2h_output, 1);
  if (result)
    printf("gpu_v1 compare pass\n");
  else
    printf("gpu_v1 compare not pass, please check\n");

  float elapsed;
  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v1 cost: %f ms\n\n", elapsed);

  cudaFree(d_tmp); 
  cudaFree(d_input_v1); 
  //-------------------------------v1



  //-------------------------------v2
  N = 64;
  BLOCK_SIZE = N / 2;

  cudaMalloc((void**)&d_tmp, sizeof(float) * ceil(M/N));

  //dim3 block_size(BLOCK_SIZE, 1);
  //dim3 grid_size(ceil(M/N), 1);

  cudaEventRecord(start, 0);
  gpu_v2<<<grid_size, block_size>>>(d_input, d_tmp, M, N);
  gpu_v2<<<dim3(1,1), dim3(ceil(M/N)/2,1)>>>(d_tmp, d_output, ceil(M/N), ceil(M/N));
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_output, d_output, sizeof(float) * 1, cudaMemcpyDeviceToHost);

  result = compare(h_output, d2h_output, 1);
  if (result)
    printf("gpu_v2 compare pass\n");
  else
    printf("gpu_v2 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v2 cost: %f ms\n\n", elapsed);

  cudaFree(d_tmp); 
  //-------------------------------v2
  


  //-------------------------------v3
  N = 64;
  BLOCK_SIZE = N / 2;

  cudaMalloc((void**)&d_tmp, sizeof(float) * ceil(M/N));

  //dim3 block_size(BLOCK_SIZE, 1);
  //dim3 grid_size(ceil(M/N), 1);

  cudaEventRecord(start, 0);
  gpu_v2<<<grid_size, block_size>>>(d_input, d_tmp, M, N);
  gpu_v2<<<dim3(1,1), dim3(ceil(M/N)/2,1)>>>(d_tmp, d_output, ceil(M/N), ceil(M/N));
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_output, d_output, sizeof(float) * 1, cudaMemcpyDeviceToHost);

  result = compare(h_output, d2h_output, 1);
  if (result)
    printf("gpu_v3 compare pass\n");
  else
    printf("gpu_v3 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v3 cost: %f ms\n\n", elapsed);

  cudaFree(d_tmp); 
  //-------------------------------v3
 


  //-------------------------------v4
  N = 64;
  BLOCK_SIZE = N;

  cudaMalloc((void**)&d_tmp, sizeof(float) * ceil(M/N));

  cudaEventRecord(start, 0);
  gpu_v4<<<dim3(ceil(M/N), 1), dim3(BLOCK_SIZE, 1)>>>(d_input, d_tmp, M, N);
  gpu_v4<<<dim3(1,1), dim3(ceil(M/N),1)>>>(d_tmp, d_output, ceil(M/N), ceil(M/N));
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_output, d_output, sizeof(float) * 1, cudaMemcpyDeviceToHost);

  result = compare(h_output, d2h_output, 1);
  if (result)
    printf("gpu_v4 compare pass\n");
  else
    printf("gpu_v4 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v4 cost: %f ms\n\n", elapsed);

  cudaFree(d_tmp); 
  //-------------------------------v4
 


  //-------------------------------v5
  N = 64;
  BLOCK_SIZE = N/4;

  cudaMalloc((void**)&d_tmp, sizeof(float) * ceil(M/N));

  cudaEventRecord(start, 0);
  gpu_v5<<<dim3(ceil(M/N), 1), dim3(BLOCK_SIZE, 1)>>>(d_input, d_tmp, M, N);
  gpu_v5<<<dim3(1,1), dim3(ceil(M/N),1)>>>(d_tmp, d_output, ceil(M/N), ceil(M/N));
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_output, d_output, sizeof(float) * 1, cudaMemcpyDeviceToHost);

  result = compare2(h_output, d2h_output, 1);
  if (result)
    printf("gpu_v5 compare pass\n");
  else
    printf("gpu_v5 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v5 cost: %f ms\n\n", elapsed);

  cudaFree(d_tmp); 
  //-------------------------------v5
 
  free(h_input);
  free(h_output);
  free(d2h_output);
  cudaFree(d_input);
  cudaFree(d_output);

  cudaEventDestroy(start);
  cudaEventDestroy(stop);
  return 0;
}
