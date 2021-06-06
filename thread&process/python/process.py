#!/usr/bin/python3
# -*- coding: utf-8 -*-

# 官方文档 https://docs.python.org/zh-cn/3.7/library/multiprocessing.html
from multiprocessing import Process
import setproctitle

import time

def process_fun(num):
    setproctitle.setproctitle("process_"+str(num)) # 在子进程中设置进程名
    count = 0
    while True:
        count += num*1.33333*3.449*2.887/4.789
        num += 1  

if __name__ == "__main__":
    setproctitle.setproctitle("python main") # 设置进程名
    thread_num = int(input("input thread number: "))
    for i in range(thread_num):
        t = Process(target=process_fun, args=(i,), name="fun_"+str(i))
        t.daemon = True # 子进程是守护进程时, 才会在主进程退出时也退出
        t.start()
        # Process(target=process_fun, args=(i,), name="fun_"+str(i)).start() # 不设置daemon时上面三句等于该一句        
        print("process_"+str(i)+"   started")
    print("main_process start sleeping")
    time.sleep(10)
    print("main process exit")
    exit()