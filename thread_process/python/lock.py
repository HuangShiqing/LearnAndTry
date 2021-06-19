#!/usr/bin/python3
# -*- coding: utf-8 -*-

from multiprocessing import Lock, Process
import time

global_num = 0

def process_fun(index, lock):
    global global_num

    time.sleep(2)
    while True:
        with lock:
            global_num+=1
            print("process_{}: ".format(str(index)), index)
            if global_num > 10:
                break
        time.sleep(1)

if __name__ == "__main__":
    thread_num = int(input("input thread number: "))

    lock = Lock()
    num = 0
    for i in range(thread_num):
        t = Process(target=process_fun, args=(i, lock, ), name="fun_"+str(i))
        t.daemon = True
        t.start()
        print("process_"+str(i)+"   started")

    print("main_process start sleeping")
    time.sleep(10)
    print("main process exit")
    exit()