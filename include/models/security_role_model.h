#ifndef ANGRU_SECURITY_ROLE_MODEL_H_
#define ANGRU_SECURITY_ROLE_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class SecurityRoleModel
{
public:
	SecurityRoleModel();
	~SecurityRoleModel();
	static pqxx::result GetSecurityRoles(int page=1, int limit=LIMIT_COUNT, std::string query="");
	static int GetSecurityRolesCount(std::string query="");
	static boost::property_tree::ptree GetSecurityRolesJson(int page=1, int limit=LIMIT_COUNT, std::string query="");
  static pqxx::result GetSecurityRole(std::string id);
	static boost::property_tree::ptree GetSecurityRoleJson(std::string id);
	static std::string AddSecurityRole(
													std::string	name,
													std::string	title,
													std::string	created_by,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateSecurityRole(
													std::string	id,
													std::string	name,
													std::string	title,
													std::string	updated_by,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteSecurityRole(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_SECURITY_ROLE_MODEL_H_
