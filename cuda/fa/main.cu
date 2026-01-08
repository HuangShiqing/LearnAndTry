#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <cuda.h>


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

void cpu(float* Q, float* K, float* V, float* O, float* l, float* m, int batch_size, int head_num, int seqlen, int head_dim, float softmax_scale){
    // 临时缓冲，存放每个查询位置 i 对所有键 j 的 (稳定化后的) exp 值
    std::vector<float> buf(seqlen);
    
    const int bh_stride = seqlen * head_dim;            // 每个 head 的元素数
    const int b_stride  = head_num * seqlen * head_dim; // 每个 batch 的元素数
    const int lm_bh_stride = seqlen;                    // l/m 的每个 head 的元素数
    const int lm_b_stride  = head_num * seqlen;         // l/m 的每个 batch 的元素数
    
    for (int b = 0; b < batch_size; ++b) {
        const int qkb_base_b = b * b_stride;
        const int lm_base_b  = b * lm_b_stride;
    
        for (int h = 0; h < head_num; ++h) {
            const int base_bh   = qkb_base_b + h * bh_stride;   // Q/K/V 的 (b,h) 起始
            const int lm_base_bh = lm_base_b  + h * lm_bh_stride; // l/m 的 (b,h) 起始
    
            for (int i = 0; i < seqlen; ++i) {
                const int qi_off = base_bh + i * head_dim;
                const float* q_i = Q + qi_off;
    
                // 1) 计算 logits = (Q_i · K_j) * softmax_scale，并找最大值
                float max_s = -std::numeric_limits<float>::infinity();
                for (int j = 0; j < seqlen; ++j) {
                    const float* k_j = K + (base_bh + j * head_dim);
                    float dot = 0.0f;
                    for (int d = 0; d < head_dim; ++d) {
                        dot += q_i[d] * k_j[d];
                    }
                    float s = dot * softmax_scale;
                    buf[j] = s;
                    if (s > max_s) max_s = s;
                }
    
                // 2) 稳定 softmax：减去 max 后取 exp，并求和
                float sum_exp = 0.0f;
                for (int j = 0; j < seqlen; ++j) {
                    float e = std::exp(buf[j] - max_s);
                    buf[j] = e;   // 复用缓冲保存 exp 值
                    sum_exp += e;
                }
                const float inv_sum = 1.0f / sum_exp;
    
                // 记录 l 和 m（可用于验证/进一步优化）
                l[lm_base_bh + i] = sum_exp;
                m[lm_base_bh + i] = max_s;
    
                // 3) 计算输出 O[b,h,i,:] = Σ_j softmax_ij * V[b,h,j,:]
                float* o_i = O + qi_off;
                for (int d = 0; d < head_dim; ++d) o_i[d] = 0.0f;
    
                for (int j = 0; j < seqlen; ++j) {
                    const float a = buf[j] * inv_sum; // softmax 权重
                    const float* v_j = V + (base_bh + j * head_dim);
                    for (int d = 0; d < head_dim; ++d) {
                        o_i[d] += a * v_j[d];
                    }
                }
            }
        }
    }
}

