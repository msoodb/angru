#ifndef ANGRU_SIGNAL_H_
#define ANGRU_SIGNAL_H_

#include <iostream>
#include <csignal>

class _signal
{
   public:
    static void signalHandler( int );
};

#endif // ANGRU_SIGNAL_H_
