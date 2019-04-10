#ifndef ANGRU_USERS_CONTENT_PROVIDER_MODEL_H_
#define ANGRU_USERS_CONTENT_PROVIDER_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class UsersContentProviderModel
{
public:
	UsersContentProviderModel();
	~UsersContentProviderModel();
	static pqxx::result GetUsersContentProviders(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
	static int GetUsersContentProvidersCount(std::string query="");
	static boost::property_tree::ptree GetUsersContentProvidersJson(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
  static pqxx::result GetUsersContentProvider(std::string id);
	static boost::property_tree::ptree GetUsersContentProviderJson(std::string id);
	static std::string AddUsersContentProvider(
													std::string	_user_,
													std::string	content_provider,
													std::string	created_by,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateUsersContentProvider(
													std::string	id,
													std::string	_user_,
													std::string	content_provider,
													std::string	updated_by,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteUsersContentProvider(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_USERS_CONTENT_PROVIDER_MODEL_H_
