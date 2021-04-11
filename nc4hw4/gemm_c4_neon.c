#include <arm_neon.h>  //要用neon内联函数必须要该头文件
#include <memory.h>
#define UP_DIV(x, y) (((x) + (y)-1) / (y))



void gemm_nt_c4_neon(int M, int N, int K, float* A, int lda, float* B, int ldb, float* C, int ldc) {
    // *A=指向卷积核参数的指针
    // *B=经过im2col的上一层featuremap
    // *C=指向卷积结果的指针
    int a = K / 4;                       // K=k*k*c,单个卷积核的空间尺寸大小
    int b = N;                           // N=输出feature map的w*h
    int c = M;                           // M=n,卷积核个数
    for (int i_c = 0; i_c < c; i_c++) {  // n
        float* A_c = A + K * i_c;
        float* B_c = B;
        float* C_c = C + N * i_c;
        for (int i_b = 0; i_b < b; i_b++) {  // wh*4
            float* A_b = A_c;
            float* B_b = B_c + K * i_b;
            float* C_b = C_c + i_b;

            float32x4_t in1x4, in2x4;
            float32x4_t outx4 = {0.0, 0.0, 0.0, 0.0};
            float* C_a = C_b;
            for (int i_a = 0; i_a < a; i_a++) {  // k/4
                float* A_a = A_b + 4 * i_a;
                float* B_a = B_b + 4 * i_a;
                in1x4 = vld1q_f32(A_a);
                in2x4 = vld1q_f32(B_a);
                outx4 = vmlaq_f32(outx4, in1x4, in2x4);
            }
            *C_a = vgetq_lane_f32(outx4, 0) + vgetq_lane_f32(outx4, 1) + vgetq_lane_f32(outx4, 2) +
                   vgetq_lane_f32(outx4, 3);
            // outx2 = vpadd_f32(outx4[0], outx4[1]);
            // outx1 = vadd_f32(outx2[0], outx2[1]);
            // vst1q_f32(outx1, C_a);
        }
    }
}

void gemm_nn_c4_neon(int M, int N, int K, float* A, int lda, float* B, int ldb, float* C, int ldc) {
    // *A=指向卷积核参数的指针
    // *B=经过im2col的上一层featuremap
    // *C=指向卷积结果的指针
    int a = K / 4;                       // K=k*k*c,单个卷积核的空间尺寸大小
    int b = N;                           // N=输出feature map的w*h
    int c = M;                           // M=n,卷积核个数
    for (int i_c = 0; i_c < c; i_c++) {  // n
        float* A_c = A + K * i_c;
        float* B_c = B;
        float* C_c = C + N * i_c;
        for (int i_b = 0; i_b < b; i_b++) {  // wh*4
            float* A_b = A_c;
            float* B_b = B_c + 4 * i_b;
            float* C_b = C_c + i_b;

            float32x4_t in1x4, in2x4;
            float32x4_t outx4 = {0.0, 0.0, 0.0, 0.0};
            float* C_a = C_b;
            for (int i_a = 0; i_a < a; i_a++) {  // k/4
                float* A_a = A_b + 4 * i_a;
                float* B_a = B_b + 4 * N * i_a;
                in1x4 = vld1q_f32(A_a);
                in2x4 = vld1q_f32(B_a);
                outx4 = vmlaq_f32(outx4, in1x4, in2x4);
            }
            *C_a = vgetq_lane_f32(outx4, 0) + vgetq_lane_f32(outx4, 1) + vgetq_lane_f32(outx4, 2) +
                   vgetq_lane_f32(outx4, 3);
            // outx2 = vpadd_f32(outx4[0], outx4[1]);
            // outx1 = vadd_f32(outx2[0], outx2[1]);
            // vst1q_f32(outx1, C_a);

            // float* C_a = C_b;
            // //TODO:clear q2
            // for (int i_a = 0; i_a < a; i_a++) {  // k/4
            //     float* A_a = A_b + 4 * i_a;
            //     float* B_a = B_b + 4 * N * i_a;
            //     asm volatile(
            //         ".loop:\n"
            //         // "cbz             %[count], .return\n"
            //         // "subs            %[count], %[count], #1\n"
            //         "vld1.32         {q0}, [%[A_a]]!\n"
            //         "vld1.32         {q1}, [%[B_a]]!        @ for current set\n"
            //         "vmlaq.f32        q2, q0, q1         @ q2 += q0 * q1\n"
            //         "vpadd.f32        d6, d5, d4  "
            //         "vadd.f32         "
            //         "b               .loop\n"
            //         ".return:\n"
            //         // // "mov               %[dst], #0\n"//不需要函数的返回跳转
            //         // // "bx                lr\n"
            //         : // 解释返回参数,如[ dst ] "+r"(dst)，有个加号
            //         : [ A_a ] "r"(A_a), [ B_a ] "r"(B_a), [ C_a ] "r"(C_a), [ i_a ] "r"(i_a)// 解释输入参数
            //         // : "memory", "q0", "q1", "q3"// 不太懂，但是要加
            //     );
            // }
        }
    }
}