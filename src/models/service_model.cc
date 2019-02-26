#include "models/service_model.h"

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

ServiceModel::ServiceModel(){}
ServiceModel::~ServiceModel(){}

pqxx::result ServiceModel::GetServices(int page, std::string query){
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
									      				pendar , \
									      				(select name from mobile_operators where id = main.mobile_operator) as mobile_operator , \
									      				(select name from aggregators where id = main.aggregator) as aggregator , \
									      				(select name from content_providers where id = main.content_provider) as content_provider , \
									      				name , \
									      				title , \
									      				code , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM services AS main where deleted_at is NULL ";
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

int ServiceModel::GetServicesCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM services where deleted_at is NULL ";
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

boost::property_tree::ptree ServiceModel::GetServicesJson(int page, std::string query){
	pqxx::result R = GetServices(page, query);
	int result_count = GetServicesCount(query);
	int pageCount = (result_count / OFFSET_COUNT) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree service_node;
	boost::property_tree::ptree services_node;

	for (size_t i = 0; i < R.size(); i++) {
		service_node.put("id", R[i][0]);
		service_node.put("pendar", R[i][1]);
		service_node.put("mobile_operator", R[i][2]);
		service_node.put("aggregator", R[i][3]);
		service_node.put("content_provider", R[i][4]);
		service_node.put("name", R[i][5]);
		service_node.put("title", R[i][6]);
		service_node.put("code", R[i][7]);
		service_node.put("created_by", R[i][8]);
		service_node.put("updated_by", R[i][9]);
		service_node.put("created_at", R[i][10]);
		service_node.put("updated_at", R[i][11]);
		service_node.put("details", R[i][12]);
		service_node.put("status", R[i][13]);
		service_node.put("situation", R[i][14]);
		service_node.put("description", R[i][15]);
		services_node.push_back(std::make_pair("", service_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("offset", OFFSET_COUNT);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", services_node);
	return result_node;
}

pqxx::result ServiceModel::GetService(std::string id){
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
									      				pendar , \
									      				mobile_operator , \
									      				aggregator , \
									      				content_provider , \
									      				name , \
									      				title , \
									      				code , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM services AS main where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree ServiceModel::GetServiceJson(std::string id){
	pqxx::result R = GetService(id);
	boost::property_tree::ptree service_node;

	if(R.size() == 1){
		service_node.put("id", R[0][0]);
		service_node.put("pendar", R[0][1]);
		service_node.put("mobile_operator", R[0][2]);
		service_node.put("aggregator", R[0][3]);
		service_node.put("content_provider", R[0][4]);
		service_node.put("name", R[0][5]);
		service_node.put("title", R[0][6]);
		service_node.put("code", R[0][7]);
		service_node.put("created_by", R[0][8]);
		service_node.put("updated_by", R[0][9]);
		service_node.put("created_at", R[0][10]);
		service_node.put("updated_at", R[0][11]);
		service_node.put("details", R[0][12]);
		service_node.put("status", R[0][13]);
		service_node.put("situation", R[0][14]);
		service_node.put("description", R[0][15]);
	}
	return service_node;
}

std::string ServiceModel::AddService(
													std::string	pendar,
													std::string	mobile_operator,
													std::string	aggregator,
													std::string	content_provider,
													std::string	name,
													std::string	title,
													std::string	code,
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
	C.prepare("insert", "INSERT INTO services( \
													id, \
													pendar, \
													mobile_operator, \
													aggregator, \
													content_provider, \
													name, \
													title, \
													code, \
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
                 (pendar)
                 (mobile_operator)
                 (aggregator)
                 (content_provider)
                 (name)
                 (title)
                 (code)
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

void ServiceModel::UpdateService(
													std::string	id,
													std::string	pendar,
													std::string	mobile_operator,
													std::string	aggregator,
													std::string	content_provider,
													std::string	name,
													std::string	title,
													std::string	code,
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
	C.prepare("update", "UPDATE services SET \
													pendar = $2, \
													mobile_operator = $3, \
													aggregator = $4, \
													content_provider = $5, \
													name = $6, \
													title = $7, \
													code = $8, \
													updated_by = $9, \
													updated_at = now(), \
													details = $10, \
													status = $11, \
													situation = $12, \
													description = $13	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (pendar)
                 (mobile_operator)
                 (aggregator)
                 (content_provider)
                 (name)
                 (title)
                 (code)
                 (updated_by)
                 (details)
                 (status)
                 (situation)
                 (description)
         .exec();
	W.commit();
}

void ServiceModel::DeleteService(std::string id){
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
	 C.prepare("update", "UPDATE services SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
