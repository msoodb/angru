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
	static pqxx::result getUsers(int page=1, std::string query="");
	static boost::property_tree::ptree getUsers_json(int page=1, std::string query="");
  static pqxx::row getUser(int);
	static boost::property_tree::ptree getUser_json(int);
	static void addUser(std::string, std::string, std::string);
	static void updateUser(int, std::string, std::string, std::string);
	static void deleteUser(int);
};

} // model
} // mvc
} // angru

#endif // ANGRU_USER_MODEL_H_
