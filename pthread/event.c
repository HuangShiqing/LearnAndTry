#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  //getpid()

typedef struct {
  pthread_cond_t mID;
  pthread_mutex_t mQueryMutex;
  int mAutoReset;
  int mQuery;
} event_parameter;

event_parameter *event;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int g_count = 0;
int g_retrieved = 1;

pthread_cond_t cond;
void event_init(event_parameter *event_par, int autoreset) {
  event_par->mAutoReset = autoreset;  // 为1时退出阻塞后会重新准备下一次阻塞
  event_par->mQuery = 0;                       // 参数为0时会阻塞wait
  pthread_cond_init(&(event_par->mID), NULL);  // 需要一个mutex配合
  pthread_mutex_init(&(event_par->mQueryMutex), NULL);
}

void event_wake(event_parameter *event_par) {
  pthread_mutex_lock(&(event_par->mQueryMutex));
  event_par->mQuery = 1;
  pthread_cond_signal(&(event_par->mID));
  pthread_mutex_unlock(&(event_par->mQueryMutex));
}

int event_wait(event_parameter *event_par) {
  pthread_mutex_lock(&(
      event_par
          ->mQueryMutex));  // 为了保护下面的while条件的结果和wait结果是原子的，https://www.zhihu.com/question/24116967

  while (!event_par->mQuery)  // TODO:为了啥
    pthread_cond_wait(
        &(event_par->mID),
        &(event_par
              ->mQueryMutex));  // 会先unlock，然后加入唤醒队列，允许别的线程>进入wait，直到被唤醒后再lock

  if (event_par->mAutoReset)  //自动使能准备下一次阻塞
    event_par->mQuery = 0;

  pthread_mutex_unlock(&(event_par->mQueryMutex));
  return 1;
}

void *consumer_thread(void *arg) {
  while (1) {
    printf("consumer start to wait\r\n");
    event_wait(event);
    pthread_mutex_lock(&mutex);  // 上锁失败代表别的线程在使用，则当前线程阻塞
    printf("g_count consumer receive: %d\r\n", g_count);
    const int retrieved = g_retrieved;
    g_retrieved = 1;
    pthread_mutex_unlock(&mutex);

    if (retrieved == 1) continue;
    printf("g_count consumer after sub=%d\r\n", --g_count);
  }
}

int main() {
  event = (event_parameter *)malloc(sizeof(event_parameter));
  printf("start\r\n");
  event_init(event, 1);
  printf("end\r\n");
  pthread_t process_tid1;
  int r = pthread_create(&process_tid1, 0, consumer_thread, (void *)event);
  if (r != 0) printf("Thread creation failed");
  while (1) {
    pthread_mutex_lock(&mutex);  // 上锁失败代表别的线程在使用，则当前线程阻塞
    printf("g_count producer after add=%d\r\n", ++g_count);
    g_retrieved = 0;  // 刚生产出来所以消费者没有收到
    pthread_mutex_unlock(&mutex);
    event_wake(event);
    sleep(2);
  }
}