#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <cusparse.h>

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
#define CUSPARSE_CHECK(err) do { \
    cusparseStatus_t err_ = (err); \
    if (err_ != CUSPARSE_STATUS_SUCCESS) { \
        std::cerr << "cuSPARSE error at " << __FILE__ << ":" << __LINE__ << std::endl; \
        exit(EXIT_FAILURE); \
    } \
} while (0)


bool compare(float* input1, float* input2, int M, int N, float atol = 1e-5, float rtol = 1e-5) {
  for(int i=0; i<M*N; ++i) {
    //if(input1[i]!=input2[i]) {
    if (std::abs(input1[i] - input2[i]) > atol + rtol * std::abs(input2[i])) {
      printf("i: %d, input1[%d]: %f, input2[%d]: %f\n", i, i, input1[i], i, input2[i]);
      return false;
    }   
  }
  return true;
}

void spmm_cpu(
    int m, int k, int n,
    const float *h_csrValA,
    const int   *h_csrColIndA,
    const int   *h_csrRowPtrA,
    const float *h_B,
    float       *h_C)
{
    // 初始化C为0
    std::fill(h_C, h_C + m * n, 0.0f);

    // 遍历A的每一行
    #pragma omp parallel for
    for (int row = 0; row < m; ++row) {
        // 取当前行的非零元素区间
        int row_start = h_csrRowPtrA[row];
        int row_end   = h_csrRowPtrA[row + 1];

        // 遍历该行的每个非零元素
        for (int idx = row_start; idx < row_end; ++idx) {
            float val = h_csrValA[idx];    // 非零值
            int colA = h_csrColIndA[idx];  // 非零值对应的列

            // 该非零元素 * B的colA行，对应累加到C的row行
            for (int colB = 0; colB < n; ++colB) {
                // C[row, colB] += val * B[colA, colB]
                h_C[row * n + colB] += val * h_B[colA * n + colB];
            }
        }
    }
}

__global__ void gpu_v1(float* d_csrA_value, int* d_csrA_col_index, int* d_csrA_row_offset, int nnz, float* d_B, float* d_C, int m, int n, int k) {
    int BM = 4;
    int BN = 32;//lock

    int warp_idx = threadIdx.x / 32;
    int thread_idx = threadIdx.x % 32;

    int warp_row_offset_offset = blockIdx.y * BM + threadIdx.x / 32;
    int warp_row_offset = d_csrA_row_offset[warp_row_offset_offset];
    int warp_row_offset2 = d_csrA_row_offset[warp_row_offset_offset+1];
    float result = 0.0;
    for(int i = warp_row_offset; i < warp_row_offset2; i+=32) {
        float a_v = 0.0;
        int a_col = 0;

        int thread_val_offset = i + thread_idx;
        if(thread_val_offset < warp_row_offset2) {
            a_v = d_csrA_value[thread_val_offset];
            a_col = d_csrA_col_index[thread_val_offset];
        }

        float val_temp = 0.0;
        int col_temp = 0;

        for(int j=0; j<32;j++) {
            val_temp = __shfl_sync(0xFFFFFFFF, a_v, j);
            col_temp = __shfl_sync(0xFFFFFFFF, a_col, j);
            result += val_temp * d_B[blockIdx.x * BN + thread_idx +col_temp*n];
        }
    }
    d_C[blockIdx.y * BM * n + blockIdx.x * BN + warp_idx * n + thread_idx] = result;
} 


