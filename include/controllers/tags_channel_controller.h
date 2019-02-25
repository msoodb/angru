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

class TagsChannelController
{
public:
	TagsChannelController();
	~TagsChannelController();
	static void	doGetTagsChannels(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetTagsChannel(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteTagsChannel(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddTagsChannel(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateTagsChannel(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_TAGS_CHANNEL_CONTROLLER_H_
