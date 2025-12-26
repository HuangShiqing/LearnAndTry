#include <stdio.h>
#include <cmath>
#include <cuda.h>
#include <algorithm>
#include <random>    // std::default_random_engine
#include <ctime>     // std::time


#define CUDA_CHECK(call)                                                       \
    do {                                                                       \
        cudaError_t err = call;                                                \
        if (err != cudaSuccess) {                                              \
            printf("CUDA Error: \n");                                          \
            printf("    File:       %s\n", __FILE__);                          \
            printf("    Line:       %d\n", __LINE__);                          \
            printf("    Error Code: %d\n", err);                               \
            printf("    Error Text: %s\n", cudaGetErrorString(err));           \
            exit(1);                                                           \
        }                                                                      \
    } while (0)
#define CUBLAS_CHECK(call)                                                     \
    do {                                                                       \
        cublasStatus_t err = call;                                             \
        if (err != CUBLAS_STATUS_SUCCESS) {                                    \
            printf("cuBLAS Error: \n");                                        \
            printf("    File:       %s\n", __FILE__);                          \
            printf("    Line:       %d\n", __LINE__);                          \
            printf("    Error Code: %d\n", err);                               \
            printf("    Error Text: %s\n", cublasGetStatusString(err));        \
            exit(1);                                                           \
        }                                                                      \
    } while (0)

void random_matrix(float* input, int M, int N) {
  for(int i=0; i<M*N; ++i) {
    //input[i] = rand() / (float)RAND_MAX;
    input[i] = rand() % M*N;
    //input[i] = i;
  }
  input[0]=5;
  input[16]=5;
}

bool compare(float* input1, float* input2, int M, int N) {
  for(int i=0; i<M*N; ++i) {
    if(input1[i]!=input2[i]) {
      printf("i: %d, input1[%d]: %f, input2[%d]: %f\n", i, i, input1[i], i, input2[i]);
      return false;
    }
  }
  return true;
}

bool compare2(float* input1, float* input2, int M, int N, float atol = 1e-5, float rtol = 1e-5) {
  for(int i=0; i<M*N; ++i) {
    //if(input1[i]!=input2[i]) {
    if (std::abs(input1[i] - input2[i]) > atol + rtol * std::abs(input2[i])) {
      printf("i: %d, input1[%d]: %f, input2[%d]: %f\n", i, i, input1[i], i, input2[i]);
      return false;
    }
  }
  return true;
}

template<typename type>
__device__ void swap(type& v1, type& v2){
  type t = v1;
  v1 = v2;
  v2 = t;
}

__global__ void bitonic_sort(float* d_src, int N, int N2) {
  int block_size = N2;
  int block_begin_offset = blockIdx.x * 2 * block_size;
  int thread_id = threadIdx.x;
  for(int k=2; k<=block_size;k*=2){
    for(int p=k/2;p>=1;p/=2) {
      int s = thread_id/p*2*p+thread_id%p;
      int offset=block_begin_offset + s;
      if(offset>N || offset+p>N){
        continue;
      }
      if(s/k%2==0) {
        if(d_src[offset]>d_src[offset+p]) {
          swap<float>(d_src[offset], d_src[offset+p]);
        }
      } else {
        if(d_src[offset]<d_src[offset+p]) {
          swap<float>(d_src[offset], d_src[offset+p]);
        }
      }
      __syncthreads();
    }
  }

  int k=2*block_size;
  for(int p=k/2;p>=1;p/=2) {
    int offset=block_begin_offset + thread_id/p*2*p+thread_id%p;
    if(d_src[offset]>d_src[offset+p]) {
      swap<float>(d_src[offset], d_src[offset+p]);
    }
    __syncthreads();
  }
}

//lower_bound
template <typename type>
__device__ int upper_equal(type* v, int n, type k)
{
    int left = 0, right = n;
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(v[mid] >= k) right = mid;
        else left = mid + 1;
    }
    return left;
//    int left = 0;
//    int right = n - 1;
//    int middle = (left + right) / 2;
//
//    while (left <= right)
//    {
//        if (v[middle] >= k){
//            if((middle-1)>=0){
//                if(v[middle-1]<k) {
//                    return middle;
//                } else {
//                    right = middle - 1;
//                }
//            } else {
//                return middle;
//            }
//        } else if (v[middle] < k)
//            left = middle + 1;
//
//        middle = (left + right) / 2;
//    }
//    return n;//所有数都比k小则k应该排在最右边(新序列长度是n+1)
}

