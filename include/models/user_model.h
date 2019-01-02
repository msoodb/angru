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
  static pqxx::result  GetUser(int);
	static boost::property_tree::ptree GetUserJson(int);
	static void AddUser(std::string, std::string, std::string);
	static void UpdateUser(int, std::string, std::string, std::string);
	static void DeleteUser(int);
};

} // model
} // mvc
} // angru

#endif // ANGRU_USER_MODEL_H_
