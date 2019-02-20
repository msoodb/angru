#ifndef ANGRU_CHANNEL_CONTROLLER_H_
#define ANGRU_CHANNEL_CONTROLLER_H_

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

class ChannelController
{
public:
	ChannelController();
	~ChannelController();
	static void	doGetChannels(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetChannel(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteChannel(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddChannel(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateChannel(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_CHANNEL_CONTROLLER_H_
