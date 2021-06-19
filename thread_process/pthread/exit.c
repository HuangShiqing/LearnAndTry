#include <pthread.h>
#include <stdio.h>
#include <unistd.h>  //getpid()

void *thread_0(void *arg) {
  pid_t pid = getpid();
  pthread_t tid = pthread_self();
  for (int i = 0; i < 5; i++)
    printf("I am thread: %d, pid: %u, tid: 0x%x\r\n", *((int *)arg),
           (unsigned int)pid, (unsigned int)tid);
  return 0;  // 执行到线程函数的末尾会自动结束线程
}

void *thread_1(void *arg) {
  pid_t pid = getpid();
  pthread_t tid = pthread_self();
  for (int i = 0; i < 5; i++) {
    printf("I am thread: %d, pid: %u, tid: 0x%x\r\n", *((int *)arg),
           (unsigned int)pid, (unsigned int)tid);
    if (i == 3) pthread_exit(0);  // 自己先退出
  }
  return 0;  // 执行到线程函数的末尾会自动结束线程
}

void *thread_2(void *arg) {
  pid_t pid = getpid();
  pthread_t tid = pthread_self();
  while (1) {
    printf("I am thread: %d, pid: %u, tid: 0x%x\r\n", *((int *)arg),
           (unsigned int)pid, (unsigned int)tid);
    sleep(1);  // 有没有这个sleep在接受到pthread_cancel后都会终止该线程
  }
  return 0;  // 永远不会自己执行到这里
}

int main() {
  int num_thread = 5;
  int index[num_thread];
  pthread_t thread_tid[num_thread];

  index[0] = 0;
  printf("main() : 创建线程, %d\n", 0);
  int ret = pthread_create(&thread_tid[0], 0, thread_0, (void *)&(index[0]));
  if (ret != 0) printf("Thread creation failed");

  index[1] = 1;
  printf("main() : 创建线程, %d\n", 1);
  ret = pthread_create(&thread_tid[1], 0, thread_1, (void *)&(index[1]));
  if (ret != 0) printf("Thread creation failed");

  index[2] = 2;
  printf("main() : 创建线程, %d\n", 2);
  ret = pthread_create(&thread_tid[2], 0, thread_2, (void *)&(index[2]));
  if (ret != 0) printf("Thread creation failed");

  sleep(1);
  if (pthread_cancel(thread_tid[2]) == 0)  // 取消别的线程
    printf("send the cancel cmd to thread_2\r\n");
  pthread_exit(NULL);  // 退出主线程，不会影响别的线程
  return 0;            // 有了上面那句pthread_exit就不会执行到这句
}