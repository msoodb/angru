#ifndef ANGRU_TAGS_CHANNEL_MODEL_H_
#define ANGRU_TAGS_CHANNEL_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class TagsChannelModel
{
public:
	TagsChannelModel();
	~TagsChannelModel();
	static pqxx::result GetTagsChannels(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
	static int GetTagsChannelsCount(std::string query="");
	static boost::property_tree::ptree GetTagsChannelsJson(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
  static pqxx::result GetTagsChannel(std::string id);
	static boost::property_tree::ptree GetTagsChannelJson(std::string id);
	static std::string AddTagsChannel(
													std::string	tag,
													std::string	channel,
													std::string	created_by,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateTagsChannel(
													std::string	id,
													std::string	tag,
													std::string	channel,
													std::string	updated_by,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteTagsChannel(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_TAGS_CHANNEL_MODEL_H_
