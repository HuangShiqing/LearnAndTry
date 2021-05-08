#include "winograd4.h"
#include "common.h"

static void K_add_K(float* k, float* dst, int index1, int index2) {
    float* k1 = k + 6 * index1;
    float* k2 = k + 6 * index2;
    for (int i = 0; i < 6; i++)
        *dst++ = *(k1++) + *(k2++);
}

static void K_sub_K(float* k, float* dst, int index1, int index2) {
    float* k1 = k + 6 * index1;
    float* k2 = k + 6 * index2;
    for (int i = 0; i < 6; i++)
        *dst++ = *(k1++) - *(k2++);
}

void transforme_g_winograd4(float* g, float* transformed_g, int c, int n) {
    int g_c_stride = 3 * 3;
    int g_n_stride = c * g_c_stride;

    int transformed_g_c_stride = 16;
    int transformed_g_n_stride = c * transformed_g_c_stride;
    for (int i = 0; i < n; i++) {
        float* g_n = g + i * g_n_stride;
        float* transformed_g_n = transformed_g + i * transformed_g_n_stride;
        for (int j = 0; j < c; j++) {
            float* g_c = g_n + j * g_c_stride;
            float* transformed_g_c = transformed_g_n + j * transformed_g_c_stride;

            *(transformed_g_c++) = *g_c;
            *(transformed_g_c++) = (*g_c + *(g_c + 1) + *(g_c + 2)) * 0.5;
            *(transformed_g_c++) = (*g_c - *(g_c + 1) + *(g_c + 2)) * 0.5;
            *(transformed_g_c++) = *(g_c + 2);

            *(transformed_g_c++) = (*g_c + *(g_c + 3) + *(g_c + 6)) * 0.5;
            *(transformed_g_c++) = (*g_c + *(g_c + 3) + *(g_c + 6) + *(g_c + 1) + *(g_c + 4) + *(g_c + 7) + *(g_c + 2) +
                                    *(g_c + 5) + *(g_c + 8)) *
                                   0.25;
            *(transformed_g_c++) = (*g_c + *(g_c + 3) + *(g_c + 6) - *(g_c + 1) - *(g_c + 4) - *(g_c + 7) + *(g_c + 2) +
                                    *(g_c + 5) + *(g_c + 8)) *
                                   0.25;
            *(transformed_g_c++) = (*(g_c + 2) + *(g_c + 5) + *(g_c + 8)) * 0.5;

            *(transformed_g_c++) = (*g_c - *(g_c + 3) + *(g_c + 6)) * 0.5;
            *(transformed_g_c++) = (*g_c - *(g_c + 3) + *(g_c + 6) + *(g_c + 1) - *(g_c + 4) + *(g_c + 7) + *(g_c + 2) -
                                    *(g_c + 5) + *(g_c + 8)) *
                                   0.25;
            *(transformed_g_c++) = (*g_c - *(g_c + 3) + *(g_c + 6) - *(g_c + 1) + *(g_c + 4) - *(g_c + 7) + *(g_c + 2) -
                                    *(g_c + 5) + *(g_c + 8)) *
                                   0.25;
            *(transformed_g_c++) = (*(g_c + 2) - *(g_c + 5) + *(g_c + 8)) * 0.5;

            *(transformed_g_c++) = *(g_c + 6);
            *(transformed_g_c++) = (*(g_c + 6) + *(g_c + 7) + *(g_c + 8)) * 0.5;
            *(transformed_g_c++) = (*(g_c + 6) - *(g_c + 7) + *(g_c + 8)) * 0.5;
            *(transformed_g_c++) = *(g_c + 8);
        }
    }
}

void winograd4_1d(float* d, float* transformed_g, float* m) {
    //原始版本
    float m1 = (d[0] - d[2]) * transformed_g[0];
    float m2 = (d[1] + d[2]) * transformed_g[1];
    float m3 = (d[2] - d[1]) * transformed_g[2];
    float m4 = (d[1] - d[5]) * transformed_g[3];
    m[0] = m1 + m2 + m3;
    m[1] = m2 - m3 - m4;

    //优化点：减少中间变量
    //结果：无影响
    //   float m2 = (d[1] + d[2]) * transformed_g[1];
    //   float m3 = (d[2] - d[1]) * transformed_g[2];
    //   m[0] = (d[0] - d[2]) * transformed_g[0] + m2 + m3;
    //   m[1] = m2 - m3 - (d[1] - d[5]) * transformed_g[3];

    //测试点：乘法与加法对速度的影响
    //结果：无影响，则内存读写是瓶颈
    //   float m1 = (d[0] - d[2]) + transformed_g[0];
    //   float m2 = (d[1] + d[2]) + transformed_g[1];
    //   float m3 = (d[2] - d[1]) + transformed_g[2];
    //   float m4 = (d[1] - d[5]) + transformed_g[3];
    //   m[0] = m1 + m2 + m3;
    //   m[1] = m2 - m3 - m4;

    //测试点：内存读写对速度的影响
    //结果：前后时间比值为2.8
    //   float a=0.3;
    //   float b=0.1;
    //   float m1 = (a - b) * transformed_g[0];
    //   float m2 = (a + b) * transformed_g[1];
    //   float m3 = (a - b) * transformed_g[2];
    //   float m4 = (a - b) * transformed_g[3];
    //   m[0] = m1 + m2 + m3;
    //   m[1] = m2 - m3 - m4;

    //优化点：先从d都读到寄存器中，都内存操作减少了一半
    //结果：无影响
    //   register float d0 = d[0];
    //   register float d1 = d[1];
    //   register float d2 = d[2];
    //   register float d5 = d[5];
    //   float m1 = (d0 - d2) * transformed_g[0];
    //   float m2 = (d1 + d2) * transformed_g[1];
    //   float m3 = (d2 - d1) * transformed_g[2];
    //   float m4 = (d1 - d5) * transformed_g[3];
    //   m[0] = m1 + m2 + m3;
    //   m[1] = m2 - m3 - m4;
}

