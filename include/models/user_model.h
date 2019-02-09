#ifndef ANGRU_USER_MODEL_H_
#define ANGRU_USER_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace angru{
namespace mvc{
namespace model{

class UserModel
{
public:
	UserModel();
	~UserModel();
	static pqxx::result GetUsers(int page=1, std::string query="");
	static int GetUsersCount(std::string query="");
	static boost::property_tree::ptree GetUsersJson(int page=1, std::string query="");
  static pqxx::result GetUser(std::string);
	static boost::property_tree::ptree GetUserJson(std::string);
	static std::string AddUser(
													std::string	first_name,
													std::string	middle_name,
													std::string	last_name,
													std::string	user_name,
													std::string	email,
													std::string	password,
													int	type,
													std::string	details,
													int	status,
													std::string	description);
	static void UpdateUser(
													std::string,
													std::string	first_name,
													std::string	middle_name,
													std::string	last_name,
													std::string	user_name,
													std::string	email,
													std::string	password,
													int	type,
													std::string	details,
													int	status,
													std::string	description);
	static void DeleteUser(std::string);
};

} // model
} // mvc
} // angru

#endif // ANGRU_USER_MODEL_H_
