#ifndef ANGRU_AVATAR_CONTROLLER_H_
#define ANGRU_AVATAR_CONTROLLER_H_

#include <iostream>

#include <pqxx/pqxx>

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/description.h>
#include <pistache/router.h>
#include <pistache/serializer/rapidjson.h>

namespace angru{
namespace mvc{
namespace controller{

class AvatarController
{
public:
	AvatarController();
	~AvatarController();
	static void doGetAvatar(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void doAddAvatar(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // controller
} // mvc
} // angru

#endif // ANGRU_AVATAR_CONTROLLER_H_