int main() {
    //srand(time(NULL));
    srand(1);

    cudaEvent_t start, stop;
    float elapsed;
    CUDA_CHECK(cudaEventCreate(&start));
    CUDA_CHECK(cudaEventCreate(&stop));

    cusparseHandle_t handle;
    CUSPARSE_CHECK(cusparseCreate(&handle));

    int m = 4096; // rows of sparse matrix A and dense matrix C
    int k = 2048;  // columns of sparse matrix A and rows of dense matrix B
    int n = 4096; // columns of dense matrices B and C
    float nnz_rate = 0.5;

    // 1. Host allocation
    float *h_B = new float[k * n];
    float *h_C = new float[m * n];
    float *h_C_cpu = new float[m * n];
    float *h_csrValA = nullptr;
    int   *h_csrColIndA = nullptr;
    int   *h_csrRowPtrA = nullptr;
    int nnz = m * k * nnz_rate; // Assume 10% sparsity

    // 2. Initialize host arrays
    for (int i = 0; i < k * n; ++i) {
        h_B[i] = rand() / (float)RAND_MAX;
    }

    h_csrValA    = new float[nnz];
    h_csrColIndA = new int[nnz];
    h_csrRowPtrA = new int[m + 1];

    // Initialize sparse matrix A in CSR format
    std::set<std::pair<int, int>> pos_set;
    while ((int)pos_set.size() < nnz) {
        int row = rand() % m;
        int col = rand() % k;
        pos_set.emplace(row, col); // Avoid duplicates
    }
    std::vector<std::vector<int>> row_cols(m);
    for (const auto& rc : pos_set) {
        row_cols[rc.first].push_back(rc.second);
    }
    h_csrRowPtrA[0] = 0;
    int idx = 0;
    for (int i = 0; i < m; ++i) {
        for (int col : row_cols[i]) {
            h_csrValA[idx]    = rand() / (float)RAND_MAX;
            h_csrColIndA[idx] = col;
            idx++;
        }
        h_csrRowPtrA[i + 1] = idx;
    }
    // 3. Device allocation
    float *d_B, *d_C;
    float* d_C_cusparse;
    float *d_csrValA;
    int *d_csrColIndA, *d_csrRowPtrA;

    CUDA_CHECK(cudaMalloc(&d_B, k * n * sizeof(float)));
    CUDA_CHECK(cudaMalloc(&d_C, m * n * sizeof(float)));
    CUDA_CHECK(cudaMalloc(&d_C_cusparse, m * n * sizeof(float)));
    CUDA_CHECK(cudaMalloc(&d_csrValA,    nnz * sizeof(float)));
    CUDA_CHECK(cudaMalloc(&d_csrColIndA, nnz * sizeof(int)));
    CUDA_CHECK(cudaMalloc(&d_csrRowPtrA, (m + 1) * sizeof(int)));

    // 4. Memcpy from host to device
    CUDA_CHECK(cudaMemcpy(d_B, h_B, k * n * sizeof(float), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemset(d_C, 0, m * n * sizeof(float))); // beta = 0, so C not used but nice to clear
    CUDA_CHECK(cudaMemcpy(d_csrValA,    h_csrValA,    nnz * sizeof(float), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_csrColIndA, h_csrColIndA, nnz * sizeof(int),   cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_csrRowPtrA, h_csrRowPtrA, (m + 1) * sizeof(int), cudaMemcpyHostToDevice));

    // cusparse descriptors
    cusparseSpMatDescr_t matA;
    cusparseDnMatDescr_t matB, matC;

    CUSPARSE_CHECK(cusparseCreateCsr(&matA, m, k, nnz, d_csrRowPtrA, d_csrColIndA, d_csrValA,
                      CUSPARSE_INDEX_32I, CUSPARSE_INDEX_32I, CUSPARSE_INDEX_BASE_ZERO, CUDA_R_32F));
    CUSPARSE_CHECK(cusparseCreateDnMat(&matB, k, n, n, d_B, CUDA_R_32F, CUSPARSE_ORDER_ROW));
    CUSPARSE_CHECK(cusparseCreateDnMat(&matC, m, n, n, d_C_cusparse, CUDA_R_32F, CUSPARSE_ORDER_ROW));

    float alpha = 1.0f, beta = 0.0f;

    ////-------------------------------cpu
    //too slow
    //spmm_cpu(m,k,n,h_csrValA,h_csrColIndA,h_csrRowPtrA,h_B,h_C_cpu);
    ////-------------------------------cpu

    // Workspace for SpMM
    size_t workspace_size = 0;
    void* dBuffer = nullptr;
    CUSPARSE_CHECK(cusparseSpMM_bufferSize(
        handle, CUSPARSE_OPERATION_NON_TRANSPOSE, CUSPARSE_OPERATION_NON_TRANSPOSE,
        &alpha, matA, matB, &beta, matC, CUDA_R_32F,
        CUSPARSE_SPMM_ALG_DEFAULT, &workspace_size));
    CUDA_CHECK(cudaMalloc(&dBuffer, workspace_size));
    // Execute SpMM
    CUDA_CHECK(cudaEventRecord(start, 0));
    CUSPARSE_CHECK(cusparseSpMM(
        handle, CUSPARSE_OPERATION_NON_TRANSPOSE, CUSPARSE_OPERATION_NON_TRANSPOSE,
        &alpha, matA, matB, &beta, matC, CUDA_R_32F,
        CUSPARSE_SPMM_ALG_DEFAULT, dBuffer));
    CUDA_CHECK(cudaEventRecord(stop, 0));
    CUDA_CHECK(cudaEventSynchronize(stop));

    cudaMemcpy(h_C_cpu, d_C_cusparse, sizeof(float) * m * n, cudaMemcpyDeviceToHost);

    //bool result = compare(h_C, h_C_cpu, m, n); 
    //if (result)
    //  printf("cusparse compare pass\n");
    //else
    //  printf("cusparse compare not pass, please check\n");

    cudaEventElapsedTime(&elapsed, start, stop);
    printf("cusparseSpMM cost: %f ms\n", elapsed);


    ////-------------------------------v1
    cudaEventRecord(start, 0);
    int BM=4;
    int BN=32;
    gpu_v1<<<dim3(n/BN, m/BM), dim3(BM*BN,1)>>>(d_csrValA, d_csrColIndA, d_csrRowPtrA, nnz, d_B, d_C, m, n, k); 
    CUDA_CHECK(cudaDeviceSynchronize());
    cudaEventRecord(stop, 0); 
    cudaEventSynchronize(stop);
  
    cudaMemcpy(h_C, d_C, sizeof(float) * m * n, cudaMemcpyDeviceToHost);
  
    bool result = compare(h_C, h_C_cpu, m, n); 
    if (result)
      printf("gpu_v1 compare pass\n");
    else
      printf("gpu_v1 compare not pass, please check\n");
  
    cudaEventElapsedTime(&elapsed, start, stop);
    printf("gpu_v1 cost: %f ms\n\n", elapsed);
    ////-------------------------------v1

    // Cleanup
    CUDA_CHECK(cudaFree(dBuffer));
    CUSPARSE_CHECK(cusparseDestroySpMat(matA));
    CUSPARSE_CHECK(cusparseDestroyDnMat(matB));
    CUSPARSE_CHECK(cusparseDestroyDnMat(matC));
    CUSPARSE_CHECK(cusparseDestroy(handle));
    CUDA_CHECK(cudaFree(d_B));
    CUDA_CHECK(cudaFree(d_C));
    CUDA_CHECK(cudaFree(d_csrValA));
    CUDA_CHECK(cudaFree(d_csrRowPtrA));
    CUDA_CHECK(cudaFree(d_csrColIndA));
    CUDA_CHECK(cudaEventDestroy(start));
    CUDA_CHECK(cudaEventDestroy(stop));

    delete[] h_B;
    delete[] h_C;
    delete[] h_C_cpu;
    delete[] h_csrValA;
    delete[] h_csrColIndA;
    delete[] h_csrRowPtrA;

    return 0;
}

