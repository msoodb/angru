#ifndef ANGRU_SECURITY_ROLE_CONTROLLER_H_
#define ANGRU_SECURITY_ROLE_CONTROLLER_H_

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

class SecurityRolesController
{
public:
	SecurityRolesController();
	~SecurityRolesController();
	static void	doGetSecurityRoless(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetSecurityRoles(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteSecurityRoles(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddSecurityRoles(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateSecurityRoles(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_SECURITY_ROLE_CONTROLLER_H_