//https://github.com/tspeterkim/flash-attention-minimal/tree/main
__global__ void fa(const float* Q, //[batch_size, head_num, seqlen, head_dim]
                   const float* K, //[batch_size, head_num, seqlen, head_dim]
                   const float* V, //[batch_size, head_num, seqlen, head_dim]
                   float* O, // [batch_size, head_num, seqlen, head_dim]
                   float* l, // [batch_size, head_num, seqlen]
                   float* m, //[batch_size, head_num, seqlen]
                   const int seqlen,
                   const int head_dim,
                   const int Tc,
                   const int Tr,
                   const int Bc,
                   const int Br,
                   const float softmax_scale) {

    int tx = threadIdx.x;
    int bx = blockIdx.x; int by = blockIdx.y;  // batch and head index

    // Offset into Q,K,V,O,l,m - different for each batch and head
    int qkv_offset = (bx * gridDim.y * seqlen * head_dim) + (by * seqlen * head_dim);  // gridDim.y = nh
    int lm_offset = (bx * gridDim.y * seqlen) + (by * seqlen);  // offset for l and m

    // Define SRAM for Q,K,V,S
    extern __shared__ float sram[];
    int tile_size = Bc * head_dim;  // size of Qi, Kj, Vj
    float* Qi = sram; // [Bc, head_dim]
    float* Kj = &sram[tile_size]; // [Bc, head_dim]
    float* Vj = &sram[tile_size * 2]; // [Bc, head_dim]
    float* S = &sram[tile_size * 3]; // [Bc, Br]

    for (int j = 0; j < Tc; j++) {

        // Load Kj, Vj to SRAM
        for (int x = 0; x < head_dim; x++) {
            Kj[(tx * head_dim) + x] = K[qkv_offset + (tile_size * j) + (tx * head_dim) + x];
            Vj[(tx * head_dim) + x] = V[qkv_offset + (tile_size * j) + (tx * head_dim) + x];
        }
        __syncthreads();  // such that the inner loop can use the correct Kj, Vj

        for (int i = 0; i < Tr; i++)  {

            // Load Qi to SRAM, l and m to registers
            for (int x = 0; x < head_dim; x++) {
                Qi[(tx * head_dim) + x] = Q[qkv_offset + (tile_size * i) + (tx * head_dim) + x];
            }
            __syncthreads();

            float row_m_prev = m[lm_offset + (Br * i) + tx];
            float row_l_prev = l[lm_offset + (Br * i) + tx];

            // S = QK^T, row_m = rowmax(S)
            float row_m = -INFINITY;
            for (int y = 0; y < Bc; y++) {
                float s = 0;
                for (int x = 0; x < head_dim; x++) {
                    s += Qi[(tx * head_dim) + x] * Kj[(y * head_dim) + x];
                }
                s *= softmax_scale;
                S[(Bc * tx) + y] = s;

                if (s > row_m)
                    row_m = s;
            }

            // P = exp(S - row_m), row_l = rowsum(P)
            float row_l = 0;
            for (int y = 0; y < Bc; y++) {
                S[(Bc * tx) + y] = __expf(S[(Bc * tx) + y] - row_m); //用当前block的max计算S
                row_l += S[(Bc * tx) + y];
            }

            // Compute new m and l
            float row_m_new = max(row_m_prev, row_m);
            float row_l_new = (__expf(row_m_prev - row_m_new) * row_l_prev) //修正上次计算累加值没有使用
                              + (__expf(row_m - row_m_new) * row_l);

            // Write O, l, m to HBM
            for (int x = 0; x < head_dim; x++) {
                float pv = 0;  // Pij * Vj
                for (int y = 0; y < Bc; y++) {
                    pv += S[(Bc * tx) + y] * Vj[(y * head_dim) + x];
                }
                // O[qkv_offset + (tile_size * i) + (tx * d) + x] = (1 / row_l_new) \
                //     * ((row_l_prev * __expf(row_m_prev - row_m_new) * O[qkv_offset + (tile_size * i) + (tx * head_dim) + x]) \
                //     + (__expf(row_m - row_m_new) * pv));
                size_t offset = qkv_offset + (tile_size * i) + (tx * head_dim) + x;
                O[offset] = (row_l_prev * O[offset] //恢复上次计算O时的除法
                             * __expf(row_m_prev - row_m_new) //修正上次计算时使用久的全局最大值而非新的全局最大值
                             + (__expf(row_m - row_m_new) * pv) //修正计算当前BcxBr的S时使用该S的每行的最大值而非新的全局最大值
                            ) / row_l_new;
            }
            m[lm_offset + (Br * i) + tx] = row_m_new;
            l[lm_offset + (Br * i) + tx] = row_l_new;
        }
        __syncthreads();  // otherwise, thread can use the wrong Kj, Vj in inner loop
    }
}

