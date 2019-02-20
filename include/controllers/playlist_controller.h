#ifndef ANGRU_PLAYLIST_CONTROLLER_H_
#define ANGRU_PLAYLIST_CONTROLLER_H_

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

class PlaylistController
{
public:
	PlaylistController();
	~PlaylistController();
	static void	doGetPlaylists(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetPlaylist(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeletePlaylist(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddPlaylist(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdatePlaylist(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_PLAYLIST_CONTROLLER_H_
