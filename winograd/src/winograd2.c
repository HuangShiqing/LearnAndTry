#include "winograd2.h"
#include "common.h"

void transforme_g_winograd2(float* g, float* transformed_g, int c, int n) {
    float Gg[12] = {0};
    for (int nn = 0; nn < n; nn++) {
        for (int cc = 0; cc < c; cc++)  //卷积核通道循环
        {
            memset(Gg, 0, 12 * sizeof(float));                //清空
            dot(G, 4, 3, nn * c * 9 + cc * 9 + g, 3, 3, Gg);  //先计算得到U=GgGT
            dot(Gg, 4, 3, GT, 3, 4, nn * c * 16 + cc * 16 + transformed_g);
        }
    }
}

void winograd2_2d(float* U, float* d, float* result) {
    // float g[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // float d[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    // float Gg[12] = {0};
    // float U[16]={0};
    float BTd[16] = {0};
    float V[16] = {0};
    float UV[16] = {0};
    float ATUV[8] = {0};
    // float result[4]={0};
    // dot(G, 4, 3, g, 3, 3, Gg);
    // dot(Gg,4,3,GT,3,4,U);
    dot(BT, 4, 4, d, 4, 4, BTd);
    dot(BTd, 4, 4, B, 4, 4, V);
    multi(U, 4, 4, V, 4, 4, UV);
    dot(AT, 2, 4, UV, 4, 4, ATUV);
    dot(ATUV, 2, 4, A, 4, 2, result);
}

void convolutional_winograd2(float* transformed_g, float* d, float* result, int height, int width, int channels, int n,
                             int m, int r) {
    int height_col = (height - 2) / m;  //纵坐标上有多少个tile
    int width_col = (width - 2) / m;    //横坐标上有多少个tile

    int width_col_16 = width_col * 16;
    int height_col_width_col_16 = height_col * width_col_16;
    int channels_height_col_width_col_16 = channels * height_col_width_col_16;
    int width_col_4 = width_col * 4;
    int height_col_width_col_4 = height_col * width_col_4;
    // int channels_height_col_width_col_4 = channels * height_col_width_col_4;
    int temp_U_nn, temp_U_c, temp_U_h;
    int temp_d_nn, temp_d_c, temp_d_h;

    for (int nn = 0; nn < n; nn++)  //卷积核个数循环
    {
        // temp_U_nn = nn * channels_height_col_width_col_16;
        temp_d_nn = nn * height_col_width_col_4;
        for (int c = 0; c < channels; c++)  //卷积核通道循环
        {
            temp_U_c = c * height_col_width_col_16;
            // temp_d_c = c * height_col_width_col_4;
            for (int h = 0; h < height_col; h++) {
                temp_U_h = h * width_col_16;
                temp_d_h = h * width_col_4;
                for (int w = 0; w < width_col; w++)
                    winograd2_2d(nn * channels * 16 + c * 16 + transformed_g, temp_U_c + temp_U_h + w * 16 + d,
                                 temp_d_nn + temp_d_h + w * 4 + result);  // temp_U_nn ++ temp_d_c
            }
        }
    }
}