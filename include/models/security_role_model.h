#ifndef ANGRU_SECURITY_ROLE_MODEL_H_
#define ANGRU_SECURITY_ROLE_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace angru{
namespace mvc{
namespace model{

class SecurityRolesModel
{
public:
	SecurityRolesModel();
	~SecurityRolesModel();
	static pqxx::result GetSecurityRoless(int page=1, std::string query="");
	static int GetSecurityRolessCount(std::string query="");
	static boost::property_tree::ptree GetSecurityRolessJson(int page=1, std::string query="");
  static pqxx::result GetSecurityRoles(std::string id);
	static boost::property_tree::ptree GetSecurityRolesJson(std::string id);
	static std::string AddSecurityRoles(
													std::string	name,
													std::string	title,
													std::string	created_by,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateSecurityRoles(
													std::string	id,
													std::string	name,
													std::string	title,
													std::string	updated_by,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteSecurityRoles(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_SECURITY_ROLE_MODEL_H_
