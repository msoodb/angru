#ifndef ANGRU_SYSTEM_H_
#define ANGRU_SYSTEM_H_

#include <iostream>
#include <csignal>

namespace angru{
namespace system{
namespace localization{

void Setup();
void Output();
void Init();
void Sample();
void SampleII();

} // namespace localization

namespace exception{

class error : public std::runtime_error {
   public:
      error( const std::string & emsg )
         : std::runtime_error( emsg ) {
      }
};

} // namespace exception

namespace{

void signalHandler(int);
void *PrintHello(void *threadid);
void *CalcFib(void *threadid);
void useThread();
void useThread2();

} // namespace
} // namespace tools
} // namespace angru

#endif // ANGRU_SYSTEM_H_
