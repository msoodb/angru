#ifndef ANGRU_PRIVILEGE_CONTROLLER_H_
#define ANGRU_PRIVILEGE_CONTROLLER_H_

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

class PrivilegeController
{
public:
	PrivilegeController();
	~PrivilegeController();
	static void	doGetPrivileges(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetPrivilege(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeletePrivilege(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddPrivilege(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdatePrivilege(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_PRIVILEGE_CONTROLLER_H_
