#ifndef ANGRU_TAGS_CHANNEL_CONTROLLER_H_
#define ANGRU_TAGS_CHANNEL_CONTROLLER_H_

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

class TagChannelController
{
public:
	TagChannelController();
	~TagChannelController();
	static void	doGetTagChannels(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetTagChannel(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteTagChannel(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddTagChannel(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateTagChannel(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_TAGS_CHANNEL_CONTROLLER_H_
