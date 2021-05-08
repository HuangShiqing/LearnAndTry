#include "conv0.h"
#include "common.h"

float im2col_get_pixel(float* im, int height, int width, int channels, int row, int col, int channel, int pad) {
    row -= pad;
    col -= pad;

    if (row < 0 || col < 0 || row >= height || col >= width)
        return 0;
    return im[col + width * (row + height * channel)];
}

// From Berkeley Vision's Caffe!
// https://github.com/BVLC/caffe/blob/master/LICENSE
void im2col_cpu(float* data_im, int channels, int height, int width, int ksize, int stride, int pad, float* data_col) {
    int c, h, w;
    int height_col = (height + 2 * pad - ksize) / stride + 1;
    int width_col = (width + 2 * pad - ksize) / stride + 1;

    //卷积过程滑动窗口所移动到过的位置长宽=输出feature map的长宽
    int channels_col = channels * ksize * ksize;
    for (c = 0; c < channels_col; ++c) {
        int w_offset = c % ksize;
        int h_offset = (c / ksize) % ksize;
        int c_im = c / ksize / ksize;
        for (h = 0; h < height_col; ++h) {
            for (w = 0; w < width_col; ++w) {
                int im_row = h_offset + h * stride;
                int im_col = w_offset + w * stride;
                int col_index = (c * height_col + h) * width_col + w;
                data_col[col_index] = im2col_get_pixel(data_im, height, width, channels, im_row, im_col, c_im, pad);
            }
        }
    }
}

void gemm_nn(int M, int N, int K, float ALPHA, float* A, int lda, float* B, int ldb, float* C, int ldc)
// M=n,卷积核个数
// N=输出feature map的w*h
// K=k*k*c,单个卷积核的空间尺寸大小
// ALPHA=1
//*A=指向卷积核参数的指针
// lda=K=k*k*c,单个卷积核的空间尺寸大小
//*B=经过im2col的上一层feature map
// ldb=N=输出feature map的w*h
//*C=指向卷积结果的指针
// ldc=N=输出feature map的w*h
{
    int i, j, k;
    //#pragma omp parallel for
    for (i = 0; i < M; ++i) {      //卷积核间的循环，M=卷积核个数
        for (k = 0; k < K; ++k) {  //卷积核内的循环，K=单个卷积核的空间尺寸大小
            register float A_PART = ALPHA * A[i * lda + k];
            for (j = 0; j < N; ++j) {  // N=输出feature map的w*h
                C[i * ldc + j] += A_PART * B[k * ldb + j];
            }
        }
    }
}
void gemm_cpu(int TA, int TB, int M, int N, int K, float ALPHA, float* A, int lda, float* B, int ldb, float BETA,
              float* C, int ldc) {
    // printf("cpu: %d %d %d %d %d %f %d %d %f %d\n",TA, TB, M, N, K, ALPHA, lda, ldb, BETA, ldc);
    int i, j;
    for (i = 0; i < M; ++i) {
        for (j = 0; j < N; ++j) {
            C[i * ldc + j] *= BETA;
        }
    }
    if (!TA && !TB)
        gemm_nn(M, N, K, ALPHA, A, lda, B, ldb, C, ldc);
    // else if(TA && !TB)
    //     gemm_tn(M, N, K, ALPHA,A,lda, B, ldb,C,ldc);
    // else if(!TA && TB)
    //     gemm_nt(M, N, K, ALPHA,A,lda, B, ldb,C,ldc);
    // else
    //     gemm_tt(M, N, K, ALPHA,A,lda, B, ldb,C,ldc);
}

void gemm(int TA, int TB, int M, int N, int K, float ALPHA, float* A, int lda, float* B, int ldb, float BETA, float* C,
          int ldc) {
    gemm_cpu(TA, TB, M, N, K, ALPHA, A, lda, B, ldb, BETA, C, ldc);
}