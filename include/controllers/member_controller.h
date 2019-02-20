#ifndef ANGRU_MEMBER_CONTROLLER_H_
#define ANGRU_MEMBER_CONTROLLER_H_

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

class MemberController
{
public:
	MemberController();
	~MemberController();
	static void	doGetMembers(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetMember(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteMember(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddMember(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateMember(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_MEMBER_CONTROLLER_H_
