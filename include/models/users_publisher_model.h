#ifndef ANGRU_USERS_PUBLISHER_MODEL_H_
#define ANGRU_USERS_PUBLISHER_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class UsersPublisherModel
{
public:
	UsersPublisherModel();
	~UsersPublisherModel();
	static pqxx::result GetUsersPublishers(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
	static int GetUsersPublishersCount(std::string query="");
	static boost::property_tree::ptree GetUsersPublishersJson(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
  static pqxx::result GetUsersPublisher(std::string id);
	static boost::property_tree::ptree GetUsersPublisherJson(std::string id);
	static std::string AddUsersPublisher(
													std::string	_user_,
													std::string	publisher,
													std::string	created_by,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateUsersPublisher(
													std::string	id,
													std::string	_user_,
													std::string	publisher,
													std::string	updated_by,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteUsersPublisher(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_USERS_PUBLISHER_MODEL_H_
