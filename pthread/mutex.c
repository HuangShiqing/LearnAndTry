#include <pthread.h>
#include <stdio.h>
#include <unistd.h>  //getpid()

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  //静态初始化互斥锁
int count = 0;

void *print_count(void *arg) {
  pid_t pid = getpid();
  pthread_t tid = pthread_self();
  for (int i = 0; i < 5; i++) {
    pthread_mutex_lock(&mutex);  // 上锁失败代表别的线程在使用，则当前线程阻塞
    count++;
    printf("I am thread: %d, pid: %u, tid: 0x%x count: %d\r\n", *((int *)arg),
           (unsigned int)pid, (unsigned int)tid, count);
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(0);
  return 0;  // 执行到线程函数的末尾会自动结束线程
}

int main() {
  int num_thread = 5;
  int index[num_thread];
  pthread_t thread_tid[num_thread];
  for (int i = 0; i < num_thread; i++) {
    index[i] = i;
    printf("main() : 创建线程, %d\n", i);
    int ret =
        pthread_create(&thread_tid[i], 0, print_count, (void *)&(index[i]));
    if (ret != 0) printf("Thread creation failed");
  }
  for (int i = 0; i < num_thread; i++)
    pthread_join(thread_tid[i], NULL);  // 阻塞主线程直到其他5个线程都退出
  pthread_exit(NULL);  // 退出运行main函数的主线程，该操作不影响其他5个线程
  return 0;  // 有了上面那句pthread_exit就不会执行到这句
}