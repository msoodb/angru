#ifndef ANGRU_RESTSERVER_H_
#define ANGRU_RESTSERVER_H_

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/description.h>
#include <pistache/router.h>
#include <pistache/serializer/rapidjson.h>

namespace angru{
namespace wrapper{

class RestServer
{
private:
  std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
  Pistache::Rest::Router router;
  Pistache::Rest::Description desc;
public:
  static void Setup(int port_number, int thread_count);
  RestServer(Pistache::Address);
  void PrintCookies(const Pistache::Http::Request&);
  void HandleReady(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  void Init(size_t thr = 2);
  void Start();
  void Shutdown();
  void SetupRoutes();
};

} // wrapper
} // angru

#endif // ANGRU_RESTSERVER_H_
