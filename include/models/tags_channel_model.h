#ifndef ANGRU_TAGS_CHANNEL_MODEL_H_
#define ANGRU_TAGS_CHANNEL_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace angru{
namespace mvc{
namespace model{

class TagChannelModel
{
public:
	TagChannelModel();
	~TagChannelModel();
	static pqxx::result GetTagChannels(int page=1, std::string query="");
	static int GetTagChannelsCount(std::string query="");
	static boost::property_tree::ptree GetTagChannelsJson(int page=1, std::string query="");
  static pqxx::result GetTagChannel(std::string id);
	static boost::property_tree::ptree GetTagChannelJson(std::string id);
	static std::string AddTagChannel(
													std::string	tag,
													std::string	channel,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateTagChannel(
													std::string	id,
													std::string	tag,
													std::string	channel,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteTagChannel(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_TAGS_CHANNEL_MODEL_H_
