#include "models/content_model.h"

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

ContentModel::ContentModel(){}
ContentModel::~ContentModel(){}

pqxx::result ContentModel::GetContents(int page, int limit, std::string query, std::string order){
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
									      				(select name from services where id = main.service) as  service , \
									      				(select name from channels where id = main.channel) as  channel , \
									      				(select name from publishers where id = main.publisher) as  publisher , \
									      				type , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM contents AS main where deleted_at is NULL ";
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

int ContentModel::GetContentsCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM contents where deleted_at is NULL ";
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

boost::property_tree::ptree ContentModel::GetContentsJson(int page, int limit, std::string query, std::string order){
	pqxx::result R = GetContents(page, limit, query, order);
	int result_count = GetContentsCount(query);
	int pageCount = ((result_count - 1) / limit) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree content_node;
	boost::property_tree::ptree contents_node;

	for (size_t i = 0; i < R.size(); i++) {
		content_node.put("id", R[i][0]);
		content_node.put("service", R[i][1]);
		content_node.put("channel", R[i][2]);
		content_node.put("publisher", R[i][3]);
		content_node.put("type", R[i][4]);
		content_node.put("created_by", R[i][5]);
		content_node.put("updated_by", R[i][6]);
		content_node.put("created_at", R[i][7]);
		content_node.put("updated_at", R[i][8]);
		content_node.put("details", R[i][9]);
		content_node.put("status", R[i][10]);
		content_node.put("situation", R[i][11]);
		content_node.put("description", R[i][12]);
		contents_node.push_back(std::make_pair("", content_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("limit", limit);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", contents_node);
	return result_node;
}

pqxx::result ContentModel::GetContent(std::string id){
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
									      				service , \
									      				channel , \
									      				publisher , \
									      				type , \
(select username from users where id = main.created_by) as  created_by , \
(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM contents AS main where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree ContentModel::GetContentJson(std::string id){
	pqxx::result R = GetContent(id);
	boost::property_tree::ptree content_node;

	if(R.size() == 1){
		content_node.put("id", R[0][0]);
		content_node.put("service", R[0][1]);
		content_node.put("channel", R[0][2]);
		content_node.put("publisher", R[0][3]);
		content_node.put("type", R[0][4]);
		content_node.put("created_by", R[0][5]);
		content_node.put("updated_by", R[0][6]);
		content_node.put("created_at", R[0][7]);
		content_node.put("updated_at", R[0][8]);
		content_node.put("details", R[0][9]);
		content_node.put("status", R[0][10]);
		content_node.put("situation", R[0][11]);
		content_node.put("description", R[0][12]);
	}
	return content_node;
}

std::string ContentModel::AddContent(
													std::string	service,
													std::string	channel,
													std::string	publisher,
													int	type,
													std::string	created_by,
													std::string	details,
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
	C.prepare("insert", "INSERT INTO contents( \
													id, \
													service, \
													channel, \
													publisher, \
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
													 (CASE WHEN $2 = '' THEN NULL ELSE $2 END)::uuid, \
													 (CASE WHEN $3 = '' THEN NULL ELSE $3 END)::uuid, \
												   $4, \
												   $5, \
												   NULL, \
												   NULL, \
												   now(), \
												   NULL, \
												   NULL, \
												   $6, \
												   $7, \
												   $8, \
												   $9 ) RETURNING id");

  pqxx::result R = W.prepared("insert")
                 (service)
                 (channel)
                 (publisher)
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

void ContentModel::UpdateContent(
													std::string	id,
													std::string	service,
													std::string	channel,
													std::string	publisher,
													int	type,
													std::string	updated_by,
													std::string	details,
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
	C.prepare("update", "UPDATE contents SET \
													service = $2, \
													channel = (CASE WHEN $3 = '' THEN  NULL ELSE $3 END)::uuid, \
													publisher = (CASE WHEN $4 = '' THEN  NULL ELSE $4 END)::uuid, \
													type = $5, \
													updated_by = $6, \
													updated_at = now(), \
													details = $7, \
													status = $8, \
													situation = $9, \
													description = $10	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (service)
                 (channel)
                 (publisher)
                 (type)
                 (updated_by)
                 (details)
                 (status)
                 (situation)
                 (description)
         .exec();
	W.commit();
}

void ContentModel::DeleteContent(std::string id){
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
	 C.prepare("update", "UPDATE contents SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
