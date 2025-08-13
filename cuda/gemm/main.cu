#include <stdio.h>
#include <cmath>
#include <cuda.h>
#include <cublas_v2.h>


#define CUDA_CHECK(call)                                                       \
    do {                                                                       \
        cudaError_t err = call;                                                \
        if (err != cudaSuccess) {                                              \
            printf("CUDA Error: \n");                                          \
            printf("    File:       %s\n", __FILE__);                          \
            printf("    Line:       %d\n", __LINE__);                          \
            printf("    Error Code: %d\n", err);                               \
            printf("    Error Text: %s\n", cudaGetErrorString(err));           \
            exit(1);                                                           \
        }                                                                      \
    } while (0)
#define CUBLAS_CHECK(call)                                                     \
    do {                                                                       \
        cublasStatus_t err = call;                                             \
        if (err != CUBLAS_STATUS_SUCCESS) {                                    \
            printf("cuBLAS Error: \n");                                        \
            printf("    File:       %s\n", __FILE__);                          \
            printf("    Line:       %d\n", __LINE__);                          \
            printf("    Error Code: %d\n", err);                               \
            printf("    Error Text: %s\n", cublasGetStatusString(err));        \
            exit(1);                                                           \
        }                                                                      \
    } while (0)

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

void cpu(float* A, float* B, float* C, int M, int N, int K){
  for(int m =0; m< M; m++) {
    for(int n =0; n< N; n++) {
      C[m*N+n] = 0.0;
      for(int k =0; k< K; k++) {
	C[m*N+n] += A[m*K+k] * B[k*N+n];
      }
    }
  }
}

__global__ void gpu_v1(const float* d_A, const float* d_B, float* d_C, int M, int N, int K) {
  const int m = blockIdx.y * blockDim.y + threadIdx.y;
  const int n = blockIdx.x * blockDim.x + threadIdx.x;

  float value = 0.0f;
  for (int k=0; k < K; k++) {
    value += d_A[m*K+k] * d_B[k*N+n];
  }
  d_C[m*N+n] = value;
}

__global__ void gpu_v2(const float* d_A, const float* d_B, float* d_C, int M, int N, int K) {
  const int BM = 16;
  const int BN = 16;
  const int BK = 16;
  __shared__ float s_a[BM][BK], s_b[BK][BN];

  float value = 0.0f;
  for (int step = 0; step < K / BK; step++) {
      __syncthreads();
      s_a[threadIdx.y][threadIdx.x] = d_A[(blockIdx.y * BM + threadIdx.y)*K+BK*step+threadIdx.x];
      s_b[threadIdx.y][threadIdx.x] = d_B[(BK*step+threadIdx.y)*N+blockIdx.x*BN+threadIdx.x];
      __syncthreads();
      for (int k = 0; k < BK; k++) {
        value += s_a[threadIdx.y][k] * s_b[k][threadIdx.x];
      }
  }
  d_C[(blockIdx.y*BM+threadIdx.y)*N+blockIdx.x*BN+threadIdx.x] = value;
}