//upper_bound
template <typename type>
__device__ int upper(type* v, int n, type k)
{
int left = 0, right = n;
while(left < right) {
    int mid = left + (right - left) / 2;
    if(v[mid] > k) right = mid;
    else left = mid + 1;
}
return left;
//    int left = 0;
//    int right = n - 1;
//    int middle = (left + right) / 2;
//
//    while (left <= right)
//    {
//        if (v[middle] > k){ //当[2,3,4],k==2, will insert right not left
//            if((middle-1)>=0){
//                if(v[middle-1]<k) {
//                    return middle;
//                } else {
//                    right = middle - 1;
//                }
//            } else {
//                return middle;
//            }
//        } else if (v[middle] <= k)
//            left = middle + 1;
//
//        middle = (left + right) / 2;
//    }
//    return n;//所有数都比k小则k应该排在最右边(新序列长度是n+1)
}

__global__ void merge(float* d_src,
                      float* d_dst,
                      int N1,//
                      int N2) {//输入有序的单段长度
  int block_begin_offset = blockIdx.x * 2 * N2;
  for(int i=threadIdx.x;i<N2;i+=blockDim.x){
    if(block_begin_offset+i>N1)
      return;

    float val = d_src[block_begin_offset+i];
    int offset2 = upper_equal<float>(d_src+block_begin_offset+N2, N2, val);
    d_dst[block_begin_offset+i+offset2] = val;

    val = d_src[block_begin_offset+i+N2];
    offset2 = upper<float>(d_src+block_begin_offset, N2, val);
    d_dst[block_begin_offset+i+offset2] = val;
  }
}

__global__ void split(float* d_src,
                      int* d_split_offset,
                      int N,
                      int N2,
                      int split_count) {
  float* d_src1 = d_src + blockIdx.x * 2 * N2;
  float* d_src2 = d_src + blockIdx.x * 2 * N2 + N2;

  int* offset1 = d_split_offset + blockIdx.x * 2 * split_count;
  int* offset2 = d_split_offset + blockIdx.x * 2 * split_count + split_count;

  for(int idx = threadIdx.x; idx < split_count/2; idx += blockDim.x) {
    int offset = threadIdx.x * N2/(split_count/2);
    offset1[threadIdx.x] = offset;
    offset1[split_count/2 + threadIdx.x] = upper_equal<float>(d_src1, N2, d_src2[offset]);
    
    offset2[threadIdx.x] = offset;
    offset2[split_count/2 + threadIdx.x] = upper_equal<float>(d_src2, N2, d_src1[offset]);
  }
}


__global__ void sort(int* d_split_offset,
                     int* d_split_offset_tmp,
                     int len,
                     int split_count) {
  int* offset_half1 = d_split_offset + blockIdx.x * split_count;
  int* offset_half2 = d_split_offset + blockIdx.x * split_count + split_count/2;
  
  for(int i=threadIdx.x;i<split_count/2;i+=blockDim.x){
    if(blockIdx.x * split_count + i > len)
      return;

    int val = offset_half1[i];
    int offset2 = upper_equal<int>(offset_half2, split_count/2, val);
    d_split_offset_tmp[blockIdx.x * split_count + i + offset2] = val;

    val = offset_half2[i];
    offset2 = upper<int>(offset_half1, split_count/2, val);
    d_split_offset_tmp[blockIdx.x * split_count + i + offset2] = val;
  }
}

__global__ void merge2(float* d_src,
                       int* d_split_offset_ordered,
                       float* d_dst,
                       int N2,
                       int split_count) {
  int block_begin_offset = blockIdx.y * 2 * N2; //每个block.y负责2个N2长的有序数组
  int block_split_offset = blockIdx.y * 2 * split_count + blockIdx.x;

  int split_offset_lod1 = d_split_offset_ordered[block_split_offset]; 
  int split_offset_lod2 = N2; 
  if(blockIdx.x<split_count-1) {
    split_offset_lod2 = d_split_offset_ordered[block_split_offset + 1]; 
  }

  int split2_offset_lod1 = d_split_offset_ordered[block_split_offset + split_count];
  int split2_offset_lod2 = N2;
  if(blockIdx.x<split_count-1) {
    split2_offset_lod2 = d_split_offset_ordered[block_split_offset + split_count + 1];     
  }

  int max_lod_len = max(split_offset_lod2-split_offset_lod1, split2_offset_lod2-split2_offset_lod1);

  for(int i=threadIdx.x; i<max_lod_len; i+=blockDim.x){
   if(i<split_offset_lod2-split_offset_lod1) { 
      float val = d_src[block_begin_offset+split_offset_lod1+i];
      int offset2 = upper_equal<float>(d_src+block_begin_offset+N2+split2_offset_lod1, split2_offset_lod2-split2_offset_lod1, val);
      d_dst[block_begin_offset+split_offset_lod1+split2_offset_lod1+i+offset2] = val;
      
    }

    if(i<split2_offset_lod2-split2_offset_lod1) {
      float val = d_src[block_begin_offset+N2+split2_offset_lod1+i];
      int offset2 = upper<float>(d_src+block_begin_offset+split_offset_lod1, split_offset_lod2-split_offset_lod1, val);
      d_dst[block_begin_offset+split_offset_lod1+split2_offset_lod1+i+offset2] = val;

    }
  }  

}

