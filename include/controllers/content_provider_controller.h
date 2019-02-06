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

class ContentProviderController
{
public:
	ContentProviderController();
	~ContentProviderController();
	static void	doGetContentProviders(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetContentProvider(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteContentProvider(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddContentProvider(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateContentProvider(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_CONTENT_PROVIDER_CONTROLLER_H_
