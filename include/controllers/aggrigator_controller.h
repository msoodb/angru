#ifndef ANGRU_AGGRIGATOR_CONTROLLER_H_
#define ANGRU_AGGRIGATOR_CONTROLLER_H_

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

class AggrigatorController
{
public:
	AggrigatorController();
	~AggrigatorController();
	static void	doGetAggrigators(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetAggrigator(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteAggrigator(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddAggrigator(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateAggrigator(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_AGGRIGATOR_CONTROLLER_H_
