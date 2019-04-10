#ifndef ANGRU_PRIVILEGE_MODEL_H_
#define ANGRU_PRIVILEGE_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

#define GET_ITEMS    0
#define GET_ITEM     1
#define ADD_ITEM     2
#define UPDATE_ITEM  3
#define DELETE_ITEM  4




class PrivilegeModel
{
public:
	PrivilegeModel();
	~PrivilegeModel();
	static bool AuthorizationCheck(std::string user_id, std::string entity_name, int action);
	static pqxx::result GetPrivilegeStrings(std::string user_id, std::string entity_name);
	static pqxx::result GetPrivileges(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
	static int GetPrivilegesCount(std::string query="");
	static boost::property_tree::ptree GetPrivilegesJson(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
  static pqxx::result GetPrivilege(std::string id);
	static boost::property_tree::ptree GetPrivilegeJson(std::string id);
	static std::string AddPrivilege(
													std::string	security_role,
													std::string	entity,
													std::string	privilege_string,
													std::string	created_by,
													int	status,
													int	situation,
													std::string	description);
	static void UpdatePrivilege(
													std::string	id,
													std::string	security_role,
													std::string	entity,
													std::string	privilege_string,
													std::string	updated_by,
													int	status,
													int	situation,
													std::string	description);
	static void DeletePrivilege(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_PRIVILEGE_MODEL_H_
