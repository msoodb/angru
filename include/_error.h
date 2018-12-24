#ifndef ANGRU_ERROR_H_
#define ANGRU_ERROR_H_

#include <stdexcept>
#include <string>

class _error : public std::runtime_error {
   public:
      _error( const std::string & emsg )
         : std::runtime_error( emsg ) {
      }
};

#endif // ANGRU_ERROR_H_