int main() {
  int batch_size = 1;
  int head_num = 1;
  int seqlen = 64;
  int head_dim = 64;
  float softmax_scale = 1.0 / sqrt(head_dim);

  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);

  float* h_Q = (float*)malloc(sizeof(float) * batch_size * head_num * seqlen * head_dim);
  float* h_K = (float*)malloc(sizeof(float) * batch_size * head_num * seqlen * head_dim);
  float* h_V = (float*)malloc(sizeof(float) * batch_size * head_num * seqlen * head_dim);
  float* h_O = (float*)malloc(sizeof(float) * batch_size * head_num * seqlen * head_dim);
  float* h_l = (float*)malloc(sizeof(float) * batch_size * head_num * seqlen);
  float* h_m = (float*)malloc(sizeof(float) * batch_size * head_num * seqlen);
  float* d2h_O = (float*)malloc(sizeof(float) * batch_size * head_num * seqlen * head_dim);

  random_matrix(h_Q, batch_size * head_num, seqlen * head_dim);
  random_matrix(h_K, batch_size * head_num, seqlen * head_dim);
  random_matrix(h_V, batch_size * head_num, seqlen * head_dim);
  memset(h_O, 0, batch_size * head_num * seqlen * head_dim * sizeof(float));//init zero
  memset(h_l, 0, batch_size * head_num * seqlen * sizeof(float));//init zero
  std::fill(h_m, h_m + batch_size * head_num * seqlen, -INFINITY);//init -inf
  cpu(h_Q, h_K, h_V, h_O, h_l, h_m, batch_size, head_num, seqlen, head_dim, softmax_scale);

  float* d_Q;
  float* d_K;
  float* d_V;
  float* d_O;
  float* d_l;
  float* d_m;
  cudaMalloc((void**)&d_Q, sizeof(float) * batch_size * head_num * seqlen * head_dim);
  cudaMalloc((void**)&d_K, sizeof(float) * batch_size * head_num * seqlen * head_dim);
  cudaMalloc((void**)&d_V, sizeof(float) * batch_size * head_num * seqlen * head_dim);
  cudaMalloc((void**)&d_O, sizeof(float) * batch_size * head_num * seqlen * head_dim);
  cudaMalloc((void**)&d_l, sizeof(float) * batch_size * head_num * seqlen);
  cudaMalloc((void**)&d_m, sizeof(float) * batch_size * head_num * seqlen);
  cudaMemcpy(d_Q, h_Q, sizeof(float) * batch_size * head_num * seqlen * head_dim, cudaMemcpyHostToDevice);
  cudaMemcpy(d_K, h_K, sizeof(float) * batch_size * head_num * seqlen * head_dim, cudaMemcpyHostToDevice);
  cudaMemcpy(d_V, h_V, sizeof(float) * batch_size * head_num * seqlen * head_dim, cudaMemcpyHostToDevice);
  cudaMemcpy(d_O, h_O, sizeof(float) * batch_size * head_num * seqlen * head_dim, cudaMemcpyHostToDevice);
  cudaMemcpy(d_l, h_l, sizeof(float) * batch_size * head_num * seqlen, cudaMemcpyHostToDevice);
  cudaMemcpy(d_m, h_m, sizeof(float) * batch_size * head_num * seqlen, cudaMemcpyHostToDevice);

  //------------------------------v1
  int Bc = 32;
  int Br = 32;
  int Tc = ceil((float) seqlen / Bc);
  int Tr = ceil((float) seqlen / Br);

  // Calculate SRAM size needed per block
  const int sram_size = (3 * Bc * head_dim * sizeof(float)) + (Bc * Br * sizeof(float));
  int max_sram_size;
  cudaDeviceGetAttribute(&max_sram_size, cudaDevAttrMaxSharedMemoryPerBlock, 0);
  printf("Max shared memory: %d, requested shared memory: %d.\n", max_sram_size, sram_size);

  cudaEventRecord(start, 0);
  fa<<<dim3(batch_size, head_num), dim3(Bc), sram_size>>>(d_Q, d_K, d_V, d_O, d_l, d_m, seqlen, head_dim, Tc, Tr, Bc, Br, softmax_scale);
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(d2h_O, d_O, sizeof(float) * batch_size * head_num * seqlen * head_dim, cudaMemcpyDeviceToHost);

  bool result = compare2(h_O, d2h_O, batch_size * head_num, seqlen * head_dim);
  if (result)
    printf("gpu_v1 compare pass\n");
  else
    printf("gpu_v1 compare not pass, please check\n");

  float elapsed;
  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v1 cost: %f ms\n\n", elapsed);
  //-------------------------------v1



  free(h_Q);
  free(h_K);
  free(h_V);
  free(h_O);
  free(d2h_O);
  free(h_l);
  free(h_m);
  cudaFree(d_Q);
  cudaFree(d_K);
  cudaFree(d_V);
  cudaFree(d_O);
  cudaFree(d_l);
  cudaFree(d_m);

  cudaEventDestroy(start);
  cudaEventDestroy(stop);
  return 0;
}
