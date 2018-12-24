#include <_signal.h>

#include <iostream>

void _signal::signalHandler( int signum )
{
  std::cout <<"Interrupt signal ("<<signum<<") recieved.\n";
  exit(signum);
}

/*
// register signal SIGINT and signal handler
signal(SIGINT, _signal::signalHandler);
while(1)
{
  std::cout<<"Sleep ..........."<<std::endl;
  sleep(1);
}
*/
