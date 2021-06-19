#!/usr/bin/python3
# -*- coding: utf-8 -*-
from multiprocessing import Process, Value, Array, Manager
import ctypes
import time
import numpy as np

## 一: Value和Array
# 1.1: Value和Array都是进程安全, 不用自己上锁
# 1.2: 共享变量可以定义成全局变量然后在进程函数里通过global引用

def process_fun(i, v, array):
# def process_fun(i):
#     global v, array, d, l
    time.sleep(2)
    while True:
        print("process_{}: ".format(str(i)))
        print("v: ", v.value)
        print("array[0]: {}, array[1]: {}, array[2]: {}".format(array[0], array[1], array[2]))

        v.value += 1

        array[0] += 1
        array[1] += 1
        array[2] += 1

        time.sleep(2)

if __name__ == "__main__":
    thread_num = int(input("input thread number: "))

    v = Value("i", 0)  # 定义共享变量
    array = Array("i", range(3)) # 定义共享数组
    for i in range(thread_num):
        t = Process(target=process_fun, args=(i, v, array, ), name="fun_"+str(i))
        # t = Process(target=process_fun, args=(i,), name="fun_"+str(i))
        t.daemon = True
        t.start()
        print("process_"+str(i)+"   started")


    print("main_process start sleeping")
    time.sleep(10)
    print("main process exit")
    exit()