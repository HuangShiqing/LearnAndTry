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

bool compare2(float* input1, float* input2, int M, int N, float atol = 1e-5, float rtol = 1e-5) {
  for(int i=0; i<M*N; ++i) {
    //if(input1[i]!=input2[i]) {
    if (std::abs(input1[i] - input2[i]) > atol + rtol * std::abs(input2[i])) {
      printf("i: %d, input1[%d]: %f, input2[%d]: %f\n", i, i, input1[i], i, input2[i]);
      return false;
    }
  }
  return true;
}

void cpu(float* input, float* output, int M, int N){
  for(int m =0; m< M; m++) {
    float max = -1;//TODO
    for(int n =0; n< N; n++) {
      max = input[m*N+n] > max ? input[m*N+n] : max;
    }

    float sum = 0.0;
    for(int n =0; n< N; n++) {
      sum += exp(input[m*N+n] - max); 
    }

    for(int n =0; n< N; n++) {
      output[m*N+n] = exp(input[m*N+n] - max) / sum;
    }
  }
}

__global__ void gpu_v1(const float* d_input, float* d_output, int M, int N) {
  int offset = (blockIdx.x * blockDim.x + threadIdx.x) * N;

  float max = -1.0;
  for(int i=0; i< N; i++) {
    max = d_input[offset + i] > max ? d_input[offset + i] : max;
  }

  float sum = 0.0;
  for(int i=0; i< N; i++) {
    sum += expf(d_input[offset + i] - max);
  }

  for(int i=0; i< N; i++) {
    d_output[offset + i] = exp(d_input[offset + i]-max) / sum;
  }
}

__global__ void gpu_v2(const float* d_input, float* d_output, int M, int N) {
  int offset = (blockIdx.x * blockDim.x + threadIdx.x) * N;

  float max = -1.0;
  float sum = 0.0;
  for(int i=0; i< N; i++) {
    float cur = d_input[offset + i];
    if(cur > max) {
      sum *= expf(max - cur);
      max = cur;
    }
    sum += expf(cur - max);
  }

  for(int i=0; i< N; i++) {
    d_output[offset + i] = exp(d_input[offset + i]-max) / sum;
  }
}

__global__ void gpu_v3(const float* d_input, float* d_output, int M, int N) {
  int per_thread_len = (N + blockDim.x - 1)/ blockDim.x;
  int offset = blockIdx.x * N + threadIdx.x * per_thread_len;

  __shared__ float shm_max[32];

  float old_max = -1.0;
  float sum = 0.0;
  for(int i=0; i< per_thread_len; i++) {
    float cur = d_input[offset + i];
    if(cur > old_max) {
      sum *= expf(old_max - cur);
      old_max = cur;
    }
    sum += expf(cur - old_max);
  }
  shm_max[threadIdx.x] = old_max;
  __syncthreads();

  for(int i=blockDim.x/2; i>0; i/=2) {
    shm_max[threadIdx.x] = max(shm_max[threadIdx.x], shm_max[threadIdx.x+i]);
    __syncthreads();
  }
  float new_max = shm_max[0];

  shm_max[threadIdx.x] = sum * expf(old_max - new_max);
  for(int i=blockDim.x/2; i>0; i/=2) {
    shm_max[threadIdx.x] += shm_max[threadIdx.x+i];
    __syncthreads();
  }
  float new_sum = shm_max[0];

  for(int i=0; i< per_thread_len; i++) {
    d_output[offset + i] = exp(d_input[offset + i]-new_max) / new_sum;
  }
}

__global__ void gpu_v4(const float* d_input, float* d_output, int M, int N) {
  //int per_thread_len = (N + blockDim.x - 1)/ blockDim.x;
  int per_thread_len = 1;
  int start_offset = blockIdx.x * N + threadIdx.x * per_thread_len;

  __shared__ float shm_max[32];

  float old_max = -1.0;
  float sum = 0.0;
  for(int i=0; i< per_thread_len; i++) {
    float cur = d_input[start_offset + i];
    if(cur > old_max) {
      sum *= expf(old_max - cur);
      old_max = cur;
    }
    sum += expf(cur - old_max);
  }

  float new_max = old_max;
  for(int offset=16; offset>0; offset/=2) {
    new_max = max(new_max, __shfl_down_sync(0xffffffff, new_max, offset));
  }
  if(threadIdx.x%32==0) {
    shm_max[threadIdx.x/32] = new_max;
  }
  __syncthreads();

  if(blockDim.x > 32) {
    if(threadIdx.x/32==0) {
      new_max = threadIdx.x*32<blockDim.x?shm_max[threadIdx.x]:0.0;//make sure data is valid
      for(int offset=16; offset>0; offset/=2) {
        new_max = max(new_max, __shfl_down_sync(0xffffffff, new_max, offset));
      }
      shm_max[0] = new_max;
    }
  }
  __syncthreads();

  new_max = shm_max[0];
  sum = sum * expf(old_max - new_max);
  for(int offset=16; offset>0; offset/=2) {
    sum += __shfl_down_sync(0xffffffff, sum, offset);
  }
  if(threadIdx.x%32==0) {
    shm_max[threadIdx.x/32] = sum;
  }
  __syncthreads();

  if(blockDim.x > 32) {
    if(threadIdx.x/32==0) {
      sum = threadIdx.x*32<blockDim.x?shm_max[threadIdx.x]:0.0;//make sure data is valid
      for(int offset=16; offset>0; offset/=2) {
        sum += __shfl_down_sync(0xffffffff, sum, offset);
      }
      shm_max[0] = sum;
    }
  }
  __syncthreads();
    

  float new_sum = shm_max[0];
  for(int i=0; i< per_thread_len; i++) {
    d_output[start_offset + i] = exp(d_input[start_offset + i]-new_max) / new_sum;
  }
}

