#ifndef ANGRU_TAGS_PLAYLIST_CONTROLLER_H_
#define ANGRU_TAGS_PLAYLIST_CONTROLLER_H_

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

class TagsPlaylistController
{
public:
	TagsPlaylistController();
	~TagsPlaylistController();
	static void	doGetTagsPlaylists(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetTagsPlaylist(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteTagsPlaylist(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddTagsPlaylist(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateTagsPlaylist(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_TAGS_PLAYLIST_CONTROLLER_H_