void winograd4_2d(float* transformed_k, float* transformed_g, float* R) {
    // float R[4]={0};
    // float R0[2] = {0};
    // float R1[2] = {0};

    float M0[2] = {0};
    float M1[2] = {0};
    float M2[2] = {0};
    float M3[2] = {0};
    float K0subK2[6] = {0};
    float K1subK3[6] = {0};
    float K1addK2[6] = {0};
    float K2subK1[6] = {0};

    K_sub_K(transformed_k, K0subK2, 0, 2);
    K_sub_K(transformed_k, K1subK3, 1, 5);  // k3是在5
    K_add_K(transformed_k, K1addK2, 1, 2);
    K_sub_K(transformed_k, K2subK1, 2, 1);

    winograd4_1d(K0subK2, transformed_g, M0);
    winograd4_1d(K1addK2, transformed_g + 4, M1);
    winograd4_1d(K2subK1, transformed_g + 8, M2);
    winograd4_1d(K1subK3, transformed_g + 12, M3);

    for (int i = 0; i < 2; i++)
        R[i] += M0[i] + M1[i] + M2[i];  //可以累加
    for (int i = 0; i < 2; i++)
        R[2 + i] += M1[i] - M2[i] - M3[i];  //可以累加

}

void convolutional_winograd4(float* transformed_g, float* transformed_k, float* R, int height, int width, int channels,
                             int n, int m, int r) {
    int height_col = (height - 2) / m;  //纵坐标上有多少个tile
    int width_col = (width - 2) / m;    //横坐标上有多少个tile

    int stride_transformed_k_width_col = 36;
    int stride_transformed_k_height_col = width_col * stride_transformed_k_width_col;
    int stride_transformed_k_channels = height_col * stride_transformed_k_height_col;
    int stride_transformed_k_n = 0;  //输入图像没有n

    int stride_g_width_col = 0;
    int stride_g_height_col = 0;
    int stride_g_channels = 16;
    int stride_g_n = channels * stride_g_channels;

    int stride_R_width_col = 4;
    int stride_R_height_col = width_col * stride_R_width_col;
    int stride_R_channels = 0;  //因为要累加到一起
    int stride_R_n = height_col * stride_R_height_col;

    // 原始版本
    for (int nn = 0; nn < n; nn++)          //卷积核个数循环
        for (int c = 0; c < channels; c++)  //卷积核通道循环
            for (int h = 0; h < height_col; h++)
                for (int w = 0; w < width_col; w++)
                    winograd4_2d(transformed_k + c * stride_transformed_k_channels +
                                     h * stride_transformed_k_height_col + w * stride_transformed_k_width_col,
                                 transformed_g + nn * stride_g_n + c * stride_g_channels,
                                 R + nn * stride_R_n + h * stride_R_height_col + w * stride_R_width_col);

    // 优化点：索引计算 结果没有影响
    // for (int nn = 0; nn < n; nn++) //卷积核个数循环
    // {
    //     // int transformed_k_nn = 0;
    //     int transformed_g_nn = nn*stride_g_n;
    //     int R_nn = nn*stride_R_n;
    //     for (int c = 0; c < channels; c++) //卷积核通道循环
    //     {
    //         int transformed_k_channels = c*stride_transformed_k_channels;
    //         int transformed_g_channels = c*stride_g_channels;
    //         // int R_channels = 0;
    //         for (int h = 0; h < height_col; h++)
    //         {
    //             int transformed_k_height_col = h*stride_transformed_k_height_col;
    //             // int transformed_g_height_col = 0;
    //             int R_height_col = h*stride_R_height_col;
    //             for (int w = 0; w < width_col; w++)
    //                 winograd3_2d(
    //                     transformed_k+transformed_k_channels+transformed_k_height_col+w*stride_transformed_k_width_col,
    //                     transformed_g+transformed_g_nn+transformed_g_channels,
    //                     R+R_nn+R_height_col+w*stride_R_width_col);
    //         }
    //     }
    // }
}