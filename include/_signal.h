#ifndef INC_SIGNAL_H
#define INC_SIGNAL_H

#include <iostream>
#include <csignal>

class _signal
{
   public:
    static void signalHandler( int );
};
#endif
