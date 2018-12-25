#ifndef ANGRU_HTTPCLIENT_H_
#define ANGRU_HTTPCLIENT_H_

#include <atomic>

#include <pistache/net.h>
#include <pistache/http.h>
#include <pistache/client.h>

namespace angru{
namespace wrapper{

class HttpClient
{
private:

public:
  static void setup();
  static int sampledo(int argc, char const *argv[]);
  static void get(std::string const page, std::string& body, Pistache::Http::Code &code);
};

} // wrapper
} // angru

#endif // ANGRU_HTTPCLIENT_H_
