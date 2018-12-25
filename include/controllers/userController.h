#ifndef ANGRU_USER_CONTROLLER_H_
#define ANGRU_USER_CONTROLLER_H_

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

class UserController
{
public:
	UserController();
	~UserController();
	static void doLogin(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetUsers(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetUser(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doDeleteUser(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddUser(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateUser(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // controller
} // mvc
} // angru

#endif // ANGRU_USER_CONTROLLER_H_
