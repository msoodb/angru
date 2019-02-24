#ifndef ANGRU_PLAYLISTS_CONTENT_CONTROLLER_H_
#define ANGRU_PLAYLISTS_CONTENT_CONTROLLER_H_

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

class PlaylistsContentController
{
public:
	PlaylistsContentController();
	~PlaylistsContentController();
	static void	doGetPlaylistsContents(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetPlaylistsContent(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeletePlaylistsContent(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddPlaylistsContent(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdatePlaylistsContent(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_PLAYLISTS_CONTENT_CONTROLLER_H_
