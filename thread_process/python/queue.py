#!/usr/bin/python3
# -*- coding: utf-8 -*-
from multiprocessing import Process, Queue
import time

def process_fun_producer(i, q):
    time.sleep(2)
    while True:
        print("process_{}: ".format(str(i)))        
        q.put(["a", "b"]) 
        print("send\r\n")

        time.sleep(2)

def process_fun_consumer(i, q):
    time.sleep(2)
    while True:
        print("process_{}: ".format(str(i)))
        obj = q.get()
        print("get: ", obj, "\r\n")

        time.sleep(2)

if __name__ == "__main__":
    q = Queue()
    t = Process(target=process_fun_producer, args=(0, q), name="fun_0")
    t.daemon = True
    t.start()
    print("process_0   started")

    t = Process(target=process_fun_consumer, args=(1, q), name="fun_1")
    t.daemon = True
    t.start()
    print("process_1   started")

    print("main_process start sleeping")
    time.sleep(10)
    print("main process exit")
    exit()