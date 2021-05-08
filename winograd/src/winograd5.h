#ifndef __WINOGRAD5_H__
#define __WINOGRAD5_H__

void winograd5_2d(float* U, float* d, float* result);
void convolutional_winograd5(float* transformed_g, float* d, float* result, int height, int width, int channels, int n,
                             int m, int r);

#endif /* __WINOGRAD5_H__ */                             