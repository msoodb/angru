#include "models/user_model.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

UserModel::UserModel(){}
UserModel::~UserModel(){}
pqxx::result UserModel::GetUsers(int page, std::string query){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
		} else {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	LOG_INFO << "Connected to database: " << C.dbname();
	pqxx::work W(C);
	std::string complete_query = "SELECT id, email, password, details, created_at \
																FROM users where deleted_at is NULL ";
	if(!query.empty())
	{
		complete_query += " and ";
		complete_query +=  query;
	}
	complete_query += " limit 20 offset ";
	int offset = (page-1)* OFFSET_COUNT ;
	complete_query += std::to_string(offset);
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find").exec();
  W.commit();
	return R;
}
boost::property_tree::ptree UserModel::GetUsersJson(int page, std::string query){
	pqxx::result R = GetUsers(page, query);
	int count = R.size();
	int pageCount = count / OFFSET_COUNT;
	boost::property_tree::ptree users_node;
	boost::property_tree::ptree user_node;
for (size_t i = 0; i < R.size(); i++) {
		user_node.put("id", R[i][0]);
		user_node.put("email", R[i][1]);
		user_node.put("password", R[i][2]);
		user_node.put("details", R[i][3]);
		user_node.put("created_at", R[i][4]);
		users_node.push_back(std::make_pair(R[i][0].c_str(), user_node));
	}
	return users_node;
}
pqxx::result UserModel::GetUser(int id){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
		} else {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	LOG_INFO << "Connected to database: " << C.dbname();
	pqxx::work W(C);
  C.prepare("find", "SELECT id, email, details, created_at \
																FROM users where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
  W.commit();
	return R;
}
boost::property_tree::ptree UserModel::GetUserJson(int id){
	pqxx::result R = GetUser(id);
	boost::property_tree::ptree users_node;
	boost::property_tree::ptree user_node;
	user_node.put("id", R[0][0]);
	user_node.put("email", R[0][1]);
	user_node.put("details", R[0][2]);
	user_node.put("created_at", R[0][3]);
	users_node.push_back(std::make_pair(R[0][0].c_str(), user_node));
	return users_node;
}
void UserModel::AddUser( 	std::string  email,
													std::string  password,
													std::string  details){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
		} else {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	LOG_INFO << "Connected to database: " << C.dbname();
	pqxx::work W(C);
	C.prepare("insert", "INSERT INTO users \
												(id, email, password, details, created_at, deleted_at) VALUES \
												(DEFAULT, $1, $2, $3, now(), NULL)");
  pqxx::result R = W.prepared("insert")(email)(password)(details).exec();
  W.commit();
}
void UserModel::UpdateUser(int id,
													std::string  email,
													std::string  password,
													std::string  details){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
		} else {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	LOG_INFO << "Connected to database: " << C.dbname();
	pqxx::work W(C);
	C.prepare("update", "UPDATE users SET \
												email = $2, password = $3, details = $4 WHERE id = $1");
  W.prepared("update")(id)(email)(password).exec();
  W.commit();
}
void UserModel::DeleteUser(int id){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
		} else {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	LOG_INFO << "Connected to database: " << C.dbname();
	pqxx::work W(C);
	C.prepare("update", "UPDATE users SET deleted_at = now() \
													WHERE id = $1");
	W.prepared("update")(id).exec();
  W.commit();
}

} // model
} // mvc
} // angru
