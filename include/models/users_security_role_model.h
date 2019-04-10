#ifndef ANGRU_USERS_SECURITY_ROLE_MODEL_H_
#define ANGRU_USERS_SECURITY_ROLE_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class UsersSecurityRoleModel
{
public:
	UsersSecurityRoleModel();
	~UsersSecurityRoleModel();
	static pqxx::result GetUsersSecurityRoles(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
	static int GetUsersSecurityRolesCount(std::string query="");
	static boost::property_tree::ptree GetUsersSecurityRolesJson(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
  static pqxx::result GetUsersSecurityRole(std::string id);
	static boost::property_tree::ptree GetUsersSecurityRoleJson(std::string id);
	static std::string AddUsersSecurityRole(
													std::string	_user_,
													std::string	security_role,
													std::string	created_by,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateUsersSecurityRole(
													std::string	id,
													std::string	_user_,
													std::string	security_role,
													std::string	updated_by,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteUsersSecurityRole(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_USERS_SECURITY_ROLE_MODEL_H_
