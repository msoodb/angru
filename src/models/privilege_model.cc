#include "models/privilege_model.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "wrappers/csv_writer.h"
#include "models/user_model.h"

namespace angru{
namespace mvc{
namespace model{

PrivilegeModel::PrivilegeModel(){}
PrivilegeModel::~PrivilegeModel(){}

bool PrivilegeModel::AuthorizationCheck(std::string user_id, std::string entity_name, int action){
	bool result = false;
	if(user_id == ""){
		return false;
	}
	result = angru::mvc::model::UserModel::IsZeus(user_id);
	if(result){       //zeus
		return true;
	}
  try
  {
    pqxx::result PrivilegeStrings = GetPrivilegeStrings(user_id, entity_name);
    char ch = '0';
    for (size_t i = 0; i < PrivilegeStrings.size(); i++) {
      std::string privilege = PrivilegeStrings[i][0].as<std::string>();
      ch = ch | privilege[action];
    }
    if(ch=='1'){
      result = true;
    }
    return result;
  }
  catch (std::exception const& e){
    return false;
  }
  catch(...)
  {
    return false;
  }
}

pqxx::result PrivilegeModel::GetPrivilegeStrings(std::string user_id, std::string entity_name){
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
									      				public.privileges.privilege_string \
																FROM public.users join public.users_security_roles on public.users.id = public.users_security_roles._user_ \
																join public.security_roles on public.users_security_roles.security_role = public.security_roles.id \
																join public.privileges on public.privileges.security_role = public.security_roles.id \
																join public.entities on public.privileges.entity = public.entities.id \
																WHERE public.users.id = $1 and public.entities.name = $2 \
																AND public.users.deleted_at is NULL \
																AND public.users_security_roles.deleted_at is NULL \
																AND public.privileges.deleted_at is NULL \
																AND public.entities.deleted_at is NULL ";
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find")(user_id)(entity_name).exec();
	W.commit();
	return R;
}

pqxx::result PrivilegeModel::GetPrivileges(int page, int limit, std::string query){
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
									      				(select name from security_roles where id = main.security_role) as  security_role , \
																(select name from entities where id = main.entity) as  entity , \
									      				privilege_string , \
(select username from users where id = main.created_by) as  created_by , \
(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				status , \
									      				situation , \
									      				description  FROM privileges AS main where deleted_at is NULL ";
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

int PrivilegeModel::GetPrivilegesCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM privileges where deleted_at is NULL ";
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

boost::property_tree::ptree PrivilegeModel::GetPrivilegesJson(int page, int limit, std::string query){
	pqxx::result R = GetPrivileges(page, limit, query);
	int result_count = GetPrivilegesCount(query);
	int pageCount = ((result_count - 1) / limit) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree privilege_node;
	boost::property_tree::ptree privileges_node;

	for (size_t i = 0; i < R.size(); i++) {
		privilege_node.put("id", R[i][0]);
		privilege_node.put("security_role", R[i][1]);
		privilege_node.put("entity", R[i][2]);
		privilege_node.put("privilege_string", R[i][3]);
		privilege_node.put("created_by", R[i][4]);
		privilege_node.put("updated_by", R[i][5]);
		privilege_node.put("created_at", R[i][6]);
		privilege_node.put("updated_at", R[i][7]);
		privilege_node.put("status", R[i][8]);
		privilege_node.put("situation", R[i][9]);
		privilege_node.put("description", R[i][10]);
		privileges_node.push_back(std::make_pair("", privilege_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("limit", limit);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", privileges_node);
	return result_node;
}

pqxx::result PrivilegeModel::GetPrivilege(std::string id){
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
									      				security_role , \
									      				entity , \
									      				privilege_string , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				status , \
									      				situation , \
									      				description  FROM privileges AS main where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree PrivilegeModel::GetPrivilegeJson(std::string id){
	pqxx::result R = GetPrivilege(id);
	boost::property_tree::ptree privilege_node;

	if(R.size() == 1){
		privilege_node.put("id", R[0][0]);
		privilege_node.put("security_role", R[0][1]);
		privilege_node.put("entity", R[0][2]);
		privilege_node.put("privilege_string", R[0][3]);
		privilege_node.put("created_by", R[0][4]);
		privilege_node.put("updated_by", R[0][5]);
		privilege_node.put("created_at", R[0][6]);
		privilege_node.put("updated_at", R[0][7]);
		privilege_node.put("status", R[0][8]);
		privilege_node.put("situation", R[0][9]);
		privilege_node.put("description", R[0][10]);
	}
	return privilege_node;
}

std::string PrivilegeModel::AddPrivilege(
													std::string	security_role,
													std::string	entity,
													std::string	privilege_string,
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
	C.prepare("insert", "INSERT INTO privileges( \
													id, \
													security_role, \
													entity, \
													privilege_string, \
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
												   $4, \
												   NULL, \
												   NULL, \
												   now(), \
												   NULL, \
												   NULL, \
												   $5, \
												   $6, \
												   $7 ) RETURNING id");

  pqxx::result R = W.prepared("insert")
                 (security_role)
                 (entity)
                 (privilege_string)
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

void PrivilegeModel::UpdatePrivilege(
													std::string	id,
													std::string	security_role,
													std::string	entity,
													std::string	privilege_string,
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
	C.prepare("update", "UPDATE privileges SET \
													security_role = $2, \
													entity = $3, \
													privilege_string = $4, \
													updated_by = $5, \
													updated_at = now(), \
													status = $6, \
													situation = $7, \
													description = $8	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (security_role)
                 (entity)
                 (privilege_string)
                 (updated_by)
                 (status)
                 (situation)
                 (description)
         .exec();
	W.commit();
}

void PrivilegeModel::DeletePrivilege(std::string id){
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
	 C.prepare("update", "UPDATE privileges SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
