#ifndef ANGRU_HTTPCLIENT_H_
#define ANGRU_HTTPCLIENT_H_

#include <atomic>

#include <pistache/net.h>
#include <pistache/http.h>
#include <pistache/client.h>

class HTTP_Client
{
private:

public:
  static void setup();
  static int sampledo(int argc, char const *argv[]);
  static void get(std::string const page, std::string& body, Pistache::Http::Code &code);
};

#endif // ANGRU_HTTPCLIENT_H_
