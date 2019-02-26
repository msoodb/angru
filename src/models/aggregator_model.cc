#include "models/aggregator_model.h"

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

AggregatorModel::AggregatorModel(){}
AggregatorModel::~AggregatorModel(){}

pqxx::result AggregatorModel::GetAggregators(int page, std::string query){
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
									      				code , \
									      				phone , \
									      				email , \
																(select username from users where id = main.created_by) as created_by, \
       													(select username from users where id = main.updated_by) as updated_by, \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM aggregators AS main where deleted_at is NULL ";
	if(!query.empty())
	{
		complete_query += " AND ";
		complete_query +=  query;
	}
	complete_query += " limit ";
	complete_query += std::to_string(OFFSET_COUNT);
	complete_query += " offset ";
	int offset = (page-1)* OFFSET_COUNT ;
	complete_query += std::to_string(offset);
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find").exec();
  W.commit();
	return R;
}

int AggregatorModel::GetAggregatorsCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM aggregators where deleted_at is NULL ";
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

boost::property_tree::ptree AggregatorModel::GetAggregatorsJson(int page, std::string query){
	pqxx::result R = GetAggregators(page, query);
	int result_count = GetAggregatorsCount(query);
	int pageCount = (result_count / OFFSET_COUNT) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree aggregator_node;
	boost::property_tree::ptree aggregators_node;

	for (size_t i = 0; i < R.size(); i++) {
		aggregator_node.put("id", R[i][0]);
		aggregator_node.put("name", R[i][1]);
		aggregator_node.put("title", R[i][2]);
		aggregator_node.put("code", R[i][3]);
		aggregator_node.put("phone", R[i][4]);
		aggregator_node.put("email", R[i][5]);
		aggregator_node.put("created_by", R[i][6]);
		aggregator_node.put("updated_by", R[i][7]);
		aggregator_node.put("created_at", R[i][8]);
		aggregator_node.put("updated_at", R[i][9]);
		aggregator_node.put("details", R[i][10]);
		aggregator_node.put("status", R[i][11]);
		aggregator_node.put("situation", R[i][12]);
		aggregator_node.put("description", R[i][13]);
		aggregators_node.push_back(std::make_pair("", aggregator_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("offset", OFFSET_COUNT);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", aggregators_node);
	return result_node;
}

pqxx::result AggregatorModel::GetAggregator(std::string id){
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
									      				code , \
									      				phone , \
									      				email , \
																(select username from users where id = main.created_by) as created_by, \
       													(select username from users where id = main.updated_by) as updated_by, \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM aggregators AS main where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree AggregatorModel::GetAggregatorJson(std::string id){
	pqxx::result R = GetAggregator(id);
	boost::property_tree::ptree aggregator_node;

	if(R.size() == 1){
		aggregator_node.put("id", R[0][0]);
		aggregator_node.put("name", R[0][1]);
		aggregator_node.put("title", R[0][2]);
		aggregator_node.put("code", R[0][3]);
		aggregator_node.put("phone", R[0][4]);
		aggregator_node.put("email", R[0][5]);
		aggregator_node.put("created_by", R[0][6]);
		aggregator_node.put("updated_by", R[0][7]);
		aggregator_node.put("created_at", R[0][8]);
		aggregator_node.put("updated_at", R[0][9]);
		aggregator_node.put("details", R[0][10]);
		aggregator_node.put("status", R[0][11]);
		aggregator_node.put("situation", R[0][12]);
		aggregator_node.put("description", R[0][13]);
	}
	return aggregator_node;
}

std::string AggregatorModel::AddAggregator(
													std::string	name,
													std::string	title,
													std::string	code,
													std::string	phone,
													std::string	email,
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
	C.prepare("insert", "INSERT INTO aggregators( \
													id, \
													name, \
													title, \
													code, \
													phone, \
													email, \
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
												   NULL, \
												   NULL, \
												   now(), \
												   NULL, \
												   NULL, \
												   $7, \
												   $8, \
												   $9, \
												   $10 ) RETURNING id");

  pqxx::result R = W.prepared("insert")
                 (name)
                 (title)
                 (code)
                 (phone)
                 (email)
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

void AggregatorModel::UpdateAggregator(
													std::string	id,
													std::string	name,
													std::string	title,
													std::string	code,
													std::string	phone,
													std::string	email,
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
	C.prepare("update", "UPDATE aggregators SET \
													name = $2, \
													title = $3, \
													code = $4, \
													phone = $5, \
													email = $6, \
													updated_by = $7, \
													updated_at = now(), \
													details = $8, \
													status = $9, \
													situation = $10, \
													description = $11	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (name)
                 (title)
                 (code)
                 (phone)
                 (email)
                 (updated_by)
                 (details)
                 (status)
                 (situation)
                 (description)
         .exec();
	W.commit();
}

void AggregatorModel::DeleteAggregator(std::string id){
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
	 C.prepare("update", "UPDATE aggregators SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
