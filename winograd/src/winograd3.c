#include "winograd3.h"
#include "common.h"

void im2col_winograd3(float* data_im, int channels, int height, int width, int ksize, int stride, int m, int r,
                      float* data_col) {
    assert(ksize == r);
    int tile = m + r - 1;               //每个tile的尺寸
    int height_col = (height - 2) / m;  //纵坐标上有多少个tile
    int width_col = (width - 2) / m;    //横坐标上有多少个tile
    int step = tile - (r - stride);     //相邻tile之间首元素的距离

    // 先乘好下面这些变量省的for循环里再重复计算
    // int tile2 = tile * tile;
    // int width_col_tile2 = width_col * tile2;
    // int height_width_col_tile2 = height_col * width_col * tile2;
    int height_width = height * width;
    int step_width = step * width;

    int step_36 = 36;
    int width_col_36 = width_col * step_36;
    int height_width_col_36 = height_col * width_col_36;
    for (int c = 0; c < channels; c++)           //遍历通道
        for (int h = 0; h < height_col; h++)     //输入图像里按列遍历每个tile
            for (int w = 0; w < width_col; w++)  //输入图像里按行遍历每个tile
            {
                int width_stride = width;  //要换成image width
                float* dst = data_col + c * height_width_col_36 + h * width_col_36 + w * step_36;
                float* src = data_im + c * height_width + h * step_width + w * step;
                // data_col[c*height_width_col_tile2+h*width_col_tile2+w*tile2+i*tile+j] =
                // data_im[c*height_width+h*step_width+w*step+i*width+j];
                *(dst++) = *src;        // k0
                *(dst++) = *(src + 1);  // k1
                *(dst++) = *(src + 2);  // k2
                *(dst++) = *(src + 1);  // k1
                *(dst++) = *(src + 2);  // k2
                *(dst++) = *(src + 3);  // k3

                *(dst++) = *(src + width_stride);      // k4
                *(dst++) = *(src + width_stride + 1);  // k5
                *(dst++) = *(src + width_stride + 2);  // k6
                *(dst++) = *(src + width_stride + 1);  // k5
                *(dst++) = *(src + width_stride + 2);  // k6
                *(dst++) = *(src + width_stride + 3);  // k7

                *(dst++) = *(src + 2 * width_stride);      // k8
                *(dst++) = *(src + 2 * width_stride + 1);  // k9
                *(dst++) = *(src + 2 * width_stride + 2);  // k10
                *(dst++) = *(src + 2 * width_stride + 1);  // k9
                *(dst++) = *(src + 2 * width_stride + 2);  // k10
                *(dst++) = *(src + 2 * width_stride + 3);  // k11

                *(dst++) = *(src + width_stride);      // k4
                *(dst++) = *(src + width_stride + 1);  // k5
                *(dst++) = *(src + width_stride + 2);  // k6
                *(dst++) = *(src + width_stride + 1);  // k5
                *(dst++) = *(src + width_stride + 2);  // k6
                *(dst++) = *(src + width_stride + 3);  // k7

                *(dst++) = *(src + 2 * width_stride);      // k8
                *(dst++) = *(src + 2 * width_stride + 1);  // k9
                *(dst++) = *(src + 2 * width_stride + 2);  // k10
                *(dst++) = *(src + 2 * width_stride + 1);  // k9
                *(dst++) = *(src + 2 * width_stride + 2);  // k10
                *(dst++) = *(src + 2 * width_stride + 3);  // k11

                *(dst++) = *(src + 3 * width_stride);      // k12
                *(dst++) = *(src + 3 * width_stride + 1);  // k13
                *(dst++) = *(src + 3 * width_stride + 2);  // k14
                *(dst++) = *(src + 3 * width_stride + 1);  // k13
                *(dst++) = *(src + 3 * width_stride + 2);  // k14
                *(dst++) = *(src + 3 * width_stride + 3);  // k15
            }
}


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

