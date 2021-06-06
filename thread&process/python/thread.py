#!/usr/bin/python3
# -*- coding: utf-8 -*-

# 官方文档 https://docs.python.org/zh-cn/3.7/library/threading.html
from threading import Thread
import time

def thread_fun(num):
    count = 0
    while True:
        count += num*1.33333*3.449*2.887/4.789
        num += 1  

if __name__ == "__main__":
    thread_num = int(input("input thread number: "))
    for i in range(thread_num):
        t = Thread(target=thread_fun, args=(i,), name="fun_"+str(i))
        t.daemon = True # 主线程不是守护线程，因此主线程创建的所有线程默认都是 daemon = False
                        # 守护线程有一个特征，如果所有的前台线程都死亡了，那么守护线程会自动死亡
        t.start()
        print("thread_"+str(i)+"   started")
    print("main_thread start sleeping")
    time.sleep(30)
    print("main thread exit")
    exit()# 唯一的前台线程退出, 剩下的守护线程也会自动退出