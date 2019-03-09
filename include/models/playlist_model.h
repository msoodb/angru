#ifndef ANGRU_PLAYLIST_MODEL_H_
#define ANGRU_PLAYLIST_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class PlaylistModel
{
public:
	PlaylistModel();
	~PlaylistModel();
	static pqxx::result GetPlaylists(int page=1, int limit=LIMIT_COUNT, std::string service="", std::string query="");
	static int GetPlaylistsCount(std::string service="", std::string query="");
	static boost::property_tree::ptree GetPlaylistsJson(int page=1, int limit=LIMIT_COUNT, std::string service="", std::string query="");
	static pqxx::result GetAllPlaylists(int page=1, int limit=LIMIT_COUNT, std::string query="");
	static int GetAllPlaylistsCount(std::string query="");
	static boost::property_tree::ptree GetAllPlaylistsJson(int page=1, int limit=LIMIT_COUNT, std::string query="");
  static pqxx::result GetPlaylist(std::string id);
	static boost::property_tree::ptree GetPlaylistJson(std::string id);
	static std::string AddPlaylist(
													std::string	name,
													std::string	title,
													std::string	service,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void UpdatePlaylist(
													std::string	id,
													std::string	name,
													std::string	title,
													std::string	service,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void DeletePlaylist(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_PLAYLIST_MODEL_H_
