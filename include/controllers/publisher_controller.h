#ifndef ANGRU_PUBLISHER_CONTROLLER_H_
#define ANGRU_PUBLISHER_CONTROLLER_H_

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

class PublisherController
{
public:
	PublisherController();
	~PublisherController();
	static void	doGetPublishers(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetPublisher(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeletePublisher(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddPublisher(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdatePublisher(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_PUBLISHER_CONTROLLER_H_
