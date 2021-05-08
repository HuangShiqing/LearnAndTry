// #include <assert.h>
// #include <memory.h>
// #include <stdio.h>
// #include <stdlib.h>

float A[8] = {1, 0, 1, 1, 1, -1, 0, -1};
float AT[8] = {1, 1, 1, 0, 0, 1, -1, -1};
float B[16] = {1, 0, 0, 0, 0, 1, -1, 1, -1, 1, 1, 0, 0, 0, 0, -1};
float BT[16] = {1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 1, 0, 0, 1, 0, -1};
float G[12] = {1, 0, 0, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0, 0, 1};
float GT[12] = {1, 0.5, 0.5, 0, 0, 0.5, -0.5, 0, 0, 0.5, 0.5, 1};

#include "common.h"
#include "conv0.h"
#include "winograd1.h"
#include "winograd2.h"
#include "winograd3.h"
#include "winograd4.h"
#include "winograd5.h"
// Y=AT[[GgGT]*[BTdB]]A
int main() {
    //------------------------------------------------
    // 产生数据
    int m = 2, r = 3;
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
    printf("input chw: %d,%d,%d\r\nfilter nchw: %d,%d,%d,%d\r\noutput nhw: %d,%d,%d\r\n\r\n", c, h, w, n, c, size, size,
           n, out_h, out_w);
    double t1, t2;

    //------------------------------------------------
    // conv0: im2col+gemm求卷积结果, 结果作为基准值
    t1 = what_time_is_it_now();
    float* im_0 = d;
    float* a_0 = g;
    float* b_0 =
        (float*)malloc(out_h * out_w * size * size * c / groups * sizeof(float));  //存储经过im2col的输入feature map
    float* output_0 = calloc(out_w * out_h * n, sizeof(float));
    im2col_cpu(im_0, c / groups, h, w, size, stride, pad, b_0);
    t2 = what_time_is_it_now();
    printf("conv0's im2col_cpu time: %f\r\n", t2 - t1);
    gemm(0, 0, n, out_h * out_w, size * size * c, 1, a_0, size * size * c, b_0, out_h * out_w, 1, output_0,
         out_h * out_w);
    t1 = what_time_is_it_now();
    printf("conv0's gemm time: %f\r\n", t1 - t2);
    printf("\r\n");

    //------------------------------------------------
    // winograd1: 思路一: 直接套公式(未提前计算g的transform)
    float* d_1 = d;
    float* g_1 = g;
    float* transformed_d_1 =
        (float*)malloc((w - 2) / 2 * (h - 2) / 2 * c * 16 * sizeof(float));  //存储经过im2col的输入feature map
    float* output_temp_1 = calloc(out_w * out_h * n, sizeof(float));
    float* output_1 = calloc(out_w * out_h * n, sizeof(float));
    t1 = what_time_is_it_now();
    im2col_winograd1(d_1, c / groups, h, w, size, stride, 2, 3, transformed_d_1);
    convolutional_winograd1(g_1, transformed_d_1, output_temp_1, h, w, c, n, 2, 3);
    col2im_winograd1(output_temp_1, n, h, w, size, stride, pad, m, output_1);
    t2 = what_time_is_it_now();
    printf("winograd1's time: %f\r\n", t2 - t1);
    compareResult(output_1, output_0, out_w * out_h * n);
    printf("\r\n");

    //------------------------------------------------
    // winograd2: 思路一: 直接套公式(提前计算g的transform)
    float* d_2 = d;
    float* g_2 = g;
    float* transformed_d_2 =
        (float*)malloc((w - 2) / 2 * (h - 2) / 2 * c * 16 * sizeof(float));  //存储经过im2col的输入feature map
    float* transformed_g_2 = calloc(n * c * 16, sizeof(float));
    float* output_temp_2 = calloc(out_w * out_h * n, sizeof(float));
    float* output_2 = calloc(out_w * out_h * n, sizeof(float));
    transforme_g_winograd2(g_2, transformed_g_2, c, n);
    t1 = what_time_is_it_now();
    im2col_winograd1(d_2, c / groups, h, w, size, stride, 2, 3, transformed_d_2);
    convolutional_winograd2(transformed_g_2, transformed_d_2, output_temp_2, h, w, c, n, 2, 3);
    col2im_winograd1(output_temp_2, n, h, w, size, stride, pad, m, output_2);
    t2 = what_time_is_it_now();
    printf("winograd2's time: %f\r\n", t2 - t1);
    compareResult(output_2, output_0, out_w * out_h * n);
    printf("\r\n");

    //------------------------------------------------
    // winograd3: 思路二: 嵌套使用两次结论公式1(未提前计算g的transform)
    float* d_3 = d;
    float* g_3 = g;
    float* transformed_d_3 =
        (float*)malloc((w - 2) / 2 * (h - 2) / 2 * c * 36 * sizeof(float));  //存储经过im2col的输入feature map
    float* output_temp_3 = calloc(out_w * out_h * n, sizeof(float));
    float* output_3 = calloc(out_w * out_h * n, sizeof(float));
    t1 = what_time_is_it_now();
    im2col_winograd3(d_3, c / groups, h, w, size, stride, 2, 3, transformed_d_3);
    t2 = what_time_is_it_now();
    printf("winograd3's im2col_winograd_3 time: %f\r\n", t2 - t1);
    convolutional_winograd3(g_3, transformed_d_3, output_temp_3, h, w, c, n, 2, 3);
    t1 = what_time_is_it_now();
    printf("winograd3's convolutional_winograd3 time: %f\r\n", t1 - t2);
    col2im_winograd1(output_temp_3, n, h, w, size, stride, pad, m, output_3);
    t2 = what_time_is_it_now();
    printf("winograd3's col2im_winograd1 time: %f\r\n", t2 - t1);
    compareResult(output_3, output_0, out_w * out_h * n);
    printf("\r\n");

    //------------------------------------------------
    // winograd4: 思路二: 嵌套使用两次结论公式1(提前计算g的transform)
    float* d_4 = d;
    float* g_4 = g;
    float* transformed_d_4 =
        (float*)malloc((w - 2) / 2 * (h - 2) / 2 * c * 36 * sizeof(float));  //存储经过im2col的输入feature map
    float* transformed_g_4 = calloc(n * c * 16, sizeof(float));
    float* output_temp_4 = calloc(out_w * out_h * n, sizeof(float));
    float* output_4 = calloc(out_w * out_h * n, sizeof(float));
    transforme_g_winograd4(g_4, transformed_g_4, c, n);
    t1 = what_time_is_it_now();
    im2col_winograd3(d_4, c / groups, h, w, size, stride, 2, 3, transformed_d_4);
    t2 = what_time_is_it_now();
    printf("winograd4's im2col_winograd3 time: %f\r\n", t2 - t1);
    convolutional_winograd4(transformed_g_4, transformed_d_4, output_temp_4, h, w, c, n, 2, 3);
    t1 = what_time_is_it_now();
    printf("winograd4's convolutional_winograd4 time: %f\r\n", t1 - t2);
    col2im_winograd1(output_temp_4, n, h, w, size, stride, pad, m, output_4);
    t2 = what_time_is_it_now();
    printf("winograd4's col2im_winograd1 time: %f\r\n", t2 - t1);
    compareResult(output_4, output_0, out_w * out_h * n);
    printf("\r\n");

    //------------------------------------------------
    // winograd5: 思路三: 结论公式2与固定已知系数的加法(提前计算g的transform)
    float* d_5 = d;
    float* g_5 = g;
    float* transformed_d_5 =
        (float*)malloc((w - 2) / 2 * (h - 2) / 2 * c * 16 * sizeof(float));  //存储经过im2col的输入feature map
    float* transformed_g_5 = calloc(n * c * 16, sizeof(float));
    float* output_temp_5 = calloc(out_w * out_h * n, sizeof(float));
    float* output_5 = calloc(out_w * out_h * n, sizeof(float));
    transforme_g_winograd2(g_5, transformed_g_5, c, n);
    t1 = what_time_is_it_now();
    im2col_winograd1(d_5, c / groups, h, w, size, stride, 2, 3, transformed_d_5);
    t2 = what_time_is_it_now();
    printf("winograd5's im2col_winograd1 time: %f\r\n", t2 - t1);
    convolutional_winograd5(transformed_g_5, transformed_d_5, output_temp_5, h, w, c, n, 2, 3);
    t1 = what_time_is_it_now();
    printf("winograd5's convolutional_winograd5 time: %f\r\n", t1 - t2);
    col2im_winograd1(output_temp_5, n, h, w, size, stride, pad, m, output_5);
    t2 = what_time_is_it_now();
    printf("winograd5's col2im_winograd1 time: %f\r\n", t2 - t1);
    compareResult(output_5, output_0, out_w * out_h * n);

    free(d);
    free(g);
    free(b_0);
    free(output_0);

    free(transformed_d_1);
    free(output_temp_1);
    free(output_1);

    free(transformed_d_2);
    free(transformed_g_2);
    free(output_temp_2);
    free(output_2);

    free(transformed_d_3);
    free(output_temp_3);
    free(output_3);

    free(transformed_d_4);
    free(transformed_g_4);
    free(output_temp_4);
    free(output_4);

    free(transformed_d_5);
    free(transformed_g_5);
    free(output_temp_5);
    free(output_5);
    return 0;
}
