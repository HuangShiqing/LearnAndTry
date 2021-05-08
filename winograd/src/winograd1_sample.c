#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// 思路一: 直接套公式
float A[8] = {1, 0, 
              1, 1, 
              1, -1,
              0, -1};
float AT[8] = {1, 1, 1, 0,
               0, 1, -1, -1};
float B[16] = {1, 0, 0, 0, 
               0, 1, -1, 1,
               -1, 1, 1, 0,
               0, 0, 0, -1};
float BT[16] = {1, 0, -1, 0,
                0, 1, 1, 0,
                0, -1, 1, 0,
                0, 1, 0, -1};
float G[12] = {1, 0, 0,
               0.5, 0.5, 0.5,
               0.5, -0.5, 0.5,
               0, 0, 1};
float GT[12] = {1, 0.5, 0.5, 0,
                0, 0.5, -0.5, 0,
                0, 0.5, 0.5, 1};
//矩阵乘
void dot(float* A, int row_A, int col_A, float* B, int row_B, int col_B, float* C) {
    assert(col_A == row_B);              // && row_A == col_B
                                         //由矩阵相乘，要求f2=s1，以下用f2
    for (int i = 0; i < row_A; i++)      // i表示第i行
        for (int j = 0; j < col_B; j++)  // j表示第j列
            //  C[i*col_A + j] = 0;        //在这里 result[i][j] = result[i*f2+j];
            for (int p = 0; p < col_A; p++)
                C[i * col_B + j] += A[i * col_A + p] * B[p * col_B + j];
}
//对应点相乘
void multi(float* A, int row_A, int col_A, float* B, int row_B, int col_B, float* C) {
    assert(row_A == row_B && col_A == col_B);
    for (int i = 0; i < row_A; i++)
        for (int j = 0; j < col_A; j++)
            C[col_A * i + j] = A[col_A * i + j] * B[col_A * i + j];
}

void winograd1(float* g, float* d, float* result) {
    float Gg[12] = {0};
    float U[16]={0};
    float BTd[16] = {0};
    float V[16] = {0};
    float UV[16] = {0};
    float ATUV[8] = {0};
    
    dot(G, 4, 3, g, 3, 3, Gg);
    dot(Gg,4,3,GT,3,4,U);
    dot(BT, 4, 4, d, 4, 4, BTd);
    dot(BTd, 4, 4, B, 4, 4, V);
    multi(U, 4, 4, V, 4, 4, UV);
    dot(AT, 2, 4, UV, 4, 4, ATUV);
    dot(ATUV, 2, 4, A, 4, 2, result);
}

int main(int argc, char const *argv[]){
    float g[] = {1, 2, 3, 
                 4, 5, 6,
                 7, 8, 9};
    float d[] = {1,2,3,4,
                 5,6,7,8,
                 9,10,11,12,
                 13,14,15,16};
    float result[4]={0};
    winograd1(g, d, result);
    printf("winograd1's sample result: %f, %f, %f, %f\r\n", result[0], result[1], result[2], result[3]);
    return 0;
}
