     .text
        .syntax   unified
        .align   4
        .global   gemm_nn_neon
        .thumb
        .thumb_func

gemm_nn_neon:
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @
        @  gemm_nn(int M, int N, int K, 
        @           @float ALPHA, 
        @           float *A, int lda, 
        @           float *B, int ldb,
        @           float *C, int ldc)
        @  r0: M=n,卷积核个数
        @  r1: N=输出feature map的w*h
        @  r2: K=k*k*c,单个卷积核的空间尺寸大小
        @      @ALPHA=1
        @  r3: *A=指向卷积核参数的指针
        @  
        @  r5: *B=经过im2col的上一层featuremap
        @  r6: ldb=N=输出feature map的w*h
        @  r7: *C=指向卷积结果的指针
        @
        @
        @  r13: sp
        @  r14: ld
        @  r15: pc
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        push	        {fp, lr}                @ 进入函数的基本操作
	add	        fp, sp, #4
	sub	        sp, sp, #24
	str	        r0, [fp, #-16]
	str	        r1, [fp, #-20]
	str	        r2, [fp, #-24]
	str	        r3, [fp, #-28]
.L_n_start:

.L_n_loop:
        ldr             r2, [fp, #-24]          @ 读取单个卷积核的空间尺寸大小        
.L_c_start:
        ldr             r5, [fp, #8]            @ 读取要进行卷积的featuremap的初始地址
.L_c_loop:
        ldr             r1, [fp, #-20]          @ 读取要进行卷积的featuremap的初始大小        
        ldr             r7, [fp, #16]           @ 读取卷积结果的初始地址    
.L_wh_start:        
        vld1.32         d0[0], [r3]!            @ 读卷积核
.L_wh_loop:
        and             r4, r1, #3              @ r4 = w*h % 4; calculate the residual loop
        asr             r6, r1, #2              @ r6 = w*h >> 2 = w*h / 4; calculate the main loop
        cbz             r4, .L_check_wh_mainloop
.L_wh_residualloop:        
        vld1.32         {d2[0]}, [r7]           @ 读取要保存的地址
        vmov.f32        d1, #0.0                @ 赋值为0
        vld1.32         {d1[0]}, [r5]!          @ 读要进行卷积的featuremap        
        vmla.f32        d2, d1, d0[0]           @ q2 += q1 * d0[0]
        vst1.32         {d2[0]}, [r7]!          @ 将结果从寄存器保存到内存中

        subs            r4, r4, #1              @ 需要进行的residual循环次数减一
        bgt             .L_wh_residualloop      @ 如果上一句subs没有更改状态寄存器的大于位，即r4-1仍然大于0,则继续循环
.L_check_wh_mainloop:
        cbz             r6, .L_check_c_loop
.L_wh_mainloop:
        vld1.32         {q2}, [r7]              @ 读取要保存的地址
        vld1.32         {q1}, [r5]!             @ 读要进行卷积的featuremap
        vmla.f32        q2, q1, d0[0]           @ q2 += q1 * d0[0]
        vst1.32         {q2}, [r7]!             @ 将结果从寄存器保存到内存中

        subs            r6, r6, #1              @ 需进行的循环数减1
        bgt             .L_wh_mainloop          @ 如果上一句subs没有更改状态寄存器的大于位，即r6-1仍然大于0，则继续循环
.L_check_c_loop:
        subs            r2, r2, #1              @ 需要进行的c循环次数减一
        bgt             .L_c_loop               @ 如果上一句subs没有更改状态寄存器的大于位，即r2-1仍然大于0,则继续循环
.L_c_return:

.L_check_n_loop:
        str             r7, [fp, #16]           @ 将更新的卷积结果地址保存
        subs            r0, r0, #1              @ 需要进行的n循环次数减一        
        bgt             .L_n_loop               @ 如果上一句subs没有更改状态寄存器的大于位，即r0-1仍然大于0，则继续循环                
.L_n_return:

.L_return:
        mov             r0, #0
        add	        sp, sp, #24             @ sp移到进入该函数的初始位置
        pop	        {fp, pc}
        