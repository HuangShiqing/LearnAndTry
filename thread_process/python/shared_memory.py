#!/usr/bin/python3
# -*- coding: utf-8 -*-
from multiprocessing import Process, shared_memory, Array
import ctypes
import time
import numpy as np

# using SharedMemory
def process_sharedmemory_producer(i, shm_np):
    time.sleep(2)
    while True:
        print("process_{}: ".format(str(i)))        
        rand_np = np.random.rand(shape=shape, dtype=np.uint8)

        shm_np[:] = rand_np

        time.sleep(2)

def process_sharedmemory_consumer(i, shm_np, shm_name):
    time.sleep(2)
    while True:
        print("process_{}: ".format(str(i)))
        
        # existing_shm = shared_memory.SharedMemory(name=shm_name)
        # c = np.ndarray([416, 416, 3], dtype=np.uint8, buffer=existing_shm.buf)        
        print("shm_np[0,0,0] = ", shm_np[0,0,0])

        time.sleep(2)


# using Array
def process_array_producer(i, shared_array, shape):
    time.sleep(2)
    while True:
        print("process_{}: ".format(str(i)))        
        rand_np = np.random.rand(shape=shape, dtype=np.uint8)

        with shared_array.get_lock():
            # shared_np = np.frombuffer(shared_array.get_obj()).reshape(shape)
            shared_np = np.ctypeslib.as_array(shared_array.get_obj()).reshape(shape) # no data copying
            shared_np[:] = rand_np[:] # data copying

        time.sleep(2)

def process_array_consumer(i, shared_array):
    time.sleep(2)
    while True:
        print("process_{}: ".format(str(i)))        

        with shared_array.get_lock():
            # shared_np = np.frombuffer(shared_array.get_obj()).reshape(shape)
            shared_np = np.ctypeslib.as_array(shared_array.get_obj()).reshape(shape) # no data copying
            print("shared_np[0,0,0] = ", shared_np[0,0,0])

        time.sleep(2)

if __name__ == "__main__":
    
    shape = [416, 416, 3]

    # using SharedMemory
    shm = shared_memory.SharedMemory(create=True, size=416*416*3)
    shm_np = np.ndarray(shape, dtype=np.uint8, buffer=shm.buf)

    t = Process(target=process_sharedmemory_producer, args=(0, shm_np, ), name="fun_0")
    t.daemon = True
    t.start()
    print("process_0   started")

    t = Process(target=process_sharedmemory_consumer, args=(1, shm_np, shm.name, ), name="fun_1")
    t.daemon = True
    t.start()
    print("process_1   started")

    # using Array
    shared_array = Array(ctypes.c_uint8, shape[0]*shape[1]*shape[2])
    shared_np = np.ctypeslib.as_array(shared_array.get_obj()).reshape(shape) # no data copying

    t = Process(target=process_array_producer, args=(2, shared_array, shape, ), name="fun_2")
    t.daemon = True
    t.start()
    print("process_2   started")

    t = Process(target=process_array_consumer, args=(3, shared_array, shape, ), name="fun_3")
    t.daemon = True
    t.start()
    print("process_3   started")    

    print("main_process start sleeping")
    time.sleep(10)
    print("main process exit")
    exit()