#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// 思路三: 结论公式2与固定已知系数的加法
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

void winograd5_transforme_g(float* g, float* transformed_g) {
    float Gg[12] = {0};

    dot(G, 4, 3, g, 3, 3, Gg);  //先计算得到U=GgGT
    dot(Gg, 4, 3, GT, 3, 4, transformed_g);
}

void winograd5(float* U, float* d, float* result) {
    float BTd[16] = {0};
    float V[16] = {0};
    float UV[16] = {0};
    float ATUV[8] = {0};

    // start dot(BT, 4, 4, d, 4, 4, BTd);
    BTd[0] = d[0] - d[8];
    BTd[1] = d[1] - d[9];
    BTd[2] = d[2] - d[10];
    BTd[3] = d[3] - d[11];

    BTd[4] = d[4] + d[8];
    BTd[5] = d[5] + d[9];
    BTd[6] = d[6] + d[10];
    BTd[7] = d[7] + d[11];

    BTd[8] = -d[4] + d[8];
    BTd[9] = -d[5] + d[9];
    BTd[10] = -d[6] + d[10];
    BTd[11] = -d[7] + d[11];

    BTd[12] = d[4] - d[12];
    BTd[13] = d[5] - d[13];
    BTd[14] = d[6] - d[14];
    BTd[15] = d[7] - d[15];
    // end dot(BT, 4, 4, d, 4, 4, BTd);

    // start dot(BTd, 4, 4, B, 4, 4, V);
    V[0] = BTd[0] - BTd[2];
    V[4] = BTd[4] - BTd[6];
    V[8] = BTd[8] - BTd[10];
    V[12] = BTd[12] - BTd[14];

    V[1] = BTd[1] + BTd[2];
    V[5] = BTd[5] + BTd[6];
    V[9] = BTd[9] + BTd[10];
    V[13] = BTd[13] + BTd[14];

    V[2] = -BTd[1] + BTd[2];
    V[6] = -BTd[5] + BTd[6];
    V[10] = -BTd[9] + BTd[10];
    V[14] = -BTd[13] + BTd[14];

    V[3] = BTd[1] - BTd[3];
    V[7] = BTd[5] - BTd[7];
    V[11] = BTd[9] - BTd[11];
    V[15] = BTd[13] - BTd[15];
    // end dot(BTd, 4, 4, B, 4, 4, V);

    multi(U, 4, 4, V, 4, 4, UV);

    // start dot(AT, 2, 4, UV, 4, 4, ATUV);
    ATUV[0] = UV[0] + UV[4] + UV[8];
    ATUV[1] = UV[1] + UV[5] + UV[9];
    ATUV[2] = UV[2] + UV[6] + UV[10];
    ATUV[3] = UV[3] + UV[7] + UV[11];
    
    ATUV[4] = UV[4] - UV[8] - UV[12];
    ATUV[5] = UV[5] - UV[9] - UV[13];
    ATUV[6] = UV[6] - UV[10] - UV[14];
    ATUV[7] = UV[7] - UV[11] - UV[15];
    // end dot(AT, 2, 4, UV, 4, 4, ATUV);

    // start dot(ATUV, 2, 4, A, 4, 2, result);
    result[0] += (ATUV[0] + ATUV[1] + ATUV[2]);
    result[2] += (ATUV[4] + ATUV[5] + ATUV[6]);
    result[1] += (ATUV[1] - ATUV[2] - ATUV[3]);
    result[3] += (ATUV[5] - ATUV[6] - ATUV[7]);
    // end dot(ATUV, 2, 4, A, 4, 2, result);
}

int main(int argc, char const* argv[]) {
    float g[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    float d[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    float result[4] = {0};

    float* transformed_g = calloc(16, sizeof(float));
    winograd5_transforme_g(g, transformed_g);
    winograd5(transformed_g, d, result);

    printf("winograd5's sample result: %f, %f, %f, %f\r\n", result[0], result[1], result[2], result[3]);
    return 0;
}
