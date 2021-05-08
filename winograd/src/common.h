#ifndef __COMMON_H__
#define __COMMON_H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

extern float A[8];
extern float AT[8];
extern float B[16];
extern float BT[16];
extern float G[12];
extern float GT[12];

double what_time_is_it_now();
void dot(float* A, int row_A, int col_A, float* B, int row_B, int col_B, float* C);
void multi(float* A, int row_A, int col_A, float* B, int row_B, int col_B, float* C);
void compareResult(float* A, float* B, int len);

#endif /* __COMMON_H__ */