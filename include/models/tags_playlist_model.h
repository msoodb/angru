#ifndef ANGRU_TAGS_PLAYLIST_MODEL_H_
#define ANGRU_TAGS_PLAYLIST_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class TagsPlaylistModel
{
public:
	TagsPlaylistModel();
	~TagsPlaylistModel();
	static pqxx::result GetTagsPlaylists(int page=1, int limit=LIMIT_COUNT, std::string query="");
	static int GetTagsPlaylistsCount(std::string query="");
	static boost::property_tree::ptree GetTagsPlaylistsJson(int page=1, int limit=LIMIT_COUNT, std::string query="");
  static pqxx::result GetTagsPlaylist(std::string id);
	static boost::property_tree::ptree GetTagsPlaylistJson(std::string id);
	static std::string AddTagsPlaylist(
													std::string	tag,
													std::string	playlist,
													std::string	created_by,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateTagsPlaylist(
													std::string	id,
													std::string	tag,
													std::string	playlist,
													std::string	updated_by,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteTagsPlaylist(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_TAGS_PLAYLIST_MODEL_H_
