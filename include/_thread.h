#ifndef INC_THREAD_H
#define INC_THREAD_H

#include <iostream>
#include <pthread.h>

#define NUM_THREADS 20

class _thread
{
public:
  static void *PrintHello(void *threadid);
  static void *CalcFib(void *threadid);
  static void useThread();
  static void useThread2();
};
#endif
