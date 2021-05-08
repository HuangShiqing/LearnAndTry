#ifndef __WINOGRAD4_H__
#define __WINOGRAD4_H__

void transforme_g_winograd4(float* g, float* transformed_g, int c, int n);
void winograd4_1d(float* d, float* transformed_g, float* m);
void winograd4_2d(float* transformed_k, float* transformed_g, float* R);
void convolutional_winograd4(float* transformed_g, float* transformed_k, float* R, int height, int width, int channels,
                             int n, int m, int r);

#endif /* __WINOGRAD4_H__ */                             