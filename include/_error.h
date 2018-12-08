#ifndef INC_ERROR_H
#define INC_ERROR_H

#include <stdexcept>
#include <string>

class _error : public std::runtime_error {
   public:
      _error( const std::string & emsg )
         : std::runtime_error( emsg ) {
      }
};
#endif
