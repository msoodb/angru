#include <_thread.h>

#include <iostream>
#include <pthread.h>

#include "_math.h"


void * _thread::PrintHello(void *threadid)
{
  long tid;
  tid = (long) threadid;
  std::cout<<"Hello Wormald! Thread ID: "<<tid<<"\n";
  pthread_exit(NULL);
}

void * _thread::CalcFib(void *threadid)
{
  int n = 44;
  long tid;
  tid = (long) threadid;
  // /long long j = _math::fibonacci(n);
  std::cout<<"fibonacci ("<<n<<") is: "<<_math::fibonacci(n)<<"\n";
  pthread_exit(NULL);
}

void _thread::useThread2()
{
  /*pthread_t threads[NUM_THREADS];
  int rc;
  int i;

  for(i=0; i<NUM_THREADS; i++)
  {
    std::cout <<"main() : creating thread : "<< i << std::endl;
    rc = pthread_create(&threads[i], NULL, CalcFib, (void *)i);

    if(rc){
      std::cout << "Error : unable to create thread : " << rc <<std::endl;
      exit(-1);
    }
  }
  pthread_exit(NULL);*/
}
void _thread::useThread()
{
  /*pthread_t threads[NUM_THREADS];
  int rc;
  int i;

  for(i=0; i<NUM_THREADS; i++)
  {
    std::cout <<"main() : creating thread : "<< i << std::endl;
    rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);

    if(rc){
      std::cout << "Error : unable to create thread : " << rc <<std::endl;
      exit(-1);
    }
  }
  pthread_exit(NULL);*/
}

/*pthread_t threads[NUM_THREADS];
int rc;
int i;

for(i=0; i<NUM_THREADS; i++)
{
  std::cout <<"main() : creating thread : "<< i << std::endl;
  rc = pthread_create(&threads[i], NULL, CalcFib, (void *)i);

  if(rc){
    std::cout << "Error : unable to create thread : " << rc <<std::endl;
    exit(-1);
  }
}
pthread_exit(NULL);
*/
