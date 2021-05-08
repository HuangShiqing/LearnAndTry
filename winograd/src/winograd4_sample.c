#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

//思路二: 嵌套使用两次结论公式1
void winograd4_transforme_g(float* g, float* transformed_g) {
    *(transformed_g++) = *g;
    *(transformed_g++) = (*g + *(g + 1) + *(g + 2)) * 0.5;
    *(transformed_g++) = (*g - *(g + 1) + *(g + 2)) * 0.5;
    *(transformed_g++) = *(g + 2);

    *(transformed_g++) = (*g + *(g + 3) + *(g + 6)) * 0.5;
    *(transformed_g++) = (*g + *(g + 3) + *(g + 6) + *(g + 1) + *(g + 4) + *(g + 7) + *(g + 2) + *(g + 5) + *(g + 8)) * 0.25;
    *(transformed_g++) = (*g + *(g + 3) + *(g + 6) - *(g + 1) - *(g + 4) - *(g + 7) + *(g + 2) + *(g + 5) + *(g + 8)) * 0.25;
    *(transformed_g++) = (*(g + 2) + *(g + 5) + *(g + 8)) * 0.5;

    *(transformed_g++) = (*g - *(g + 3) + *(g + 6)) * 0.5;
    *(transformed_g++) = (*g - *(g + 3) + *(g + 6) + *(g + 1) - *(g + 4) + *(g + 7) + *(g + 2) - *(g + 5) + *(g + 8)) * 0.25;
    *(transformed_g++) = (*g - *(g + 3) + *(g + 6) - *(g + 1) + *(g + 4) - *(g + 7) + *(g + 2) - *(g + 5) + *(g + 8)) * 0.25;
    *(transformed_g++) = (*(g + 2) - *(g + 5) + *(g + 8)) * 0.5;

    *(transformed_g++) = *(g + 6);
    *(transformed_g++) = (*(g + 6) + *(g + 7) + *(g + 8)) * 0.5;
    *(transformed_g++) = (*(g + 6) - *(g + 7) + *(g + 8)) * 0.5;
    *(transformed_g++) = *(g + 8);
}

void winograd4_im2col(float* data_im, float* data_col) {
    int width_stride = 4;
    float* dst = data_col;
    float* src = data_im;

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

void winograd4_1d(float* d, float* transformed_g, float* m) {
    //原始版本
    float m1 = (d[0] - d[2]) * transformed_g[0];
    float m2 = (d[1] + d[2]) * transformed_g[1];
    float m3 = (d[2] - d[1]) * transformed_g[2];
    float m4 = (d[1] - d[5]) * transformed_g[3];
    m[0] = m1 + m2 + m3;
    m[1] = m2 - m3 - m4;
}

void K_add_K(float* k, float* dst, int index1, int index2) {
    float* k1 = k + 6 * index1;
    float* k2 = k + 6 * index2;
    for (int i = 0; i < 6; i++)
        *dst++ = *(k1++) + *(k2++);
}

void K_sub_K(float* k, float* dst, int index1, int index2) {
    float* k1 = k + 6 * index1;
    float* k2 = k + 6 * index2;
    for (int i = 0; i < 6; i++)
        *dst++ = *(k1++) - *(k2++);
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

int main(int argc, char const* argv[]) {
    float g[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    float d[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    float result[4] = {0};
    
    float* transformed_g = calloc(16, sizeof(float));
    winograd4_transforme_g(g, transformed_g);
    float* transformed_d = calloc(36, sizeof(float));
    winograd4_im2col(d, transformed_d);
    winograd4_2d(transformed_d, transformed_g, result);

    printf("winograd4's sample result: %f, %f, %f, %f\r\n", result[0], result[1], result[2], result[3]);
    return 0;
}