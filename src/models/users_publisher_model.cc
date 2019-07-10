#include "models/users_publisher_model.h"

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

UsersPublisherModel::UsersPublisherModel(){}
UsersPublisherModel::~UsersPublisherModel(){}

pqxx::result UsersPublisherModel::GetUsersPublishers(int page, int limit, std::string query, std::string order){
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
									      				(select username from users where id = main._user_) as  _user_ , \
									      				(select name from publishers where id = main.publisher) as  publisher , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				status , \
									      				situation , \
									      				description  FROM users_publishers AS main where deleted_at is NULL ";
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
	int offset = (page-1)* limit;
	complete_query += std::to_string(offset);
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find").exec();
  W.commit();
	return R;
}

int UsersPublisherModel::GetUsersPublishersCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM users_publishers where deleted_at is NULL ";
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

boost::property_tree::ptree UsersPublisherModel::GetUsersPublishersJson(int page, int limit, std::string query, std::string order){
	pqxx::result R = GetUsersPublishers(page, limit, query, order);
	int result_count = GetUsersPublishersCount(query);
	int pageCount = ((result_count - 1) / limit) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree users_publisher_node;
	boost::property_tree::ptree users_publishers_node;

	for (size_t i = 0; i < R.size(); i++) {
		users_publisher_node.put("id", R[i][0]);
		users_publisher_node.put("_user_", R[i][1]);
		users_publisher_node.put("publisher", R[i][2]);
		users_publisher_node.put("created_by", R[i][3]);
		users_publisher_node.put("updated_by", R[i][4]);
		users_publisher_node.put("created_at", R[i][5]);
		users_publisher_node.put("updated_at", R[i][6]);
		users_publisher_node.put("status", R[i][7]);
		users_publisher_node.put("situation", R[i][8]);
		users_publisher_node.put("description", R[i][9]);
		users_publishers_node.push_back(std::make_pair("", users_publisher_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("limit", limit);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", users_publishers_node);
	return result_node;
}

pqxx::result UsersPublisherModel::GetUsersPublisher(std::string id){
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
									      				_user_ , \
									      				publisher , \
(select username from users where id = main.created_by) as  created_by , \
(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				status , \
									      				situation , \
									      				description  FROM users_publishers AS main where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree UsersPublisherModel::GetUsersPublisherJson(std::string id){
	pqxx::result R = GetUsersPublisher(id);
	boost::property_tree::ptree users_publisher_node;

	if(R.size() == 1){
		users_publisher_node.put("id", R[0][0]);
		users_publisher_node.put("_user_", R[0][1]);
		users_publisher_node.put("publisher", R[0][2]);
		users_publisher_node.put("created_by", R[0][3]);
		users_publisher_node.put("updated_by", R[0][4]);
		users_publisher_node.put("created_at", R[0][5]);
		users_publisher_node.put("updated_at", R[0][6]);
		users_publisher_node.put("status", R[0][7]);
		users_publisher_node.put("situation", R[0][8]);
		users_publisher_node.put("description", R[0][9]);
	}
	return users_publisher_node;
}

std::string UsersPublisherModel::AddUsersPublisher(
													std::string	_user_,
													std::string	publisher,
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
	C.prepare("insert", "INSERT INTO users_publishers( \
													id, \
													_user_, \
													publisher, \
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
                 (publisher)
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

void UsersPublisherModel::UpdateUsersPublisher(
													std::string	id,
													std::string	_user_,
													std::string	publisher,
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
	C.prepare("update", "UPDATE users_publishers SET \
													_user_ = $2, \
													publisher = $3, \
													updated_by = $4, \
													updated_at = now(), \
													status = $5, \
													situation = $6, \
													description = $7	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (_user_)
                 (publisher)
                 (updated_by)
                 (status)
                 (situation)
                 (description)
         .exec();
	W.commit();
}

void UsersPublisherModel::DeleteUsersPublisher(std::string id){
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
	 C.prepare("update", "UPDATE users_publishers SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