int main() {
  int N = 2048;//TODO:4096 not ok

  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);

  float* h_src = (float*)malloc(sizeof(float) * N);
  float* h_dst = (float*)malloc(sizeof(float) * N);
  float* h_dst_cpu = (float*)malloc(sizeof(float) * N);
  random_matrix(h_src, N, 1);
  // 随机数生成器
  //std::default_random_engine rng(static_cast<unsigned>(std::time(nullptr)));
  //std::default_random_engine rng(1);
  // shuffle 指针数组
  //std::shuffle(h_src, h_src + N, rng);

  float* d_src;
  float* d_dst;
  cudaMalloc((void**)&d_src, sizeof(float) * N);
  cudaMalloc((void**)&d_dst, sizeof(float) * N);
  cudaMemcpy(d_src, h_src, sizeof(float) * N, cudaMemcpyHostToDevice);

  memcpy(h_dst_cpu, h_src, N * sizeof(float));
  std::sort(h_dst_cpu, h_dst_cpu+N);

  //------------------------------v1
  cudaEventRecord(start, 0);
  int block_size = 128;//8;//双调里的单调长度
  int grid_size = ceil((float)N/(block_size*2));
  bitonic_sort<<<grid_size, block_size>>>(d_src, N, block_size);//inplace

  //cudaMemcpy(h_dst, d_src, sizeof(float) * N, cudaMemcpyDeviceToHost);
  //for(int i=0;i<32;i++) {
  //  printf("%d,", (int)h_dst[i]);
  //}
  //printf("\n\n");

  int new_grid_size;
  int N2 = block_size*2;//双调变成单调的长度
  int count=0;
  for(new_grid_size=grid_size/2; new_grid_size>0; new_grid_size/=2){
    merge<<<new_grid_size, block_size>>>(d_src, d_dst, N, N2);

  //printf("N2: %d\n", N2);
  //cudaMemcpy(h_dst, d_dst, sizeof(float) * N, cudaMemcpyDeviceToHost);
  //for(int i=0;i<32;i++) {
  //  printf("%d,", (int)h_dst[i]);
  //  if ((i + 1) % (2*N2) == 0){
  //      printf("\n");
  //  }
  //}
  //printf("\n\n");

   
    std::swap(d_src, d_dst);
    N2*=2;
    count++;
  }
  if(count%2==1) {//根据循环体执行奇偶数次决定最后是要swap一次保证最后输出存在dst里
    std::swap(d_src, d_dst);
  }
 
  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(h_dst, d_dst, sizeof(float) * N, cudaMemcpyDeviceToHost);

  bool result = compare2(h_dst, h_dst_cpu, 1, N);
  if (result)
    printf("gpu_v1 compare pass\n");
  else
    printf("gpu_v1 compare not pass, please check\n");

  float elapsed;
  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v1 cost: %f ms\n\n", elapsed);
  //-------------------------------v1

  //-------------------------------v2
  cudaMemcpy(d_src, h_src, sizeof(float) * N, cudaMemcpyHostToDevice);

  cudaEventRecord(start, 0); 
  block_size = 128;//debug=8
  grid_size = ceil((float)N/(block_size*2));
  bitonic_sort<<<grid_size, block_size>>>(d_src, N, block_size);

  //cudaMemcpy(h_dst, d_src, sizeof(float) * N, cudaMemcpyDeviceToHost);
  //printf("d_src: ");
  //for(int i=0;i<2*block_size*2;i++) {
  //  printf("%d,", (int)h_dst[i]);
  //}
  //printf("\n\n");

  count = 0;
  N2 = 2*block_size;//1个有序序列长度
  int split_len1 = 128;//=8;1次切分后的单位长度
  int split_len2 = 64;
  int split_count = N2/split_len1*2;//1个有序序列2次切分后的片数
  int total_split_count = split_count * grid_size;//所有有序序列2次切分后的总片数
  int* d_split_offset;
  int* d_split_offset_ordered;
  cudaMalloc((void**)&d_split_offset, sizeof(int) * total_split_count);
  cudaMalloc((void**)&d_split_offset_ordered, sizeof(int) * total_split_count);

  int* h_split_offset = (int*)malloc(sizeof(int) * total_split_count);

  int target_count = 0;
  int check_block_num = 1;
  for(new_grid_size=grid_size/2; new_grid_size>0; new_grid_size/=2){

    //if(count==target_count) {
    //  cudaMemcpy(h_dst, d_src, sizeof(float) * N, cudaMemcpyDeviceToHost);
    //  printf("N2: %d\n", N2);
    //  printf("new_grid_size: %d, split_count: %d\n", new_grid_size, split_count);
    //  printf("d_src:\n");
    //  for(int i=0;i<check_block_num*2*N2;i++) {
    //    printf("%d,", (int)h_dst[i]);
    //    if ((i + 1) % N2 == 0){
    //      printf("\n");
    //    }
    //  }
    //  printf("\n\n");
    //}

    split<<<new_grid_size, 128>>>(d_src, d_split_offset, N, N2, split_count);//每个block负责2个N2长的有序序列切分, 每个有序序列切分为split_count段.TODO:最后还是会一个block切分很多段

    //if(count==target_count) {
    //  cudaMemcpy(h_split_offset, d_split_offset, sizeof(int) * total_split_count, cudaMemcpyDeviceToHost);
    //  printf("split_offset:\n");
    //  for(int i=0;i<check_block_num*2*split_count;i++) {
    //    printf("%d,", (int)h_split_offset[i]);
    //    if ((i + 1) % split_count == 0){ 
    //      printf("\n");
    //    }
    //  }
    //  printf("\n\n");
    //}

    sort<<<new_grid_size * 2, 128>>>(d_split_offset, d_split_offset_ordered, total_split_count, split_count);

    //if(count==target_count) {
    //  cudaDeviceSynchronize();
    //  cudaMemcpy(h_split_offset, d_split_offset_ordered, sizeof(int) * total_split_count, cudaMemcpyDeviceToHost);
    //  printf("split_offset_ordered:\n");
    //  for(int i=0;i<check_block_num*2*split_count;i++) {
    //    printf("%d,", (int)h_split_offset[i]);
    //    if ((i + 1) % split_count == 0){
    //      printf("\n");
    //    }
    //  }
    //  printf("\n\n");
    //}

    merge2<<<dim3(split_count, new_grid_size), 128>>>(d_src, d_split_offset_ordered, d_dst, N2, split_count);//每个block负责2个段的合并

    //if(count==target_count) {
    //  cudaDeviceSynchronize();
    //  cudaMemcpy(h_dst, d_dst, sizeof(float) * N, cudaMemcpyDeviceToHost);
    //  printf("dst:\n");
    //  for(int i=0;i<check_block_num*2*N2;i++) {
    //    printf("%d,", (int)h_dst[i]);
    //    if ((i + 1) % N2 == 0){
    //      printf("\n");
    //    }
    //  }
    //  printf("\n\n");
    //}

    N2*=2;//1次合并后有序序列长度翻倍
    split_count*=2;//1次合并后有序序列2次切分后的片数也同样翻倍
    count++;
    std::swap(d_src, d_dst);
  }
  if(count%2==1) {//根据循环体执行奇偶数次决定最后是要swap一次保证最后输出存在dst里
    std::swap(d_src, d_dst);
  }

  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(h_dst, d_dst, sizeof(float) * N, cudaMemcpyDeviceToHost);

  result = compare2(h_dst, h_dst_cpu, 1, N);
  if (result)
    printf("gpu_v2 compare pass\n");
  else
    printf("gpu_v2 compare not pass, please check\n");

  cudaEventElapsedTime(&elapsed, start, stop);
  printf("gpu_v2 cost: %f ms\n\n", elapsed);

  cudaFree(d_split_offset);
  //-------------------------------v2
  free(h_src);
  free(h_dst);
  free(h_dst_cpu);
  cudaFree(d_src);
  cudaFree(d_dst);

  cudaEventDestroy(start);
  cudaEventDestroy(stop);
  return 0;
}
