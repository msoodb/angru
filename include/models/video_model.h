#ifndef ANGRU_VIDEO_MODEL_H_
#define ANGRU_VIDEO_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace angru{
namespace mvc{
namespace model{

class VideoModel
{
public:
	VideoModel();
	~VideoModel();
	static pqxx::result GetVideos(int page=1, std::string query="");
	static int GetVideosCount(std::string query="");
	static boost::property_tree::ptree GetVideosJson(int page=1, std::string query="");
  static pqxx::result GetVideo(std::string id);
	static boost::property_tree::ptree GetVideoJson(std::string id);
	static std::string AddVideo(
													std::string	content,
													std::string	name,
													std::string	title,
													std::string	path,
													float	size,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateVideo(
													std::string	id,
													std::string	content,
													std::string	name,
													std::string	title,
													std::string	path,
													float	size,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteVideo(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_VIDEO_MODEL_H_
