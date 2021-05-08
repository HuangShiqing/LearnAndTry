#ifndef __WINOGRAD1_H__
#define __WINOGRAD1_H__

void im2col_winograd1(float* data_im, int channels, int height, int width, int ksize, int stride, int m, int r,
                      float* data_col);
void winograd1_2d(float* U, float* d, float* result);
void convolutional_winograd1(float* g, float* d, float* result, int height, int width, int channels, int n, int m,
                             int r);
void col2im_winograd1(float* temp_c, int n, int height, int width, int ksize, int stride, int pad, int m, float* c);

#endif /* __WINOGRAD1_H__ */