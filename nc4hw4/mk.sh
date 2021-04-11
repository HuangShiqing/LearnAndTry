#!/bin/bash
mode=$1

if [ ! -d "./Debug" ]; then
    mkdir Debug
fi

if [ "${mode}" == "debug" ]; then
    echo "[hsq] build for debug"
    gcc gemm_c4_neon.c -c -o ./Debug/gemm_c4_neon.o -mfpu=neon -mcpu=cortex-a53 -O0 -g 
    gcc gemm_neon.s -c -mfpu=neon -mcpu=cortex-a53 -o ./Debug/gemm_neon.o -O0 -g 
    gcc main.c ./Debug/gemm_neon.o ./Debug/gemm_c4_neon.o -o main -O0 -g 
else
    echo "[hsq] build for release"
    gcc gemm_c4_neon.c -c -o ./Debug/gemm_c4_neon.o -mfpu=neon -mcpu=cortex-a53 -Ofast 
    gcc gemm_neon.s -c -mfpu=neon -mcpu=cortex-a53 -o ./Debug/gemm_neon.o -Ofast
    gcc main.c ./Debug/gemm_neon.o ./Debug/gemm_c4_neon.o -o main
fi