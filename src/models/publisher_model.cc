#include "models/publisher_model.h"

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

PublisherModel::PublisherModel(){}
PublisherModel::~PublisherModel(){}

pqxx::result PublisherModel::GetPublishers(int page, std::string query){
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
									      				(select username from users where id = main.admin) as  admin , \
									      				name , \
									      				title , \
									      				code , \
									      				phone , \
									      				email , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM publishers AS main where deleted_at is NULL ";
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

int PublisherModel::GetPublishersCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM publishers where deleted_at is NULL ";
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

boost::property_tree::ptree PublisherModel::GetPublishersJson(int page, std::string query){
	pqxx::result R = GetPublishers(page, query);
	int result_count = GetPublishersCount(query);
	int pageCount = (result_count / OFFSET_COUNT) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree publisher_node;
	boost::property_tree::ptree publishers_node;

	for (size_t i = 0; i < R.size(); i++) {
		publisher_node.put("id", R[i][0]);
		publisher_node.put("admin", R[i][1]);
		publisher_node.put("name", R[i][2]);
		publisher_node.put("title", R[i][3]);
		publisher_node.put("code", R[i][4]);
		publisher_node.put("phone", R[i][5]);
		publisher_node.put("email", R[i][6]);
		publisher_node.put("created_by", R[i][7]);
		publisher_node.put("updated_by", R[i][8]);
		publisher_node.put("created_at", R[i][9]);
		publisher_node.put("updated_at", R[i][10]);
		publisher_node.put("details", R[i][11]);
		publisher_node.put("status", R[i][12]);
		publisher_node.put("situation", R[i][13]);
		publisher_node.put("description", R[i][14]);
		publishers_node.push_back(std::make_pair("", publisher_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("offset", OFFSET_COUNT);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", publishers_node);
	return result_node;
}

pqxx::result PublisherModel::GetPublisher(std::string id){
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
									      				admin , \
									      				name , \
									      				title , \
									      				code , \
									      				phone , \
									      				email , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM publishers AS main where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree PublisherModel::GetPublisherJson(std::string id){
	pqxx::result R = GetPublisher(id);
	boost::property_tree::ptree publisher_node;

	if(R.size() == 1){
		publisher_node.put("id", R[0][0]);
		publisher_node.put("admin", R[0][1]);
		publisher_node.put("name", R[0][2]);
		publisher_node.put("title", R[0][3]);
		publisher_node.put("code", R[0][4]);
		publisher_node.put("phone", R[0][5]);
		publisher_node.put("email", R[0][6]);
		publisher_node.put("created_by", R[0][7]);
		publisher_node.put("updated_by", R[0][8]);
		publisher_node.put("created_at", R[0][9]);
		publisher_node.put("updated_at", R[0][10]);
		publisher_node.put("details", R[0][11]);
		publisher_node.put("status", R[0][12]);
		publisher_node.put("situation", R[0][13]);
		publisher_node.put("description", R[0][14]);
	}
	return publisher_node;
}

std::string PublisherModel::AddPublisher(
													std::string	admin,
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
	C.prepare("insert", "INSERT INTO publishers( \
													id, \
													admin, \
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
												   $7, \
												   NULL, \
												   NULL, \
												   now(), \
												   NULL, \
												   NULL, \
												   $8, \
												   $9, \
												   $10, \
												   $11 ) RETURNING id");

  pqxx::result R = W.prepared("insert")
                 (admin)
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

void PublisherModel::UpdatePublisher(
													std::string	id,
													std::string	admin,
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
	C.prepare("update", "UPDATE publishers SET \
													admin = $2, \
													name = $3, \
													title = $4, \
													code = $5, \
													phone = $6, \
													email = $7, \
													updated_by = $8, \
													updated_at = now(), \
													details = $9, \
													status = $10, \
													situation = $11, \
													description = $12	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (admin)
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

void PublisherModel::DeletePublisher(std::string id){
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
	 C.prepare("update", "UPDATE publishers SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
