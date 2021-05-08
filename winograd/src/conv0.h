#ifndef __CON0_H__
#define __CON0_H__

float im2col_get_pixel(float* im, int height, int width, int channels, int row, int col, int channel, int pad);
void im2col_cpu(float* data_im, int channels, int height, int width, int ksize, int stride, int pad, float* data_col);
void gemm_nn(int M, int N, int K, float ALPHA, float* A, int lda, float* B, int ldb, float* C, int ldc);
void gemm_cpu(int TA, int TB, int M, int N, int K, float ALPHA, float* A, int lda, float* B, int ldb, float BETA,
              float* C, int ldc);
void gemm(int TA, int TB, int M, int N, int K, float ALPHA, float* A, int lda, float* B, int ldb, float BETA, float* C,
          int ldc);

#endif /* __CON0_H__ */