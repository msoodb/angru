// This is start of the header guard. _RESTSERVER_H can be any unique name.  By convention, we use the name of the header file.
#ifndef _RESTSERVER_H
#define _RESTSERVER_H

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/description.h>
#include <pistache/router.h>
#include <pistache/serializer/rapidjson.h>

//#define POSTGRES_CONN pqxx::connection
// This is the content of the .h file, which is where the declarations go

class REST_Server
{
private:
  std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
  Pistache::Rest::Router router;
  Pistache::Rest::Description desc;
public:
  REST_Server(Pistache::Address);
  void printCookies(const Pistache::Http::Request&);
  void handleReady(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  void init(size_t thr = 2);
  void start();
  void shutdown();
  void setupRoutes();  
};
// This is the end of the header guard
#endif
