#ifndef ANGRU_CHANNEL_MODEL_H_
#define ANGRU_CHANNEL_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class ChannelModel
{
public:
	ChannelModel();
	~ChannelModel();
	static pqxx::result GetChannels(int page=1, int limit=LIMIT_COUNT, std::string service="", std::string parent="", std::string query="");
	static int GetChannelsCount(std::string service="", std::string parent="", std::string query="");
	static boost::property_tree::ptree GetChannelsJson(int page=1, int limit=LIMIT_COUNT, std::string service="", std::string parent="", std::string query="");
	static pqxx::result GetAllChannels(int page=1, int limit=LIMIT_COUNT, std::string query="");
	static int GetAllChannelsCount(std::string query="");
	static boost::property_tree::ptree GetAllChannelsJson(int page=1, int limit=LIMIT_COUNT, std::string query="");
  static pqxx::result GetChannel(std::string id);
	static boost::property_tree::ptree GetChannelJson(std::string id);
	static std::string AddChannel(
													std::string	name,
													std::string	title,
													std::string	service,
													std::string	parent,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateChannel(
													std::string	id,
													std::string	name,
													std::string	title,
													std::string	service,
													std::string	parent,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteChannel(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_CHANNEL_MODEL_H_
