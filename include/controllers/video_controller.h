#ifndef ANGRU_VIDEO_CONTROLLER_H_
#define ANGRU_VIDEO_CONTROLLER_H_

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

class VideoController
{
public:
	VideoController();
	~VideoController();
	static void	doGetVideos(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetVideo(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteVideo(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddVideo(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateVideo(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_VIDEO_CONTROLLER_H_
