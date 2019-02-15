#ifndef ANGRU_ENTITIE_CONTROLLER_H_
#define ANGRU_ENTITIE_CONTROLLER_H_

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

class EntitieController
{
public:
	EntitieController();
	~EntitieController();
	static void	doGetEntities(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetEntitie(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteEntitie(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddEntitie(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateEntitie(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_ENTITIE_CONTROLLER_H_