//gpu_v3<<<dim3(ceil(M/16), ceil(N/16)), dim3(16, 16)>>>(d_A, d_B, d_C, M, N, K);
//__global__ void gpu_v3(const float* d_A, const float* d_B, float* d_C, int M, int N, int K) {
//  const int BM = 16;
//  const int BN = 16;
//  const int BK = 16;
//  __shared__ float s_a[BM][BK], s_b[BK][BN];
//
//  const int TM = 2;
//  const int TN = 2;
//  //const int TK = 1;
//  float r_a[TM];
//  float r_b[TN];
//  float r_c[TM][TN]={0.0f};
//
//  for (int step = 0; step < K / BK; step++) {
//      __syncthreads();
//      s_a[threadIdx.y][threadIdx.x] = d_A[(blockIdx.y * BM + threadIdx.y)*K+BK*step+threadIdx.x];
//      s_b[threadIdx.y][threadIdx.x] = d_B[(BK*step+threadIdx.y)*N+blockIdx.x*BN+threadIdx.x];
//      __syncthreads();
//      if(threadIdx.x>=8 || threadIdx.y>=8)
//	continue;
//      
//      for (int k = 0; k < BK; k++) {
//            for (int i = 0; i < TM; i++) {
//                r_a[i] = s_a[threadIdx.y * TM + i][k];
//            }
//            for (int i = 0; i < TN; i++) {
//                r_b[i] = s_b[k][threadIdx.x * TN + i];
//            }
//            for (int m = 0; m < TM; m++) {
//                for (int n = 0; n < TN; n++) {
//                    r_c[m][n] += r_a[m] * r_b[n];
//                }
//            }
//      }
//  }
//  if(threadIdx.x>=8 || threadIdx.y>=8)
//    return;
//  for (int m = 0; m < TM; m++) {
//      for (int n = 0; n < TN; n++) {
//          d_C[(blockIdx.y*BM+threadIdx.y*TM+m)*N+blockIdx.x*BN+threadIdx.x*TN+n] = r_c[m][n];
//      }
//  }
//}
__global__ void gpu_v3(const float* d_A, const float* d_B, float* d_C, int M, int N, int K) {
    const int BM = 32;
    const int BN = 32;
    const int BK = 8;
    __shared__ float s_a[BM][BK], s_b[BK][BN];
  
    const int TM = 2;
    const int TN = 2;
    //const int TK = 1;
    float r_a[TM];
    float r_b[TN];
    float r_c[TM][TN]={0.0f};

	const int tid = threadIdx.y * blockDim.x + threadIdx.x;
    const int row_s_a = tid / BK;
    const int col_s_a = tid % BK;
    const int row_s_b = tid / BN;
    const int col_s_b = tid % BN;
	const int row_A = blockIdx.y * BM + row_s_a;
    const int col_B = blockIdx.x * BN + col_s_b;
	for (int step = 0; step < K / BK; step++) {
		__syncthreads();
		s_a[row_s_a][col_s_a] = d_A[row_A * K + step * BK + col_s_a];
		s_b[row_s_b][col_s_b] = d_B[(step * BK + row_s_b)*N+col_B];
		__syncthreads();
      
        for (int k = 0; k < BK; k++) {
        	for (int i = 0; i < TM; i++) {
                r_a[i] = s_a[threadIdx.y * TM + i][k];
            }
            for (int i = 0; i < TN; i++) {
                r_b[i] = s_b[k][threadIdx.x * TN + i];
            }
            for (int m = 0; m < TM; m++) {
                for (int n = 0; n < TN; n++) {
                    r_c[m][n] += r_a[m] * r_b[n];
                }
            }
        }
    }
    for (int m = 0; m < TM; m++) {
        for (int n = 0; n < TN; n++) {
            d_C[(blockIdx.y*BM+threadIdx.y*TM+m)*N+blockIdx.x*BN+threadIdx.x*TN+n] = r_c[m][n];
        }
    }
}