void winograd3_1d(float* d, float* g, float* m) {
    float m1 = (d[0] - d[2]) * g[0];
    float m2 = (d[1] + d[2]) * (g[0] + g[1] + g[2]) * 0.5;
    float m3 = (d[2] - d[1]) * (g[0] - g[1] + g[2]) * 0.5;
    float m4 = (d[1] - d[5]) * g[2];
    m[0] = m1 + m2 + m3;
    m[1] = m2 - m3 - m4;
}

void winograd3_2d(float* transformed_k, float* g, float* R) {
    // float R[4]={0};
    // float R0[2] = {0};
    // float R1[2] = {0};
    float M0[2] = {0};
    float M1[2] = {0};
    float M2[2] = {0};
    float M3[2] = {0};
    float W0addW1addW2[3] = {0};
    float W0subW1addW2[3] = {0};
    float K0subK2[6] = {0};
    float K1subK3[6] = {0};
    float K1addK2[6] = {0};
    float K2subK1[6] = {0};

    K_sub_K(transformed_k, K0subK2, 0, 2);
    K_sub_K(transformed_k, K1subK3, 1, 5);  // k3是在5
    K_add_K(transformed_k, K1addK2, 1, 2);
    K_sub_K(transformed_k, K2subK1, 2, 1);

    for (int i = 0; i < 3; i++)
        W0addW1addW2[i] = (g[i] + g[3 + i] + g[6 + i]) * 0.5;
    for (int i = 0; i < 3; i++)
        W0subW1addW2[i] = (g[i] - g[3 + i] + g[6 + i]) * 0.5;

    winograd3_1d(K0subK2, g, M0);
    winograd3_1d(K1addK2, W0addW1addW2, M1);
    winograd3_1d(K2subK1, W0subW1addW2, M2);
    winograd3_1d(K1subK3, g + 6, M3);

    for (int i = 0; i < 2; i++)
        R[i] += M0[i] + M1[i] + M2[i];  //可以累加
    for (int i = 0; i < 2; i++)
        R[2 + i] += M1[i] - M2[i] - M3[i];  //可以累加
}

void convolutional_winograd3(float* g, float* transformed_k, float* R, int height, int width, int channels, int n,
                             int m, int r) {
    int height_col = (height - 2) / m;  //纵坐标上有多少个tile
    int width_col = (width - 2) / m;    //横坐标上有多少个tile

    int stride_transformed_k_width_col = 36;
    int stride_transformed_k_height_col = width_col * stride_transformed_k_width_col;
    int stride_transformed_k_channels = height_col * stride_transformed_k_height_col;
    int stride_transformed_k_n = 0;  //输入图像没有n

    int stride_g_width_col = 0;
    int stride_g_height_col = 0;
    int stride_g_channels = 9;
    int stride_g_n = channels * stride_g_channels;

    int stride_R_width_col = 4;
    int stride_R_height_col = width_col * stride_R_width_col;
    int stride_R_channels = 0;  //因为要累加到一起
    int stride_R_n = height_col * stride_R_height_col;

    for (int nn = 0; nn < n; nn++)          //卷积核个数循环
        for (int c = 0; c < channels; c++)  //卷积核通道循环
            for (int h = 0; h < height_col; h++)
                for (int w = 0; w < width_col; w++)
                    winograd3_2d(
                        transformed_k + nn * stride_transformed_k_n + c * stride_transformed_k_channels +
                            h * stride_transformed_k_height_col + w * stride_transformed_k_width_col,
                        g + nn * stride_g_n + c * stride_g_channels + h * stride_g_height_col + w * stride_g_width_col,
                        R + nn * stride_R_n + c * stride_R_channels + h * stride_R_height_col + w * stride_R_width_col);
    // winograd3_2d(transformed_k+nn*channels*height_col*width_col*36+c*height_col*width_col*36+h*width_col*36+w*36,
    // g+nn*channels*9+c*9, R+nn*height_col*width_col*4+h*width_col*4+w*4);
}