#include "models/users_security_role_model.h"

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

UsersSecurityRoleModel::UsersSecurityRoleModel(){}
UsersSecurityRoleModel::~UsersSecurityRoleModel(){}

pqxx::result UsersSecurityRoleModel::GetUsersSecurityRoles(int page, int limit, std::string query){
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
																(select username from users where id = main._user_) as  _user_ , \
																(select name from security_roles where id = main.security_role) as  security_role , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				status , \
									      				situation , \
									      				description  FROM users_security_roles AS main where deleted_at is NULL ";
	if(!query.empty())
	{
		complete_query += " AND ";
		complete_query +=  query;
	}
	complete_query += " limit ";
	complete_query += std::to_string(limit);
	complete_query += " offset ";
	int offset = (page-1)* limit;
	complete_query += std::to_string(offset);
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find").exec();
  W.commit();
	return R;
}

int UsersSecurityRoleModel::GetUsersSecurityRolesCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM users_security_roles where deleted_at is NULL ";
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

boost::property_tree::ptree UsersSecurityRoleModel::GetUsersSecurityRolesJson(int page, int limit, std::string query){
	pqxx::result R = GetUsersSecurityRoles(page, limit, query);
	int result_count = GetUsersSecurityRolesCount(query);
	int pageCount = (result_count / limit) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree users_security_role_node;
	boost::property_tree::ptree users_security_roles_node;

	for (size_t i = 0; i < R.size(); i++) {
		users_security_role_node.put("id", R[i][0]);
		users_security_role_node.put("_user_", R[i][1]);
		users_security_role_node.put("security_role", R[i][2]);
		users_security_role_node.put("created_by", R[i][3]);
		users_security_role_node.put("updated_by", R[i][4]);
		users_security_role_node.put("created_at", R[i][5]);
		users_security_role_node.put("updated_at", R[i][6]);
		users_security_role_node.put("status", R[i][7]);
		users_security_role_node.put("situation", R[i][8]);
		users_security_role_node.put("description", R[i][9]);
		users_security_roles_node.push_back(std::make_pair("", users_security_role_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("limit", limit);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", users_security_roles_node);
	return result_node;
}

pqxx::result UsersSecurityRoleModel::GetUsersSecurityRole(std::string id){
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
																_user_ , \
																security_role , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				status , \
									      				situation , \
									      				description  FROM users_security_roles AS main where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree UsersSecurityRoleModel::GetUsersSecurityRoleJson(std::string id){
	pqxx::result R = GetUsersSecurityRole(id);
	boost::property_tree::ptree users_security_role_node;

	if(R.size() == 1){
		users_security_role_node.put("id", R[0][0]);
		users_security_role_node.put("_user_", R[0][1]);
		users_security_role_node.put("security_role", R[0][2]);
		users_security_role_node.put("created_by", R[0][3]);
		users_security_role_node.put("updated_by", R[0][4]);
		users_security_role_node.put("created_at", R[0][5]);
		users_security_role_node.put("updated_at", R[0][6]);
		users_security_role_node.put("status", R[0][7]);
		users_security_role_node.put("situation", R[0][8]);
		users_security_role_node.put("description", R[0][9]);
	}
	return users_security_role_node;
}

std::string UsersSecurityRoleModel::AddUsersSecurityRole(
													std::string	_user_,
													std::string	security_role,
													std::string	created_by,
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
	C.prepare("insert", "INSERT INTO users_security_roles( \
													id, \
													_user_, \
													security_role, \
													created_by, \
													deleted_by, \
													updated_by, \
													created_at, \
													deleted_at, \
													updated_at, \
													status, \
													situation, \
													description	) VALUES (\
												   DEFAULT, \
												   $1, \
												   $2, \
												   $3, \
												   NULL, \
												   NULL, \
												   now(), \
												   NULL, \
												   NULL, \
												   $4, \
												   $5, \
												   $6 ) RETURNING id");

  pqxx::result R = W.prepared("insert")
                 (_user_)
                 (security_role)
                 (created_by)
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

void UsersSecurityRoleModel::UpdateUsersSecurityRole(
													std::string	id,
													std::string	_user_,
													std::string	security_role,
													std::string	updated_by,
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
	C.prepare("update", "UPDATE users_security_roles SET \
													_user_ = $2, \
													security_role = $3, \
													updated_by = $4, \
													updated_at = now(), \
													status = $5, \
													situation = $6, \
													description = $7	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (_user_)
                 (security_role)
                 (updated_by)
                 (status)
                 (situation)
                 (description)
         .exec();
	W.commit();
}

void UsersSecurityRoleModel::DeleteUsersSecurityRole(std::string id){
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
	 C.prepare("update", "UPDATE users_security_roles SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