__global__ void gpu_v4(const float* d_A, const float* d_B, float* d_C, int M, int N, int K) {
    const int BM = 128;
    const int BN = 128;
    const int BK = 8;
    __shared__ float s_a[BM][BK], s_b[BK][BN];
  
    const int TM = 8;
    const int TN = 8;
    //const int TK = 1;
    float r_a[TM];
    float r_b[TN];
    float r_c[TM][TN]={0.0f};

	const int tid = threadIdx.y * blockDim.x + threadIdx.x;
    const int row_s_a = tid / (BK/4);
    const int col_s_a = tid % (BK/4)*4;
    const int row_s_b = tid / (BN/4);
    const int col_s_b = tid % (BN/4)*4;
	const int row_A = blockIdx.y * BM + row_s_a;
    const int col_B = blockIdx.x * BN + col_s_b;
	for (int step = 0; step < K / BK; step++) {
		__syncthreads();
		(((float4*)&(s_a[row_s_a][col_s_a]))[0]) = (((float4*)&(d_A[row_A * K + step * BK + col_s_a]))[0]);
		(((float4*)&(s_b[row_s_b][col_s_b]))[0]) = (((float4*)&(d_B[(step * BK + row_s_b)*N+col_B]))[0]);
		__syncthreads();
      
        for (int k = 0; k < BK; k++) {
        	for (int i = 0; i < TM; i++) {
                r_a[i] = s_a[threadIdx.y * TM + i][k];
            }
            for (int i = 0; i < TN; i++) {
                r_b[i] = s_b[k][threadIdx.x * TN + i];
            }
            for (int m = 0; m < TM; m++) {
                for (int n = 0; n < TN; n++) {
                    r_c[m][n] += r_a[m] * r_b[n];
                }
            }
        }
    }
    for (int m = 0; m < TM; m++) {
        for (int n = 0; n < TN; n+=4) {
            (((float4*)&(d_C[(blockIdx.y*BM+threadIdx.y*TM+m)*N+blockIdx.x*BN+threadIdx.x*TN+n]))[0]) = (((float4*)&(r_c[m][n]))[0]);
        }
    }
}

//__global__ void gpu_v5(const float* d_A, const float* d_B, float* d_C, int M, int N, int K) {
//    const int BM = 128;
//    const int BN = 128;
//    const int BK = 8;
//    __shared__ float s_a[BK][BM], s_b[BK][BN];
//  
//    const int TM = 8;
//    const int TN = 8;
//    //const int TK = 1;
//    float r_a[TM];
//    float r_b[TN];
//    float r_c[TM][TN]={0.0f};
//
//	const int tid = threadIdx.y * blockDim.x + threadIdx.x;
//    const int row_s_a = tid / (BK/4);
//    const int col_s_a = tid % (BK/4)*4;
//    const int row_s_b = tid / (BN/4);
//    const int col_s_b = tid % (BN/4)*4;
//	const int row_A = blockIdx.y * BM + row_s_a;
//    const int col_B = blockIdx.x * BN + col_s_b;
//	for (int step = 0; step < K / BK; step++) {
//		__syncthreads();
//		(((float4*)&(r_a[0]))[0]) = (((float4*)&(d_A[row_A * K + step * BK + col_s_a]))[0]);
//		s_a[col_s_a + 0][row_s_a] = r_a[0];
//		s_a[col_s_a + 1][row_s_a] = r_a[1];
//		s_a[col_s_a + 2][row_s_a] = r_a[2];
//		s_a[col_s_a + 3][row_s_a] = r_a[3];
//		(((float4*)&(s_b[row_s_b][col_s_b]))[0]) = (((float4*)&(d_B[(step * BK + row_s_b)*N+col_B]))[0]);
//		__syncthreads();
//      
//        for (int k = 0; k < BK; k++) {
//        	for (int i = 0; i < TM; i++) {
//                r_a[i] = s_a[k][threadIdx.y * TM + i];
//            }
//            for (int i = 0; i < TN; i++) {
//                r_b[i] = s_b[k][threadIdx.x * TN + i];
//            }
//            for (int m = 0; m < TM; m++) {
//                for (int n = 0; n < TN; n++) {
//                    r_c[m][n] += r_a[m] * r_b[n];
//                }
//            }
//        }
//    }
//    for (int m = 0; m < TM; m++) {
//        for (int n = 0; n < TN; n+=4) {
//            (((float4*)&(d_C[(blockIdx.y*BM+threadIdx.y*TM+m)*N+blockIdx.x*BN+threadIdx.x*TN+n]))[0]) = (((float4*)&(r_c[m][n]))[0]);
//        }
//    }
//}
__global__ void gpu_v5(const float* d_A, const float* d_B, float* d_C, int M, int N, int K) {
    const int BM = 128;
    const int BN = 128;
    const int BK = 8;
    __shared__ float s_a[BM][BK], s_b[BK][BN];
  
    const int TM = 8;
    const int TN = 8;
    //const int TK = 1;
    float r_a[TM];
    float r_b[TN];
    float r_c[TM][TN]={0.0f};

	const int tid = threadIdx.y * blockDim.x + threadIdx.x;
    const int row_s_a = tid / (BK/4);
    const int col_s_a = tid % (BK/4)*4;
    const int row_s_b = tid / (BN/4);
    const int col_s_b = tid % (BN/4)*4;
	const int row_A = blockIdx.y * BM + row_s_a;
    const int col_B = blockIdx.x * BN + col_s_b;
	for (int step = 0; step < K / BK; step++) {
		__syncthreads();
		(((float4*)&(s_a[row_s_a][col_s_a]))[0]) = (((float4*)&(d_A[row_A * K + step * BK + col_s_a]))[0]);
		(((float4*)&(s_b[row_s_b][col_s_b]))[0]) = (((float4*)&(d_B[(step * BK + row_s_b)*N+col_B]))[0]);
		__syncthreads();
      
        for (int k = 0; k < BK; k++) {
        	for (int i = 0; i < TM; i++) {
                r_a[i] = s_a[threadIdx.y * TM + i][k];
            }
            //for (int i = 0; i < TN; i++) {
            //    r_b[i] = s_b[k][threadIdx.x * TN + i];
            //}
			(((float4*)&(r_b[0]))[0]) = (((float4*)&(s_b[k][threadIdx.x * TN/2]))[0]);
			(((float4*)&(r_b[0]))[4]) = (((float4*)&(s_b[k][threadIdx.x * TN/2 + BN/2]))[0]);
            for (int m = 0; m < TM; m++) {
                for (int n = 0; n < TN; n++) {
                    r_c[m][n] += r_a[m] * r_b[n];
                }
            }
        }
    }
    for (int m = 0; m < TM; m++) {
        //for (int n = 0; n < TN; n+=4) {
        (((float4*)&(d_C[(blockIdx.y*BM+threadIdx.y*TM+m)*N+blockIdx.x*BN+threadIdx.x*TN/2]))[0]) = (((float4*)&(r_c[m][0]))[0]);
        (((float4*)&(d_C[(blockIdx.y*BM+threadIdx.y*TM+m)*N+blockIdx.x*BN+threadIdx.x*TN/2+BN/2]))[0]) = (((float4*)&(r_c[m][4]))[0]);
        //}
    }
}

