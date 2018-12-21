// This is start of the header guard. _HTTPCLIENT_H can be any unique name.  By convention, we use the name of the header file.
#ifndef _HTTPCLIENT_H
#define _HTTPCLIENT_H

#include <atomic>

#include <pistache/net.h>
#include <pistache/http.h>
#include <pistache/client.h>

//#define POSTGRES_CONN pqxx::connection
// This is the content of the .h file, which is where the declarations go

class HTTP_Client
{
private:

public:
  static void setup();
  static int sampledo(int argc, char const *argv[]);
  static void get(std::string const page, std::string& body, Pistache::Http::Code &code);
};
// This is the end of the header guard
#endif
