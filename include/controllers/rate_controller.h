#ifndef ANGRU_RATE_CONTROLLER_H_
#define ANGRU_RATE_CONTROLLER_H_

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

class RateController
{
public:
	RateController();
	~RateController();
	static void	doGetRates(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetRate(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteRate(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddRate(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateRate(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_RATE_CONTROLLER_H_
