#ifndef ANGRU_USERS_PUBLISHER_CONTROLLER_H_
#define ANGRU_USERS_PUBLISHER_CONTROLLER_H_

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

class UsersPublisherController
{
public:
	UsersPublisherController();
	~UsersPublisherController();
	static void	doGetUsersPublishers(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetUsersPublisher(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteUsersPublisher(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddUsersPublisher(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateUsersPublisher(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_USERS_PUBLISHER_CONTROLLER_H_