__global__ void gpu_v6(const float* d_A, const float* d_B, float* d_C, int M, int N, int K) {
    const int BM = 128;
    const int BN = 128;
    const int BK = 8;
    __shared__ float s_a[2][BM][BK], s_b[2][BK][BN];
  
    const int TM = 8;
    const int TN = 8;
    //const int TK = 1;
    float r_a[TM];
    float r_b[TN];
    float r_c[TM][TN]={0.0f};

	const int tid = threadIdx.y * blockDim.x + threadIdx.x;
    const int row_s_a = tid / (BK/4);
    const int col_s_a = tid % (BK/4)*4;
    const int row_s_b = tid / (BN/4);
    const int col_s_b = tid % (BN/4)*4;
	const int row_A = blockIdx.y * BM + row_s_a;
    const int col_B = blockIdx.x * BN + col_s_b;

	int pingpong = 0;
	int step = 0;
	(((float4*)&(s_a[pingpong][row_s_a][col_s_a]))[0]) = (((float4*)&(d_A[row_A * K + step * BK + col_s_a]))[0]);
	(((float4*)&(s_b[pingpong][row_s_b][col_s_b]))[0]) = (((float4*)&(d_B[(step * BK + row_s_b)*N+col_B]))[0]);
	for (int step = 1; step < K / BK; step++) {
		__syncthreads();
		(((float4*)&(s_a[(pingpong+1)%2][row_s_a][col_s_a]))[0]) = (((float4*)&(d_A[row_A * K + step * BK + col_s_a]))[0]);
		(((float4*)&(s_b[(pingpong+1)%2][row_s_b][col_s_b]))[0]) = (((float4*)&(d_B[(step * BK + row_s_b)*N+col_B]))[0]);
		//__syncthreads();
      
        for (int k = 0; k < BK; k++) {
        	for (int i = 0; i < TM; i++) {
                r_a[i] = s_a[pingpong%2][threadIdx.y * TM + i][k];
            }
            //for (int i = 0; i < TN; i++) {
            //    r_b[i] = s_b[k][threadIdx.x * TN + i];
            //}
			(((float4*)&(r_b[0]))[0]) = (((float4*)&(s_b[pingpong%2][k][threadIdx.x * TN/2]))[0]);
			(((float4*)&(r_b[0]))[4]) = (((float4*)&(s_b[pingpong%2][k][threadIdx.x * TN/2 + BN/2]))[0]);
            for (int m = 0; m < TM; m++) {
                for (int n = 0; n < TN; n++) {
                    r_c[m][n] += r_a[m] * r_b[n];
                }
            }
        }
		pingpong += 1;
    }
	//step = K / BK - 1;
    for (int k = 0; k < BK; k++) {
    	for (int i = 0; i < TM; i++) {
            r_a[i] = s_a[pingpong%2][threadIdx.y * TM + i][k];
        }
        //for (int i = 0; i < TN; i++) {
        //    r_b[i] = s_b[k][threadIdx.x * TN + i];
        //}
		(((float4*)&(r_b[0]))[0]) = (((float4*)&(s_b[pingpong%2][k][threadIdx.x * TN/2]))[0]);
		(((float4*)&(r_b[0]))[4]) = (((float4*)&(s_b[pingpong%2][k][threadIdx.x * TN/2 + BN/2]))[0]);
        for (int m = 0; m < TM; m++) {
            for (int n = 0; n < TN; n++) {
                r_c[m][n] += r_a[m] * r_b[n];
            }
        }
    }


    for (int m = 0; m < TM; m++) {
        //for (int n = 0; n < TN; n+=4) {
        (((float4*)&(d_C[(blockIdx.y*BM+threadIdx.y*TM+m)*N+blockIdx.x*BN+threadIdx.x*TN/2]))[0]) = (((float4*)&(r_c[m][0]))[0]);
        (((float4*)&(d_C[(blockIdx.y*BM+threadIdx.y*TM+m)*N+blockIdx.x*BN+threadIdx.x*TN/2+BN/2]))[0]) = (((float4*)&(r_c[m][4]))[0]);
        //}
    }
}





