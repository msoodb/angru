#ifndef ANGRU_SERVICE_CONTROLLER_H_
#define ANGRU_SERVICE_CONTROLLER_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/description.h>
#include <pistache/router.h>
#include <pistache/serializer/rapidjson.h>

namespace angru{
namespace mvc{
namespace controller{

class ServiceController
{
public:
	ServiceController();
	~ServiceController();
	static void	doGetServices(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetService(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteService(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddService(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateService(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_SERVICE_CONTROLLER_H_
