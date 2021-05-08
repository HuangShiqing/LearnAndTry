#include <sys/time.h>
#include <time.h>
#include "common.h"

// float A[8] = {1, 0, 1, 1, 1, -1, 0, -1};
// float AT[8] = {1, 1, 1, 0, 0, 1, -1, -1};
// float B[16] = {1, 0, 0, 0, 0, 1, -1, 1, -1, 1, 1, 0, 0, 0, 0, -1};
// float BT[16] = {1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 1, 0, 0, 1, 0, -1};
// float G[12] = {1, 0, 0, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0, 0, 1};
// float GT[12] = {1, 0.5, 0.5, 0, 0, 0.5, -0.5, 0, 0, 0.5, 0.5, 1};

double what_time_is_it_now() {
    struct timeval time;
    if (gettimeofday(&time, NULL)) {
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}
// 优化https://blog.csdn.net/denlee/article/details/4206923
void dot(float* A, int row_A, int col_A, float* B, int row_B, int col_B, float* C) {
    assert(col_A == row_B);              // && row_A == col_B
                                         //由矩阵相乘，要求f2=s1，以下用f2
    for (int i = 0; i < row_A; i++)      // i表示第i行
        for (int j = 0; j < col_B; j++)  // j表示第j列
            //  C[i*col_A + j] = 0;        //在这里 result[i][j] = result[i*f2+j];
            for (int p = 0; p < col_A; p++)
                C[i * col_B + j] += A[i * col_A + p] * B[p * col_B + j];
}
void multi(float* A, int row_A, int col_A, float* B, int row_B, int col_B, float* C) {
    assert(row_A == row_B && col_A == col_B);
    for (int i = 0; i < row_A; i++)
        for (int j = 0; j < col_A; j++)
            C[col_A * i + j] = A[col_A * i + j] * B[col_A * i + j];
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