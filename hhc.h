#ifndef HHC_H
#define HHC_H
#include "test.h"

int in = 0;
int out = 0;
int buff[M] = {0};
int buffer=0;
int product_id = 0;
int consumer_id = 0;
int product_sum=0;
int consumer_sum=0;
struct timeval start;
struct timeval end1;
unsigned long timer;

// 同步信号量，作用:当缓冲区满了时阻止生产者放产品。表示空闲缓冲区的数目
sem_t empty_sem;
// 同步信号量，作用:当缓冲区没产品时阻止消费者消费。表示缓冲区可供消费多数目。
sem_t full_sem;
// 互斥信号量，作用:一次只有一个线程访问缓冲
pthread_mutex_t mutex;

void print()
{
    for(int i = 0; i < M; i++)
          std::cout<<buff[i]<<" ";
}

// 生产者方法(单缓冲)
void *product1(void * arg)
{
    int id = ++product_id;
    int t=*(int *)arg;
    while(1)
    {
        sleep(t);
        // 每次调用sem_wait(sem_t*），信号量减一
        sem_wait(&empty_sem);
        pthread_mutex_lock(&mutex);
        gettimeofday(&end1,NULL);
        product_sum++;
        timer = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
        std::cout<<"time:"<<timer<<"\t生产者编号:"<<id<<"\t生产总量:"<<product_sum<<endl;
        buffer=1;
        pthread_mutex_unlock(&mutex);
        // 每次调用sem_post(sem_t*)，信号量加一
        sem_post(&full_sem);
    }
}

// 生产者方法(多缓冲)
void *product(void * arg)
{
    int id = ++product_id;
    int t=*(int *)arg;
    while(1)
    {
        sleep(t);
        sem_wait(&empty_sem);
        pthread_mutex_lock(&mutex);
        gettimeofday(&end1,NULL);
        in = in % M;
        product_sum++;
        timer = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
        std::cout<<"time:"<<timer<<"\t生产者编号:"<<id<<"\t缓冲区:";
        buff[in] = 1;
        print();
        std::cout<<"\t生产总量:"<<product_sum<<endl;
        ++in;
        pthread_mutex_unlock(&mutex);
        sem_post(&full_sem);
    }
}


// 消费者方法(单缓冲)
void *consumer1(void *arg)
{
    int id = ++consumer_id;
    int t=*(int *)arg;
    while(1)
    {
        sleep(t);
        sem_wait(&full_sem);
        pthread_mutex_lock(&mutex);
        gettimeofday(&end1,NULL);
        consumer_sum++;
        timer = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
        std::cout<<"time:"<<timer<<"\t消费者编号:"<<id<<"\t消费总量:"<<consumer_sum<<endl;
        buffer=0;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty_sem);
    }
}

// 消费者方法(多缓冲)
void *consumer(void * arg)
{
    int id = ++consumer_id;
    int t=*(int *)arg;
    while(1)
    {
        sleep(t);
        sem_wait(&full_sem);
        pthread_mutex_lock(&mutex);
        gettimeofday(&end1,NULL);
        consumer_sum++;
        out = out%M;
        timer = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
        std::cout<<"time:"<<timer<<"\t消费者编号:"<<id<<"\t缓冲区:";
        buff[out] = 0;
        print();
        std::cout<<"\t消费总量:"<<consumer_sum<<endl;
        ++out;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty_sem);
    }
}

// 单缓冲
void f2(int N1,int N2,int T1,int T2,void *product,void *consumer)
{
    pthread_t id1[N1];
    pthread_t id2[N2];
    int i;
    int ret1[N1];
    int ret2[N2];
    // 用sem_init(); 初始化empty_sem型变量，并设置初始信号量为 1.第二个参数为0表示不应用于其他进程。
    int ini1 = sem_init(&empty_sem, 0, 1);
    // 用sem_init(); 初始化full_sem型变量，并设置初始信号量为 0.第二个参数为0表示不应用于其他进程。
    int ini2 = sem_init(&full_sem, 0, 0);
    //初始化互斥信号量，pthread_mutex_init()函数是以动态方式创建互斥锁的，参数attr指定了新建互斥锁的属性。如果参数attr为NULL，则使用默认的互斥锁属性，默认属性为快速互斥锁
    int ini3 = pthread_mutex_init(&mutex, NULL);

    for(i = 0; i < N1; i++){
        // 第一个参数为指向线程标识符的指针.第二个参数用来设置线程属性.第三个参数是线程运行函数的地址。 最后一个参数是运行函数的参数
        ret1[i] = pthread_create(&id1[i], NULL, (void*(*)(void *))product,&T1);
    }

    for(i = 0; i < N2; i++){
        ret2[i] = pthread_create(&id2[i], NULL, (void*(*)(void *))consumer,&T2);
    }

    for(i = 0; i < N1; i++){
        pthread_join(id1[i],NULL);
    }

    for(i = 0; i < N2; i++){
        pthread_join(id2[i],NULL);
    }
    exit(0);

}

// 多缓冲
void f1(int N1,int N2,int T1,int T2,void *product,void *consumer)
{
    pthread_t id1[N1];
    pthread_t id2[N2];
    int i;
    int ret1[N1];
    int ret2[N2];

    int ini1 = sem_init(&empty_sem, 0, M);
    int ini2 = sem_init(&full_sem, 0, 0);
    if(ini1 && ini2 != 0){
        exit(1);
    }

    int ini3 = pthread_mutex_init(&mutex, NULL);
    if(ini3 != 0)
    {
        exit(1);
    }

    for(i = 0; i < N1; i++)
    {
        ret1[i] = pthread_create(&id1[i], NULL, (void*(*)(void *))product,&T1);
        if(ret1[i] != 0)
        {
                exit(1);
        }
    }

    for(i = 0; i < N2; i++)
    {
        ret2[i] = pthread_create(&id2[i], NULL, (void*(*)(void *))consumer, &T2);
        if(ret2[i] != 0)
        {
                exit(1);
        }
    }

    for(i = 0; i < N1; i++)
    {
        pthread_join(id1[i],NULL);
    }

    for(i = 0; i < N2; i++)
    {
        pthread_join(id2[i],NULL);
    }
    exit(0);
}


#endif // HHC_H
