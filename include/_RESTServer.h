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
class Metric {
    public:
        Metric(std::string name, int initialValue = 1)
            : name_(std::move(name))
            , value_(initialValue)
        { }

        int incr(int n = 1) {
            int old = value_;
            value_ += n;
            return old;
        }

        int value() const {
            return value_;
        }

        std::string name() const {
            return name_;
        }
    private:
        std::string name_;
        int value_;
};

class REST_Server
{
private:
  typedef std::mutex Lock;
  typedef std::lock_guard<Lock> Guard;
  Lock metricsLock;
  std::vector<Metric> metrics;
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
  void doRecordMetric(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  void doGetMetric(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  void doGetProduct(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  void doAuth(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};
// This is the end of the header guard
#endif
