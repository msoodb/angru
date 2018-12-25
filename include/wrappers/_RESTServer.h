#ifndef ANGRU_RESTSERVER_H_
#define ANGRU_RESTSERVER_H_

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/description.h>
#include <pistache/router.h>
#include <pistache/serializer/rapidjson.h>

namespace angru{
namespace wrapper{

class REST_Server
{
private:
  std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
  Pistache::Rest::Router router;
  Pistache::Rest::Description desc;
public:
  static void setup(int port_number, int thread_count);
  REST_Server(Pistache::Address);
  void printCookies(const Pistache::Http::Request&);
  void handleReady(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  void init(size_t thr = 2);
  void start();
  void shutdown();
  void setupRoutes();
};

} // wrapper
} // angru

#endif // ANGRU_RESTSERVER_H_