__global__ void gpu_v5(const float* d_input, float* d_output, int M, int N) {
  int per_thread_len = 4;
  int start_offset = blockIdx.x * N + threadIdx.x * per_thread_len;

  __shared__ float shm_max[32];

  float old_max = -1.0;
  float sum = 0.0;
  float4 cur4 = *((float4*)&d_input[start_offset]);
  float* cur_ptr = (float*)&cur4;
  for(int i=0; i< per_thread_len; i++) {
    float cur = cur_ptr[i];
    if(cur > old_max) {
      sum *= expf(old_max - cur);
      old_max = cur;
    }
    sum += expf(cur - old_max);
  }

  float new_max = old_max;
  for(int offset=16; offset>0; offset/=2) {
    new_max = max(new_max, __shfl_down_sync(0xffffffff, new_max, offset));
  }
  if(threadIdx.x%32==0) {
    shm_max[threadIdx.x/32] = new_max;
  }
  __syncthreads();

  if(blockDim.x > 32) {
    if(threadIdx.x/32==0) {
      new_max = threadIdx.x*32<blockDim.x?shm_max[threadIdx.x]:0.0;//make sure data is valid
      for(int offset=16; offset>0; offset/=2) {
        new_max = max(new_max, __shfl_down_sync(0xffffffff, new_max, offset));
      }
      shm_max[0] = new_max;
    }
  }
  __syncthreads();

  new_max = shm_max[0];
  sum = sum * expf(old_max - new_max);
  for(int offset=16; offset>0; offset/=2) {
    sum += __shfl_down_sync(0xffffffff, sum, offset);
  }
  if(threadIdx.x%32==0) {
    shm_max[threadIdx.x/32] = sum;
  }
  __syncthreads();

  if(blockDim.x > 32) {
    if(threadIdx.x/32==0) {
      sum = threadIdx.x*32<blockDim.x?shm_max[threadIdx.x]:0.0;//make sure data is valid
      for(int offset=16; offset>0; offset/=2) {
        sum += __shfl_down_sync(0xffffffff, sum, offset);
      }
      shm_max[0] = sum;
    }
  }
  __syncthreads();
    

  float new_sum = shm_max[0];
  for(int i=0; i< per_thread_len; i++) {
    d_output[start_offset + i] = exp(d_input[start_offset + i]-new_max) / new_sum;
  }
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
  cudaEventRecord(start, 0);
  gpu_v1<<<dim3(ceil(M/32), 1), dim3(32, 1)>>>(d_input, d_output, M, N);
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_output, d_output, sizeof(float) * M * N, cudaMemcpyDeviceToHost);

  bool result = compare2(h_output, d2h_output, M, N);
  if (result)
    printf("gpu_v1 compare pass\n");
  else
    printf("gpu_v1 compare not pass, please check\n");

  float elapsed;
  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v1 cost: %f ms\n\n", elapsed);
  //-------------------------------v1



  //-------------------------------v2
  cudaEventRecord(start, 0);
  gpu_v2<<<dim3(ceil(M/32), 1), dim3(32, 1)>>>(d_input, d_output, M, N);
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_output, d_output, sizeof(float) * M * N, cudaMemcpyDeviceToHost);

  result = compare2(h_output, d2h_output, M, N);
  if (result)
    printf("gpu_v2 compare pass\n");
  else
    printf("gpu_v2 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v2 cost: %f ms\n\n", elapsed);
  //-------------------------------v2
  



  ////-------------------------------v3
  cudaEventRecord(start, 0);
  gpu_v3<<<dim3(M, 1), dim3(32,1)>>>(d_input, d_output, M, N);
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_output, d_output, sizeof(float) * M * N, cudaMemcpyDeviceToHost);

  result = compare2(h_output, d2h_output, M, N);
  if (result)
    printf("gpu_v3 compare pass\n");
  else
    printf("gpu_v3 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v3 cost: %f ms\n\n", elapsed);
  ////-------------------------------v3



  ////-------------------------------v4
  cudaEventRecord(start, 0);
  gpu_v4<<<dim3(M, 1), dim3(N,1)>>>(d_input, d_output, M, N);
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_output, d_output, sizeof(float) * M * N, cudaMemcpyDeviceToHost);

  result = compare2(h_output, d2h_output, M, N);
  if (result)
    printf("gpu_v4 compare pass\n");
  else
    printf("gpu_v4 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v4 cost: %f ms\n\n", elapsed);
  ////-------------------------------v4


  ////-------------------------------v5
  cudaEventRecord(start, 0);
  gpu_v5<<<dim3(M, 1), dim3(N/4,1)>>>(d_input, d_output, M, N);
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_output, d_output, sizeof(float) * M * N, cudaMemcpyDeviceToHost);

  result = compare2(h_output, d2h_output, M, N);
  if (result)
    printf("gpu_v5 compare pass\n");
  else
    printf("gpu_v5 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v5 cost: %f ms\n\n", elapsed);
  ////-------------------------------v5


  free(h_input);
  free(h_output);
  free(d2h_output);
  cudaFree(d_input);
  cudaFree(d_output);

  cudaEventDestroy(start);
  cudaEventDestroy(stop);
  return 0;
}
