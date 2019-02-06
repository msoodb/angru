#include "models/aggrigator_model.h"

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

AggrigatorModel::AggrigatorModel(){}
AggrigatorModel::~AggrigatorModel(){}

pqxx::result AggrigatorModel::GetAggrigators(int page, std::string query){
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
									      				name , \
									      				title , \
									      				phone , \
									      				email , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				description  FROM aggrigators where deleted_at is NULL ";
	if(!query.empty())
	{
		complete_query += " AND ";
		complete_query +=  query;
	}
	complete_query += " order by id ";
	complete_query += " limit 20 offset ";
	int offset = (page-1)* OFFSET_COUNT ;
	complete_query += std::to_string(offset);
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find").exec();
  W.commit();
	return R;
}

int AggrigatorModel::GetAggrigatorsCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM aggrigators where deleted_at is NULL ";
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

boost::property_tree::ptree AggrigatorModel::GetAggrigatorsJson(int page, std::string query){
	pqxx::result R = GetAggrigators(page, query);
	int result_count = GetAggrigatorsCount(query);
	int pageCount = (result_count / OFFSET_COUNT) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree aggrigator_node;
	boost::property_tree::ptree aggrigators_node;

	for (size_t i = 0; i < R.size(); i++) {
		aggrigator_node.put("id", R[i][0]);
		aggrigator_node.put("name", R[i][1]);
		aggrigator_node.put("title", R[i][2]);
		aggrigator_node.put("phone", R[i][3]);
		aggrigator_node.put("email", R[i][4]);
		aggrigator_node.put("created_at", R[i][5]);
		aggrigator_node.put("updated_at", R[i][6]);
		aggrigator_node.put("details", R[i][7]);
		aggrigator_node.put("description", R[i][8]);
		aggrigators_node.push_back(std::make_pair("", aggrigator_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("offset", OFFSET_COUNT);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("aggrigators", aggrigators_node);
	return result_node;
}

pqxx::result AggrigatorModel::GetAggrigator(int id){
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
									      				name , \
									      				title , \
									      				phone , \
									      				email , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				description  FROM aggrigators where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree AggrigatorModel::GetAggrigatorJson(int id){
	pqxx::result R = GetAggrigator(id);
	boost::property_tree::ptree aggrigator_node;

	if(R.size() == 1){
		aggrigator_node.put("id", R[0][0]);
		aggrigator_node.put("name", R[0][1]);
		aggrigator_node.put("title", R[0][2]);
		aggrigator_node.put("phone", R[0][3]);
		aggrigator_node.put("email", R[0][4]);
		aggrigator_node.put("created_at", R[0][5]);
		aggrigator_node.put("updated_at", R[0][6]);
		aggrigator_node.put("details", R[0][7]);
		aggrigator_node.put("description", R[0][8]);
	}
	return aggrigator_node;
}

std::string AggrigatorModel::AddAggrigator(
													std::string	name, 
													std::string	title, 
													std::string	phone, 
													std::string	email, 
													std::string	details, 
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
	C.prepare("insert", "INSERT INTO aggrigators( \
													id, \
													name, \
													title, \
													phone, \
													email, \
													created_at, \
													deleted_at, \
													updated_at, \
													details, \
													description	) VALUES (\
												   DEFAULT, \
												   $1, \
												   $2, \
												   $3, \
												   $4, \
												   now(), \
												   NULL, \
												   NULL, \
												   $5, \
												   $6 ) RETURNING id");

  pqxx::result R = W.prepared("insert")
                 (name)
                 (title)
                 (phone)
                 (email)
                 (details)
                 (description)
         .exec();
  W.commit();
	std::string id="";
	if(R.size() == 1){
		id = R[0][0].as<std::string>();
	}
	return id;
}

void AggrigatorModel::UpdateAggrigator( 
													int	id,
													std::string	name,
													std::string	title,
													std::string	phone,
													std::string	email,
													std::string	details,
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
	C.prepare("update", "UPDATE aggrigators SET \
													name = $2, \
													title = $3, \
													phone = $4, \
													email = $5, \
													updated_at = now(), \
													details = $6, \
													description = $7	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (name)
                 (title)
                 (phone)
                 (email)
                 (details)
                 (description)
         .exec();
	W.commit();
}

void AggrigatorModel::DeleteAggrigator(int id){
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
	 C.prepare("update", "UPDATE aggrigators SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
