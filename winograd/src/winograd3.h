#ifndef __WINOGRAD3_H__
#define __WINOGRAD3_H__

void im2col_winograd3(float* data_im, int channels, int height, int width, int ksize, int stride, int m, int r,
                      float* data_col);
void winograd3_1d(float* d, float* g, float* m);
void winograd3_2d(float* transformed_k, float* g, float* R);
void convolutional_winograd3(float* g, float* transformed_k, float* R, int height, int width, int channels, int n,
                             int m, int r);       

#endif /* __WINOGRAD3_H__ */                                            