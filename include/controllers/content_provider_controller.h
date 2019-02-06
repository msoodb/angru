#ifndef ANGRU_CONTENT_PROVIDER_CONTROLLER_H_
#define ANGRU_CONTENT_PROVIDER_CONTROLLER_H_

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

class Content_providerController
{
public:
	Content_providerController();
	~Content_providerController();
	static void	doGetContent_providers(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetContent_provider(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteContent_provider(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddContent_provider(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateContent_provider(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_CONTENT_PROVIDER_CONTROLLER_H_
