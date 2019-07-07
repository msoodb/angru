#ifndef ANGRU_CONTENT_CONTROLLER_H_
#define ANGRU_CONTENT_CONTROLLER_H_

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

class ContentController
{
public:
	ContentController();
	~ContentController();
	static void	doGetContents(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetContentsByChannel(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetContentsByService(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetContent(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteContent(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddContent(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateContent(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_CONTENT_CONTROLLER_H_
