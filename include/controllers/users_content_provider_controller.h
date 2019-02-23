#ifndef ANGRU_USERS_CONTENT_PROVIDER_CONTROLLER_H_
#define ANGRU_USERS_CONTENT_PROVIDER_CONTROLLER_H_

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

class UsersContentProviderController
{
public:
	UsersContentProviderController();
	~UsersContentProviderController();
	static void	doGetUsersContentProviders(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetUsersContentProvider(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteUsersContentProvider(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddUsersContentProvider(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateUsersContentProvider(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_USERS_CONTENT_PROVIDER_CONTROLLER_H_
