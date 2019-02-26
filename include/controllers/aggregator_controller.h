#ifndef ANGRU_AGGREGATOR_CONTROLLER_H_
#define ANGRU_AGGREGATOR_CONTROLLER_H_

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

class AggregatorController
{
public:
	AggregatorController();
	~AggregatorController();
	static void	doGetAggregators(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetAggregator(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteAggregator(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddAggregator(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateAggregator(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_AGGREGATOR_CONTROLLER_H_
