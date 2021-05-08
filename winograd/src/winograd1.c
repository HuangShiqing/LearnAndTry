#include "winograd1.h"
#include "common.h"

void im2col_winograd1(float* data_im, int channels, int height, int width, int ksize, int stride, int m, int r,
                      float* data_col) {
    assert(ksize == r);
    int tile = m + r - 1;               //每个tile的尺寸
    int height_col = (height - 2) / m;  //纵坐标上有多少个tile
    int width_col = (width - 2) / m;    //横坐标上有多少个tile
    int step = tile - (r - stride);     //相邻tile之间首元素的距离

    // 先乘好下面这些变量省的for循环里再重复计算
    int tile2 = tile * tile;
    int width_col_tile2 = width_col * tile2;
    int height_width_col_tile2 = height_col * width_col * tile2;
    int height_width = height * width;
    int step_width = step * width;
    for (int c = 0; c < channels; c++)              //遍历通道
        for (int h = 0; h < height_col; h++)        //输入图像里按列遍历每个tile
            for (int w = 0; w < width_col; w++)     //输入图像里按行遍历每个tile
                for (int i = 0; i < tile; i++)      //按列遍历每个tile里的行
                    for (int j = 0; j < tile; j++)  //按行遍历每个tile的元素
                        data_col[c * height_width_col_tile2 + h * width_col_tile2 + w * tile2 + i * tile + j] =
                            data_im[c * height_width + h * step_width + w * step + i * width + j];
}
void winograd1_2d(float* U, float* d, float* result) {
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
void convolutional_winograd1(float* g, float* d, float* result, int height, int width, int channels, int n, int m,
                             int r) {
    float Gg[12] = {0};
    float U[16] = {0};
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
            memset(Gg, 0, 12 * sizeof(float));  //清空
            memset(U, 0, 16 * sizeof(float));
            dot(G, 4, 3, nn * channels * 9 + c * 9 + g, 3, 3, Gg);  //先计算得到U=GgGT
            dot(Gg, 4, 3, GT, 3, 4, U);
            for (int h = 0; h < height_col; h++) {
                temp_U_h = h * width_col_16;
                temp_d_h = h * width_col_4;
                for (int w = 0; w < width_col; w++)
                    winograd1_2d(U, temp_U_c + temp_U_h + w * 16 + d,
                                 temp_d_nn + temp_d_h + w * 4 + result);  // temp_U_nn ++ temp_d_c
            }
        }
    }
}
void col2im_winograd1(float* temp_c, int n, int height, int width, int ksize, int stride, int pad, int m, float* c) {
    int height_col = (height - 2) / m;  //纵坐标上有多少个tile
    int width_col = (width - 2) / m;    //横坐标上有多少个tile

    int height_map = (height + 2 * pad - ksize) / stride + 1;
    int width_map = (width + 2 * pad - ksize) / stride + 1;
    for (int nn = 0; nn < n; nn++)                   //输出通道数循环
        for (int l = 0; l < height_col; l++)         //纵坐标上tile的循环
            for (int k = 0; k < 2; k++)              //循环每个tile结果的两行
                for (int i = 0; i < width_col; i++)  //横坐标上tile的循环
                    for (int j = 0; j < 2; j++)      //循环每个tile结果的两列
                        c[nn * width_map * height_map + l * 2 * width_map + k * 2 * width_col + i * 2 + j] =
                            temp_c[nn * width_map * height_map + l * width_col * 4 + k * 2 + i * 4 + j];
}