#include "models/entitie_model.h"

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

EntitieModel::EntitieModel(){}
EntitieModel::~EntitieModel(){}

pqxx::result EntitieModel::GetEntities(int page, int limit, std::string query, std::string order){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (!C.is_open()) {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	pqxx::work W(C);
	std::string complete_query = "SELECT \
									      				id , \
									      				name , \
									      				title , \
(select username from users where id = main.created_by) as  created_by , \
(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				status , \
									      				situation , \
									      				description  FROM entities AS main where deleted_at is NULL ";
	if(!query.empty())
	{
		complete_query += " AND ";
		complete_query +=  query;
	}
	if(!order.empty())
	{
		complete_query += " ORDER BY ";
		complete_query +=  order;
	}
	complete_query += " limit ";
	complete_query += std::to_string(limit);
	complete_query += " offset ";
	int offset = (page-1)* limit ;
	complete_query += std::to_string(offset);
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find").exec();
  W.commit();
	return R;
}

int EntitieModel::GetEntitiesCount(std::string query){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (!C.is_open()) {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	pqxx::work W(C);
	std::string complete_query = "SELECT count(id) FROM entities where deleted_at is NULL ";
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

boost::property_tree::ptree EntitieModel::GetEntitiesJson(int page, int limit, std::string query, std::string order){
	pqxx::result R = GetEntities(page, limit, query, order);
	int result_count = GetEntitiesCount(query);
	int pageCount = ((result_count - 1) / limit) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree entitie_node;
	boost::property_tree::ptree entities_node;

	for (size_t i = 0; i < R.size(); i++) {
		entitie_node.put("id", R[i][0]);
		entitie_node.put("name", R[i][1]);
		entitie_node.put("title", R[i][2]);
		entitie_node.put("created_by", R[i][3]);
		entitie_node.put("updated_by", R[i][4]);
		entitie_node.put("created_at", R[i][5]);
		entitie_node.put("updated_at", R[i][6]);
		entitie_node.put("status", R[i][7]);
		entitie_node.put("situation", R[i][8]);
		entitie_node.put("description", R[i][9]);
		entities_node.push_back(std::make_pair("", entitie_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("limit", limit);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", entities_node);
	return result_node;
}

pqxx::result EntitieModel::GetEntitie(std::string id){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (!C.is_open()) {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	pqxx::work W(C);
  C.prepare("find", "SELECT \
									      				id , \
									      				name , \
									      				title , \
(select username from users where id = main.created_by) as  created_by , \
(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				status , \
									      				situation , \
									      				description  FROM entities AS main where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree EntitieModel::GetEntitieJson(std::string id){
	pqxx::result R = GetEntitie(id);
	boost::property_tree::ptree entitie_node;

	if(R.size() == 1){
		entitie_node.put("id", R[0][0]);
		entitie_node.put("name", R[0][1]);
		entitie_node.put("title", R[0][2]);
		entitie_node.put("created_by", R[0][3]);
		entitie_node.put("updated_by", R[0][4]);
		entitie_node.put("created_at", R[0][5]);
		entitie_node.put("updated_at", R[0][6]);
		entitie_node.put("status", R[0][7]);
		entitie_node.put("situation", R[0][8]);
		entitie_node.put("description", R[0][9]);
	}
	return entitie_node;
}

std::string EntitieModel::AddEntitie(
													std::string	name,
													std::string	title,
													std::string	created_by,
													int	status,
													int	situation,
													std::string	description){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (!C.is_open()) {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	pqxx::work W(C);
	C.prepare("insert", "INSERT INTO entities( \
													id, \
													name, \
													title, \
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
                 (name)
                 (title)
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

void EntitieModel::UpdateEntitie(
													std::string	id,
													std::string	name,
													std::string	title,
													std::string	updated_by,
													int	status,
													int	situation,
													std::string	description ){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (!C.is_open()) {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	pqxx::work W(C);
	C.prepare("update", "UPDATE entities SET \
													name = $2, \
													title = $3, \
													updated_by = $4, \
													updated_at = now(), \
													status = $5, \
													situation = $6, \
													description = $7	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (name)
                 (title)
                 (updated_by)
                 (status)
                 (situation)
                 (description)
         .exec();
	W.commit();
}

void EntitieModel::DeleteEntitie(std::string id){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (!C.is_open()) {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	 pqxx::work W(C);
	 C.prepare("update", "UPDATE entities SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
