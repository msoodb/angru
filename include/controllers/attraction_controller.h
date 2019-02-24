#ifndef ANGRU_ATTRACTION_CONTROLLER_H_
#define ANGRU_ATTRACTION_CONTROLLER_H_

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

class AttractionController
{
public:
	AttractionController();
	~AttractionController();
	static void	doGetAttractions(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetAttraction(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteAttraction(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddAttraction(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateAttraction(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_ATTRACTION_CONTROLLER_H_
