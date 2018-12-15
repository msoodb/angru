#include <iostream>
#include <string>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "_error.h"
#include "_log.h"
#include "_PostgreSQL.h"

#include "userModel.h"


UserModel::UserModel(){}
UserModel::~UserModel(){}
pqxx::result UserModel::getUsers(int page, std::string query){
	pqxx::connection C(_PostgreSQL::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
		} else {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const _error &e) {
			LOG_ERROR << e.what();
	}
	LOG_INFO << "Connected to database: " << C.dbname();
	pqxx::work W(C);
	std::string complete_query = "SELECT id, email, password, details, created_at, \
																deleted_at FROM users ";
	if(!query.empty())
	{
		complete_query += " where ";
		complete_query +=  query;
	}
	complete_query += "limit 20 offset ";
	int offset = (page-1)* OFFSET_COUNT ;
	complete_query += std::to_string(offset);
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find").exec();
  W.commit();
	return R;
}
boost::property_tree::ptree UserModel::getUsers_json(int page, std::string query){
	pqxx::result R = getUsers(page, query);
	int count = R.size();
	int pageCount = count / OFFSET_COUNT;
	boost::property_tree::ptree users_node;
	boost::property_tree::ptree user_node;
	for(pqxx::row r : R)
	{
		user_node.put("id", r[0]);
		user_node.put("email", r[1]);
		user_node.put("password", r[2]);
		user_node.put("details", r[3]);
		user_node.put("created_at", r[4]);
		user_node.put("deleted_at", r[5]);
		users_node.push_back(std::make_pair(r[0].c_str(), user_node));
	}
	return users_node;
}
pqxx::row UserModel::getUser(int id){
	pqxx::connection C(_PostgreSQL::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
		} else {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const _error &e) {
			LOG_ERROR << e.what();
	}
	LOG_INFO << "Connected to database: " << C.dbname();
	pqxx::work W(C);
  C.prepare("find", "SELECT id, email, password, details, created_at, \
																deleted_at FROM users where id = $1");
  pqxx::result R = W.prepared("find")(id).exec();
	pqxx::row r;
	if (R.size() == 1){
		r = R[0];
	}
  W.commit();
	return r;
}
boost::property_tree::ptree UserModel::getUser_json(int id){
	pqxx::row r = getUser(id);
	boost::property_tree::ptree users_node;
	boost::property_tree::ptree user_node;
	user_node.put("id", r[0]);
	user_node.put("email", r[1]);
	user_node.put("password", r[2]);
	user_node.put("details", r[3]);
	user_node.put("created_at", r[4]);
	user_node.put("deleted_at", r[5]);
	users_node.push_back(std::make_pair(r[0].c_str(), user_node));
	return users_node;
}
void UserModel::addUser( int id,
													std::string title,
													float price,
													std::string  created_at,
													std::string  deleted_at,
													std::string  tags){
	pqxx::connection C(_PostgreSQL::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
		} else {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const _error &e) {
			LOG_ERROR << e.what();
	}
	LOG_INFO << "Connected to database: " << C.dbname();
	pqxx::work W(C);
	C.prepare("insert", "INSERT INTO users \
												(id, email, password, details, created_at, deleted_at) VALUES \
												($1, $2, $3, $4, $5, $6)");
  pqxx::result R = W.prepared("insert")(id)(title)(price)(created_at)(deleted_at)(tags).exec();
  W.commit();
}
void UserModel::updateUser( int id,
													std::string title,
													float price,
													std::string  created_at,
													std::string  deleted_at,
													std::string  tags){
	pqxx::connection C(_PostgreSQL::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
		} else {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const _error &e) {
			LOG_ERROR << e.what();
	}
	LOG_INFO << "Connected to database: " << C.dbname();
	pqxx::work W(C);
	C.prepare("update", "UPDATE users SET \
												email = $2, password = $3, details = $4, created_at = $5, \
												deleted_at = $6 WHERE id = $1");
  W.prepared("update")(id)(title)(price)(created_at)(deleted_at)(tags).exec();
  W.commit();
}
void UserModel::deleteUser(int id){
	pqxx::connection C(_PostgreSQL::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
		} else {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const _error &e) {
			LOG_ERROR << e.what();
	}
	LOG_INFO << "Connected to database: " << C.dbname();
	pqxx::work W(C);
  C.prepare("delete", "DELETE FROM users where id = $1");
  W.prepared("delete")(id).exec();
  W.commit();
}
