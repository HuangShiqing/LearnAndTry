#ifndef __WINOGRAD2_H__
#define __WINOGRAD2_H__

void transforme_g_winograd2(float* g, float* transformed_g, int c, int n);
void winograd2_2d(float* U, float* d, float* result);
void convolutional_winograd2(float* transformed_g, float* d, float* result, int height, int width, int channels, int n,
                             int m, int r);

#endif /* __WINOGRAD2_H__ */                             