int main() {
  int M = 1024;
  int N = 1024;
  //int K = 1024;
  int K = 64;

  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);

  float* h_A = (float*)malloc(sizeof(float) * M * K);
  float* h_B = (float*)malloc(sizeof(float) * K * N);
  float* h_C = (float*)malloc(sizeof(float) * M * N);
  float* d2h_C = (float*)malloc(sizeof(float) * M * N);
  random_matrix(h_A, M, K);
  random_matrix(h_B, K, N);
  cpu(h_A, h_B, h_C, M, N, K);

  float* d_A;
  float* d_B;
  float* d_C;
  cudaMalloc((void**)&d_A, sizeof(float) * M * K);
  cudaMalloc((void**)&d_B, sizeof(float) * K * N);
  cudaMalloc((void**)&d_C, sizeof(float) * M * N);
  cudaMemcpy(d_A, h_A, sizeof(float) * M * K, cudaMemcpyHostToDevice);
  cudaMemcpy(d_B, h_B, sizeof(float) * K * N, cudaMemcpyHostToDevice);

  //------------------------------v1
  cudaEventRecord(start, 0);
  gpu_v1<<<dim3(ceil(M/16), ceil(N/16)), dim3(16, 16)>>>(d_A, d_B, d_C, M, N, K);
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_C, d_C, sizeof(float) * M * N, cudaMemcpyDeviceToHost);

  bool result = compare2(h_C, d2h_C, M, N);
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
  gpu_v2<<<dim3(ceil(M/16), ceil(N/16)), dim3(16, 16)>>>(d_A, d_B, d_C, M, N, K);
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_C, d_C, sizeof(float) * M * N, cudaMemcpyDeviceToHost);

  result = compare2(h_C, d2h_C, M, N);
  if (result)
    printf("gpu_v2 compare pass\n");
  else
    printf("gpu_v2 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v2 cost: %f ms\n\n", elapsed);
  //-------------------------------v2
  



  ////-------------------------------v3
  cudaEventRecord(start, 0);
  gpu_v3<<<dim3(ceil(M/32), ceil(N/32)), dim3(16, 16)>>>(d_A, d_B, d_C, M, N, K);
  CUDA_CHECK(cudaDeviceSynchronize());
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_C, d_C, sizeof(float) * M * N, cudaMemcpyDeviceToHost);

  result = compare2(h_C, d2h_C, M, N);
  if (result)
    printf("gpu_v3 compare pass\n");
  else
    printf("gpu_v3 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v3 cost: %f ms\n\n", elapsed);
  ////-------------------------------v3



  ////-------------------------------v4
  cudaEventRecord(start, 0);
  gpu_v4<<<dim3(ceil(M/128), ceil(N/128)), dim3(16, 16)>>>(d_A, d_B, d_C, M, N, K);
  CUDA_CHECK(cudaDeviceSynchronize());
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_C, d_C, sizeof(float) * M * N, cudaMemcpyDeviceToHost);

  result = compare2(h_C, d2h_C, M, N);
  if (result)
    printf("gpu_v4 compare pass\n");
  else
    printf("gpu_v4 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v4 cost: %f ms\n\n", elapsed);
  ////-------------------------------v4


  ////-------------------------------v5
  cudaEventRecord(start, 0);
  gpu_v5<<<dim3(ceil(M/128), ceil(N/128)), dim3(16, 16)>>>(d_A, d_B, d_C, M, N, K);
  CUDA_CHECK(cudaDeviceSynchronize());
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_C, d_C, sizeof(float) * M * N, cudaMemcpyDeviceToHost);

  result = compare2(h_C, d2h_C, M, N);
  if (result)
    printf("gpu_v5 compare pass\n");
  else
    printf("gpu_v5 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v5 cost: %f ms\n\n", elapsed);
  ////-------------------------------v5

  ////-------------------------------v6
  cudaEventRecord(start, 0);
  gpu_v6<<<dim3(ceil(M/128), ceil(N/128)), dim3(16, 16)>>>(d_A, d_B, d_C, M, N, K);
  CUDA_CHECK(cudaDeviceSynchronize());
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_C, d_C, sizeof(float) * M * N, cudaMemcpyDeviceToHost);

  result = compare2(h_C, d2h_C, M, N);
  if (result)
    printf("gpu_v6 compare pass\n");
  else
    printf("gpu_v6 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v6 cost: %f ms\n\n", elapsed);
  ////-------------------------------v6



  ////-------------------------------cublas
  cublasHandle_t handle;
  CUBLAS_CHECK(cublasCreate(&handle));
  float cublas_alpha = 1.0;
  float cublas_beta = 0;

  cudaEventRecord(start, 0);
  cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, N, M, K, &cublas_alpha, d_B, N, d_A, K, &cublas_beta, d_C, N);
  CUDA_CHECK(cudaDeviceSynchronize());
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_C, d_C, sizeof(float) * M * N, cudaMemcpyDeviceToHost);

  result = compare2(h_C, d2h_C, M, N);
  if (result)
    printf("gpu_cublas compare pass\n");
  else
    printf("gpu_cublas compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_cublas cost: %f ms\n\n", elapsed);

  ////-------------------------------cublas

  CUBLAS_CHECK(cublasDestroy(handle));


  free(h_A);
  free(h_B);
  free(h_C);
  free(d2h_C);
  cudaFree(d_A);
  cudaFree(d_B);
  cudaFree(d_C);

  cudaEventDestroy(start);
  cudaEventDestroy(stop);
  return 0;
}
