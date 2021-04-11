#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#define UP_DIV(x, y) (((x) + (y)-1) / (y))

double what_time_is_it_now() {
    struct timeval time;
    if (gettimeofday(&time, NULL)) {
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

void compareResult(float* A, float* B, int len) {
    int correct = -1;
    for (int i = 0; i < len; i++) {
        if (A[i] != B[i]) {
            correct = i;
            break;
        }
    }
    if (correct != -1)
        printf("error in index %d\r\n", correct);
    else
        printf("same\r\n");
}

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

// 对于三维:
// area:原始图像的w*h
// depth:原始图像的c,传进来的时候不用人为设成4的倍数
// 对于四维:则需要在MNNPackC4外套for循环
void MNNPackC4(float* dst, const float* src, size_t area, size_t depth) {
    int z, x;
    int cur = 0;

    memset(dst, 0, area * UP_DIV(depth, 4) * 4 * sizeof(float));
    for (z = 0; z < depth; ++z) {
        int plane = z / 4;
        float* dstPlane = plane * area * 4 + dst;
        int offset = z % 4;
        for (x = 0; x < area; ++x) {
            dstPlane[4 * x + offset] = src[cur++];
        }
    }
}
// 对于三维:
// area:原始图像的w*h
// depth:原始图像的c,传进来的时候不用人为设成4的倍数
// 对于四维:则需要在MNNPackC4外套for循环
void MNNUnpackC4(float* dst, const float* src, size_t area, size_t depth) {
    int x;
    int z;
    int cur = 0;
    for (z = 0; z < depth; ++z) {
        int plane = z / 4;
        const float* srcPlane = plane * area * 4 + src;
        int offset = z % 4;
        for (x = 0; x < area; ++x) {
            dst[cur++] = srcPlane[4 * x + offset];
        }
    }
}

// nchw都是原始图像的参数
// c4==1时需要保证dst空间大小正确
void transpose(float* dst, float* src, int n, int c, int h, int w, int c4) {
    if (c4 == 0) {
        for (int n_i = 0; n_i < n; n_i++) {
            for (int c_i = 0; c_i < c; c_i++) {
                for (int h_i = 0; h_i < h; h_i++) {
                    for (int w_i = 0; w_i < w; w_i++) {
                        dst[c * h * w * n_i + w * h * c_i + h_i + w * w_i] =
                            src[c * h * w * n_i + w * h * c_i + w * h_i + w_i];
                    }
                }
            }
        }
    } else if (c4 == 1) {
        int depth_quad = UP_DIV(c, 4);
        int w_quad = 4 * w;
        // int plane = w*h;
        int depth_stride = 4 * h * w;
        for (int n_i = 0; n_i < n; n_i++)
            for (int depth_quad_i = 0; depth_quad_i < depth_quad; depth_quad_i++)
                for (int h_i = 0; h_i < h; h_i++)
                    for (int w_i = 0; w_i < w; w_i++) {
                        int dst_base =
                            depth_quad * depth_stride * n_i + depth_stride * depth_quad_i + 4 * h_i + 4 * h * w_i;
                        int src_base =
                            depth_quad * depth_stride * n_i + depth_stride * depth_quad_i + w_quad * h_i + 4 * w_i;
                        dst[dst_base] = src[src_base];
                        dst[dst_base + 1] = src[src_base + 1];
                        dst[dst_base + 2] = src[src_base + 2];
                        dst[dst_base + 3] = src[src_base + 3];
                    }
    }
}

void im2col_cpu_c4(float* data_im, int channels, int height, int width, int ksize, int stride, int pad,
                   float* data_col) {
    int c, h, w;
    int height_col = (height + 2 * pad - ksize) / stride + 1;
    int width_col = (width + 2 * pad - ksize) / stride + 1;

    //卷积过程滑动窗口所移动到过的位置长宽=输出feature map的长宽
    int channels_col = UP_DIV(channels, 4) * ksize * ksize;
    for (c = 0; c < channels_col; ++c) {
        int w_offset = c % ksize;
        int h_offset = (c / ksize) % ksize;
        int c_im = c / ksize / ksize;
        for (h = 0; h < height_col; ++h) {
            for (w = 0; w < width_col; ++w) {
                int im_row = h_offset + h * stride;
                int im_col = w_offset * 4 + w * stride * 4;  // change

                int col_index = (c * height_col + h) * width_col * 4 + w * 4;  // change
                data_col[col_index] = im2col_get_pixel(data_im, height, width * 4, channels, im_row, im_col, c_im, pad);
                data_col[col_index + 1] =
                    im2col_get_pixel(data_im, height, width * 4, channels, im_row, im_col + 1, c_im, pad);
                data_col[col_index + 2] =
                    im2col_get_pixel(data_im, height, width * 4, channels, im_row, im_col + 2, c_im, pad);
                data_col[col_index + 3] =
                    im2col_get_pixel(data_im, height, width * 4, channels, im_row, im_col + 3, c_im, pad);
            }
        }
    }
}

void gemm_nn(int M, int N, int K, float ALPHA, float* A, int lda, float* B, int ldb, float* C, int ldc) {
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
    int i, j, k;
// #pragma omp parallel for
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

void gemm_nn_neon(int M, int N, int K,  // float ALPHA,
                  float* A, int lda, float* B, int ldb, float* C, int ldc);
void gemm_nn_c4_neon(int M, int N, int K,  // float ALPHA,
                     float* A, int lda, float* B, int ldb, float* C, int ldc);
void gemm_nt_c4_neon(int M, int N, int K,  // float ALPHA,
                     float* A, int lda, float* B, int ldb, float* C, int ldc);
int main(int argc, const char* argv[]) {
    // int arg = atoi(argv[1]);

    // input:3*3*4  filter:3*3*4*1
    // int w = 3, h = 3, c = 4, n = 1, groups = 1, size = 3, stride = 1, pad = 0;
    // input:32*32*4  filter:3*3*4*1
    // int w = 32, h = 32, c = 4, n = 1, groups = 1, size = 3, stride = 1, pad = 0;
    // input:416*416*256  filter:3*3*256*256
    int w = 416, h = 416, c = 20, n = 8, groups = 1, size = 3, stride = 1, pad = 0;

    float* d = calloc(w * h * c, sizeof(float));
    for (int i = 0; i < w * h * c; i++)
        d[i] = rand() % 10;
    float* g = calloc(size * size * c * n, sizeof(float));
    for (int i = 0; i < size * size * c * n; i++)
        g[i] = rand() % 10;
    int out_w = (w + 2 * pad - size) / stride + 1;
    int out_h = (h + 2 * pad - size) / stride + 1;
    printf("input chw:%d,%d,%d\r\nfilter nchw:%d,%d,%d,%d\r\noutput nhw: %d,%d,%d\r\n\r\n", c, h, w, n, c, h, w, n,
           out_h, out_w);
    double t1, t2;
    //------------------------------------------------
    printf("darknet CPU: \r\n");
    float* output_1 = calloc(out_w * out_h * n, sizeof(float));
    float* im_1 = d;
    float* a_1 = g;
    float* b_1 = calloc(out_h * out_w * size * size * c / groups, sizeof(float));  //存储经过im2col的输入feature map
    t1 = what_time_is_it_now();
    im2col_cpu(im_1, c / groups, h, w, size, stride, pad, b_1);
    t2 = what_time_is_it_now();
    printf("time with im2col+gemm im2col_cpu: %f\r\n", t2 - t1);
    gemm(0, 0, n, out_h * out_w, size * size * c, 1, a_1, size * size * c, b_1, out_h * out_w, 1, output_1,
         out_h * out_w);
    t1 = what_time_is_it_now();
    printf("time with im2col+gemm gemm: %f\r\n\r\n", t1 - t2);
    //------------------------------------------------
    printf("NEON CPU: \r\n");
    float* output_2 = calloc(out_w * out_h * n, sizeof(float));
    t1 = what_time_is_it_now();
    gemm_nn_neon(n, out_h * out_w, size * size * c, a_1, size * size * c, b_1, out_h * out_w, output_2, out_h * out_w);
    t2 = what_time_is_it_now();
    printf("time with neon gemm: %f\r\n", t2 - t1);
    compareResult(output_2, output_1, out_w * out_h * n);
    printf("\r\n");
    //------------------------------------------------
    printf("NEON C4 CPU: \r\n");
    float* output_3_c4 = calloc(out_w * out_h * n, sizeof(float));
    float* output_3 = calloc(out_w * out_h * n, sizeof(float));
    float* im_3 = d;
    float* a_3 = g;
    float* b_3_c4 =
        (float*)malloc(out_h * out_w * size * size * c / groups * sizeof(float));  //存储经过im2col的输入feature map
    float* a_3_c4 = calloc(size * size * UP_DIV(c, 4) * 4 * n, sizeof(float));
    float* im_3_c4 = calloc(h * w * UP_DIV(c, 4) * 4, sizeof(float));
    float* b_3_c4_T = calloc(out_h * out_w * size * size * c, sizeof(float));
    //这里可以对输入im_1先进行im2col得到b_1,然后再对b_1进行PackC4得到b_3_c4.也可以先对im_1进行PackC4,然后进行im2col_c4得到b_3_c4
    t1 = what_time_is_it_now();
    for (int i = 0; i < n; i++)
        MNNPackC4(a_3_c4 + i * size * size * c, a_3 + i * size * size * c, size * size, c);
    MNNPackC4(b_3_c4, b_1, out_h * out_w * size * size, c);
    t2 = what_time_is_it_now();
    printf("time with c4 MNNPackC4: %f\r\n", t2 - t1);
    // t1 = what_time_is_it_now();
    // for (int i = 0; i < n; i++)
    //     MNNPackC4(a_3_c4 + i * size * size * c, a_3 + i * size * size * c, size * size, c);
    // MNNPackC4(im_3_c4, im_3, h * w, c);
    // t2 = what_time_is_it_now();
    // printf("time with c4 MNNPackC4: %f\r\n", t2 - t1);
    // im2col_cpu_c4(im_3_c4, c / groups, h, w, size, stride, pad, b_3_c4);
    // t1 = what_time_is_it_now();
    // printf("time with c4 im2col: %f\r\n", t1 - t2);
    t1 = what_time_is_it_now();
    gemm_nn_c4_neon(n, out_h * out_w, size * size * c, a_3_c4, size * size * c, b_3_c4, out_h * out_w, output_3,
                    out_h * out_w);
    t2 = what_time_is_it_now();
    printf("time with c4 gemm: %f\r\n", t2 - t1);
    compareResult(output_3, output_1, out_w * out_h * n);
    memset(output_3, 0, out_w * out_h * n * sizeof(float));

    t1 = what_time_is_it_now();
    transpose(b_3_c4_T, b_3_c4, 1, 4, size * size * c / 4, out_h * out_w, 1);
    t2 = what_time_is_it_now();
    printf("time with c4 transpose: %f\r\n", t2 - t1);
    gemm_nt_c4_neon(n, out_h * out_w, size * size * c, a_3_c4, size * size * c, b_3_c4_T, out_h * out_w, output_3,
                    out_h * out_w);
    t1 = what_time_is_it_now();
    printf("time with c4 gemm nt: %f\r\n", t1 - t2);
    compareResult(output_3, output_1, out_w * out_h * n);
    printf("\r\n");

    return 0;
}