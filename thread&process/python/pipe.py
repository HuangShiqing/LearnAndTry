#!/usr/bin/python3
# -*- coding: utf-8 -*-
from multiprocessing import Process, Pipe
import time

def process_fun_send(i, conn_send):
    time.sleep(2)
    while True:
        print("process_{}: ".format(str(i)))        
        conn_send.send(["a", "b"]) # 发送的对象必须是可以序列化的，过大的对象(接近32MiB)可能会引起ValueError异常
        conn_send.send_bytes(b'hi') 
        print("send\r\n")

        time.sleep(2)

def process_fun_recv(i, conn_recv):
    time.sleep(2)
    while True:
        print("process_{}: ".format(str(i)))
        obj = conn_recv.recv() # 该方法会一直阻塞直到接收到对象
        print("get: ", obj, "\r\n")
        obj = conn_recv.recv_bytes().decode('utf-8')
        print("get: ", obj, "\r\n")

        time.sleep(2)

if __name__ == "__main__":
    conn_send, conn_recv = Pipe()
    t = Process(target=process_fun_send, args=(0, conn_send), name="fun_0")
    t.daemon = True
    t.start()
    print("process_0   started")

    t = Process(target=process_fun_recv, args=(1, conn_recv), name="fun_1")
    t.daemon = True
    t.start()
    print("process_1   started")

    print("main_process start sleeping")
    time.sleep(10)
    print("main process exit")
    exit()