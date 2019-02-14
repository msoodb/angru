#ifndef ANGRU_MOBILE_OPERATOR_CONTROLLER_H_
#define ANGRU_MOBILE_OPERATOR_CONTROLLER_H_

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

class MobileOperatorController
{
public:
	MobileOperatorController();
	~MobileOperatorController();
	static void	doGetMobileOperators(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetMobileOperator(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteMobileOperator(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddMobileOperator(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateMobileOperator(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_MOBILE_OPERATOR_CONTROLLER_H_
