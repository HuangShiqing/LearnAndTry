#!/usr/bin/python3
# -*- coding: utf-8 -*-
from multiprocessing import Process, Manager
import time

## 二: Manager
# 2.1: 可管理多种数据类型, 包括list 、 dict 、 Namespace 、 Lock 、 RLock 、 Semaphore 、 BoundedSemaphore 、 Condition 、 Event 、 Barrier 、 Queue 、 Value 和 Array
# 2.2: 比使用共享内存慢(不知道如何证明)

def process_fun(i, d, l):
    time.sleep(2)
    while True:
        print("process_{}: ".format(str(i)))
        print("manager dict['0']: {}, dict['1']: {}, dict['2']: {}".format(d["0"], d["1"], d["2"]))
        print("manager list[0]: {}, list[1]: {}, list[2]: {}\r\n".format(l[0], l[1], l[2]))

        d["0"] += "a"
        d["1"] += "b"
        d["2"] += "c"

        l[0] += "a"
        l[1] += "b"
        l[2] += "c"

        time.sleep(2)

if __name__ == "__main__":
    thread_num = int(input("input thread number: "))

    manager = Manager() # 定义管理器
    d = manager.dict({"0":"a", "1":"b", "2":"c"})
    l = manager.list(["a", "b", "c"])
    for i in range(thread_num):
        t = Process(target=process_fun, args=(i, d, l, ), name="fun_"+str(i))
        t.daemon = True
        t.start()
        print("process_"+str(i)+"   started")

    print("main_process start sleeping")
    time.sleep(10)
    print("main process exit")
    exit()