// This is start of the header guard. USER_MODEL_H can be any unique name.  By convention, we use the name of the header file.
#ifndef USER_MODEL_H
#define USER_MODEL_H

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>



// This is the content of the .h file, which is where the declarations go
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

// This is the end of the header guard
#endif
