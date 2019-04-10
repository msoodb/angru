#ifndef ANGRU_MEMBER_MODEL_H_
#define ANGRU_MEMBER_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class MemberModel
{
public:
	MemberModel();
	~MemberModel();
	static pqxx::result GetMembers(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
	static int GetMembersCount(std::string query="");
	static boost::property_tree::ptree GetMembersJson(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
  static pqxx::result GetMember(std::string id);
	static boost::property_tree::ptree GetMemberJson(std::string id);
	static std::string AddMember(
													std::string	phone,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateMember(
													std::string	id,
													std::string	phone,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteMember(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_MEMBER_MODEL_H_
