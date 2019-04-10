#ifndef ANGRU_PLAYLISTS_CONTENT_MODEL_H_
#define ANGRU_PLAYLISTS_CONTENT_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class PlaylistsContentModel
{
public:
	PlaylistsContentModel();
	~PlaylistsContentModel();
	static pqxx::result GetPlaylistsContents(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
	static int GetPlaylistsContentsCount(std::string query="");
	static boost::property_tree::ptree GetPlaylistsContentsJson(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
  static pqxx::result GetPlaylistsContent(std::string id);
	static boost::property_tree::ptree GetPlaylistsContentJson(std::string id);
	static std::string AddPlaylistsContent(
													std::string	playlist,
													std::string	content,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void UpdatePlaylistsContent(
													std::string	id,
													std::string	playlist,
													std::string	content,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void DeletePlaylistsContent(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_PLAYLISTS_CONTENT_MODEL_H_
