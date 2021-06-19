#include <stdio.h>
#include <unistd.h>//getpid()
#include <pthread.h>

void *print_hello(void *arg)
{
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("I am thread: %d, pid: %u, tid: 0x%x\r\n", *((int *)arg), (unsigned int)pid, (unsigned int)tid);//先强制类型转换泛型指针，然后取指针指向的值
    return 0; // 执行到线程函数的末尾会自动结束线程
}

int main()
{
    int num_thread = 5;
    int index[num_thread];
    pthread_t thread_tid[num_thread];
    for (int i = 0; i < num_thread; i++)
    {
        index[i] = i;
        printf("main() : 创建线程, %d\n", i);
        int ret = pthread_create(&thread_tid[i], 0, print_hello, (void *)&(index[i]));
        if (ret != 0)
            printf("Thread creation failed");
    }

    pthread_exit(NULL);// 退出运行main函数的主线程，该操作不影响其他5个线程
    return 0;// 有了上面那句pthread_exit就不会执行到这句
}