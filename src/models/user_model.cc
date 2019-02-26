#include "models/user_model.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "wrappers/csv_writer.h"

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
	std::string complete_query = "SELECT \
									      				id , \
									      				first_name , \
									      				middle_name , \
									      				last_name , \
									      				username , \
									      				email , \
									      				password , \
									      				type , \
																(select username from users where id = main.created_by) as created_by, \
       													(select username from users where id = main.updated_by) as updated_by, \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM users AS main where deleted_at is NULL ";
	if(!query.empty())
	{
		complete_query += " AND ";
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

int UserModel::GetUsersCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM users where deleted_at is NULL ";
	if(!query.empty())
	{
		complete_query += " AND ";
		complete_query +=  query;
	}
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find").exec();
  W.commit();
	return (R[0][0]).as<int>();
}

boost::property_tree::ptree UserModel::GetUsersJson(int page, std::string query){
	pqxx::result R = GetUsers(page, query);
	int result_count = GetUsersCount(query);
	int pageCount = (result_count / OFFSET_COUNT) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree user_node;
	boost::property_tree::ptree users_node;

	for (size_t i = 0; i < R.size(); i++) {
		user_node.put("id", R[i][0]);
		user_node.put("first_name", R[i][1]);
		user_node.put("middle_name", R[i][2]);
		user_node.put("last_name", R[i][3]);
		user_node.put("username", R[i][4]);
		user_node.put("email", R[i][5]);
		user_node.put("password", R[i][6]);
		user_node.put("type", R[i][7]);
		user_node.put("created_by", R[i][8]);
		user_node.put("updated_by", R[i][9]);
		user_node.put("created_at", R[i][10]);
		user_node.put("updated_at", R[i][11]);
		user_node.put("details", R[i][12]);
		user_node.put("status", R[i][13]);
		user_node.put("situation", R[i][14]);
		user_node.put("description", R[i][15]);
		users_node.push_back(std::make_pair("", user_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("offset", OFFSET_COUNT);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", users_node);
	return result_node;
}

pqxx::result UserModel::GetUser(std::string id){
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
  C.prepare("find", "SELECT \
									      				id , \
									      				first_name , \
									      				middle_name , \
									      				last_name , \
									      				username , \
									      				email , \
									      				password , \
									      				type , \
																(select username from users where id = main.created_by) as created_by, \
       													(select username from users where id = main.updated_by) as updated_by, \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM users AS main where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

bool UserModel::IsZeus(std::string id){
	pqxx::result R = GetUser(id);
	std::string username = R[0][4].as<std::string>();
	if(username == "zeus"){
		return true;
	}
	return false;
}

boost::property_tree::ptree UserModel::GetUserJson(std::string id){
	pqxx::result R = GetUser(id);
	boost::property_tree::ptree user_node;

	if(R.size() == 1){
		user_node.put("id", R[0][0]);
		user_node.put("first_name", R[0][1]);
		user_node.put("middle_name", R[0][2]);
		user_node.put("last_name", R[0][3]);
		user_node.put("username", R[0][4]);
		user_node.put("email", R[0][5]);
		user_node.put("password", R[0][6]);
		user_node.put("type", R[0][7]);
		user_node.put("created_by", R[0][8]);
		user_node.put("updated_by", R[0][9]);
		user_node.put("created_at", R[0][10]);
		user_node.put("updated_at", R[0][11]);
		user_node.put("details", R[0][12]);
		user_node.put("status", R[0][13]);
		user_node.put("situation", R[0][14]);
		user_node.put("description", R[0][15]);
	}
	return user_node;
}

std::string UserModel::AddUser(
													std::string	first_name,
													std::string	middle_name,
													std::string	last_name,
													std::string	username,
													std::string	email,
													std::string	password,
													int	type,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description){
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
	C.prepare("insert", "INSERT INTO users( \
													id, \
													first_name, \
													middle_name, \
													last_name, \
													username, \
													email, \
													password, \
													type, \
													created_by, \
													deleted_by, \
													updated_by, \
													created_at, \
													deleted_at, \
													updated_at, \
													details, \
													status, \
													situation, \
													description	) VALUES (\
												   DEFAULT, \
												   $1, \
												   $2, \
												   $3, \
												   $4, \
												   $5, \
												   $6, \
												   $7, \
												   $8, \
												   NULL, \
												   NULL, \
												   now(), \
												   NULL, \
												   NULL, \
												   $9, \
												   $10, \
												   $11, \
												   $12 ) RETURNING id");

  pqxx::result R = W.prepared("insert")
                 (first_name)
                 (middle_name)
                 (last_name)
                 (username)
                 (email)
                 (password)
                 (type)
                 (created_by)
                 (details)
                 (status)
                 (situation)
                 (description)
         .exec();
  W.commit();
	std::string id="";
	if(R.size() == 1){
		id = R[0][0].as<std::string>();
	}
	return id;
}

void UserModel::UpdateUser(
													std::string	id,
													std::string	first_name,
													std::string	middle_name,
													std::string	last_name,
													std::string	username,
													std::string	email,
													int	type,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description ){
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
													first_name = $2, \
													middle_name = $3, \
													last_name = $4, \
													username = $5, \
													email = $6, \
													type = $7, \
													updated_by = $8, \
													updated_at = now(), \
													details = $9, \
													status = $10, \
													situation = $11, \
													description = $12	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (first_name)
                 (middle_name)
                 (last_name)
                 (username)
                 (email)
                 (type)
                 (updated_by)
                 (details)
                 (status)
                 (situation)
                 (description)
         .exec();
	W.commit();
}

void UserModel::ChangePassword(
													std::string	id,
													std::string password ){
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
													password = $2	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (password)
         .exec();
	W.commit();
}

void UserModel::DeleteUser(std::string id){
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
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
