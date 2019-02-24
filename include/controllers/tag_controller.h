#ifndef ANGRU_TAG_CONTROLLER_H_
#define ANGRU_TAG_CONTROLLER_H_

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

class TagController
{
public:
	TagController();
	~TagController();
	static void	doGetTags(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetTag(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteTag(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddTag(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateTag(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_TAG_CONTROLLER_H_
