#include "winograd5.h"
#include "common.h"

void winograd5_2d(float* U, float* d, float* result) {
    float BTd[16] = {0};
    float V[16] = {0};
    float UV[16] = {0};
    float ATUV[8] = {0};

    // dot(BT, 4, 4, d, 4, 4, BTd);
    for (int i = 0; i < 4; i++)
        BTd[i] = d[0 + i] - d[8 + i];
    for (int i = 0; i < 4; i++)
        BTd[4 + i] = d[4 + i] + d[8 + i];
    for (int i = 0; i < 4; i++)
        BTd[8 + i] = -d[4 + i] + d[8 + i];
    for (int i = 0; i < 4; i++)
        BTd[12 + i] = d[4 + i] - d[12 + i];

    // dot(BTd, 4, 4, B, 4, 4, V);
    for (int i = 0; i < 4; i++)
        V[0 + i * 4] = BTd[0 + i * 4] - BTd[2 + i * 4];
    for (int i = 0; i < 4; i++)
        V[1 + i * 4] = BTd[1 + i * 4] + BTd[2 + i * 4];
    for (int i = 0; i < 4; i++)
        V[2 + i * 4] = -BTd[1 + i * 4] + BTd[2 + i * 4];
    for (int i = 0; i < 4; i++)
        V[3 + i * 4] = BTd[1 + i * 4] - BTd[3 + i * 4];

    multi(U, 4, 4, V, 4, 4, UV);

    // dot(AT, 2, 4, UV, 4, 4, ATUV);
    for (int i = 0; i < 4; i++)
        ATUV[i] = UV[0 + i] + UV[4 + i] + UV[8 + i];
    for (int i = 0; i < 4; i++)
        ATUV[4 + i] = UV[4 + i] - UV[8 + i] - UV[12 + i];

    // dot(ATUV, 2, 4, A, 4, 2, result);
    // for(int i=0;i<2;i++)
    //     result[0+i*2] = ATUV[0+i*4] + ATUV[1+i*4] + ATUV[2+i*4];
    // for(int i=0;i<2;i++)
    //     result[1+i*2] = ATUV[1+i*4] - ATUV[2+i*4] - ATUV[3+i*4];
    result[0] += (ATUV[0] + ATUV[1] + ATUV[2]);
    result[2] += (ATUV[4] + ATUV[5] + ATUV[6]);
    result[1] += (ATUV[1] - ATUV[2] - ATUV[3]);
    result[3] += (ATUV[5] - ATUV[6] - ATUV[7]);
}

void convolutional_winograd5(float* transformed_g, float* d, float* result, int height, int width, int channels, int n,
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
                    winograd5_2d(nn * channels * 16 + c * 16 + transformed_g, temp_U_c + temp_U_h + w * 16 + d,
                                 temp_d_nn + temp_d_h + w * 4 + result);  // temp_U_nn ++ temp_d_c
            }
        }
    }
}