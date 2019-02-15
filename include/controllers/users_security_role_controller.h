#ifndef ANGRU_USERS_SECURITY_ROLE_CONTROLLER_H_
#define ANGRU_USERS_SECURITY_ROLE_CONTROLLER_H_

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

class UsersSecurityRoleController
{
public:
	UsersSecurityRoleController();
	~UsersSecurityRoleController();
	static void	doGetUsersSecurityRoles(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetUsersSecurityRole(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteUsersSecurityRole(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddUsersSecurityRole(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateUsersSecurityRole(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_USERS_SECURITY_ROLE_CONTROLLER_H_
