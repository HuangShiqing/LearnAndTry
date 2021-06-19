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
pthread_mutex_t mRingMutex = PTHREAD_MUTEX_INITIALIZER;
int g_count = 0;
int g_retrieved = 1;

pthread_cond_t cond;
void event_init(event_parameter *event_par, int autoreset) {
  event_par->mAutoReset = autoreset;  // 为1时退出阻塞后会重新准备下一次阻塞
  event_par->mQuery = 0;                       // 参数为0时会阻塞wait
  pthread_cond_init(&(event_par->mID), NULL);  // 总是需要一个mutex配合使用
  pthread_mutex_init(&(event_par->mQueryMutex), NULL);
}

void event_wake(event_parameter *event_par) {
  pthread_mutex_lock(&(event_par->mQueryMutex));
  event_par->mQuery = 1;
  pthread_cond_signal(&(event_par->mID));
  pthread_mutex_unlock(&(event_par->mQueryMutex));
}

int event_wait(event_parameter *event_par) {
  pthread_mutex_lock(&(event_par->mQueryMutex));  // 为了保护下面的while条件的结果和wait结果是原子的，https://www.zhihu.com/question/24116967

  while (!event_par->mQuery)  // 为了防止虚假唤醒https://www.zhihu.com/question/271521213
    pthread_cond_wait(&(event_par->mID), &(event_par->mQueryMutex));  // 会先unlock，然后加入唤醒队列，允许别的线程>进入wait，直到被唤醒后再lock

  if (event_par->mAutoReset)  //自动使能准备下一次阻塞
    event_par->mQuery = 0;

  pthread_mutex_unlock(&(event_par->mQueryMutex));
  return 1;
}

static const uint32_t NUM_RINGBUFFERS = 16;
void *mRingbufferCPU[NUM_RINGBUFFERS];
int mLatestRingbuffer = 0;
int mLatestRetrieved = 0;//生产者产生新数据后置0，消费者获取数据后置1 TODO:有何用

void *consumer_thread(void *arg) {
  while (1) {//消费者主循环
    // wait until a new frame is recieved
	event_wait(event);

    // get the latest ringbuffer
	pthread_mutex_lock(&mRingMutex);
	const uint32_t latest = mLatestRingbuffer;
	const int retrieved = mLatestRetrieved;
	mLatestRetrieved = 1;//TODO:有何用
	pthread_mutex_lock(&mRingMutex);

    // skip if it was already retrieved
	if( retrieved )
		continue;

    float use[10*10]={0};//接收区
    memcpy(use,mRingbufferCPU[latest],10*10*sizeof(float));//接受，即消费行为
    //TODO:如果消费者运行慢，如memcpy慢，生产者已经生产了一圈又回到了这里，是否会发生不安全行为

  }
}

  

int main() {
  //malloc ringbuffer
  for (int i = 0; i < NUM_RINGBUFFERS; i++)
    mRingbufferCPU[i] = malloc(10 * 10 * sizeof(float));

  //事件
  event = (event_parameter *)malloc(sizeof(event_parameter));
  event_init(event, 1);

  //create消费者线程
  pthread_t process_tid1;
  int r = pthread_create(&process_tid1, 0, consumer_thread, (void *)event);
  if (r != 0) printf("Thread creation failed");

  //生产者线程主循环
  while (1) {
    float *original_data = (float *)malloc(10 * 10 * sizeof(float));  //模拟产生新数据
    const uint32_t nextRingbuffer = (mLatestRingbuffer + 1) % NUM_RINGBUFFERS;  //找到列表的下一个位置
    memcpy(mRingbufferCPU[nextRingbuffer], original_data, 10 * 10 * sizeof(float));  //拷贝到下一个位置，到此，数据已更新，但还未对外公布
    free(original_data);//释放原始数据

    // update and signal sleeping threads
    pthread_mutex_lock(&mRingMutex);//保证原子操作
    mLatestRingbuffer = nextRingbuffer;//对外公布
    mLatestRetrieved = 0;//TODO:有何用
    pthread_mutex_unlock(&mRingMutex);
    event_wake(event);//唤醒消费者进行消费

    sleep(2);
  }
}