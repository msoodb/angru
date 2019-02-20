#ifndef ANGRU_SUBSCRIPTION_CONTROLLER_H_
#define ANGRU_SUBSCRIPTION_CONTROLLER_H_

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

class SubscriptionController
{
public:
	SubscriptionController();
	~SubscriptionController();
	static void	doGetSubscriptions(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetSubscription(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteSubscription(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddSubscription(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateSubscription(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_SUBSCRIPTION_CONTROLLER_H_
