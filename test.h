#ifndef TEST_H
#define TEST_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <sys/time.h>
#include <fstream>
#include <string>
#include <unistd.h>
using namespace std;
#define M 10

// 多线程相关操作头文件pthread.h
// 进程间通信-信号量头文件semaphore.h

class test
{
public:

    test();
    void config(int *N1,int *N2,int *T1,int *T2);
    void menu();

};
#endif // TEST_H







