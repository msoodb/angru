#include "models/content_provider_model.h"

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

ContentProviderModel::ContentProviderModel(){}
ContentProviderModel::~ContentProviderModel(){}

pqxx::result ContentProviderModel::GetContentProviders(int page, std::string query){
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
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				description  FROM content_providers where deleted_at is NULL ";
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

int ContentProviderModel::GetContentProvidersCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM content_providers where deleted_at is NULL ";
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

boost::property_tree::ptree ContentProviderModel::GetContentProvidersJson(int page, std::string query){
	pqxx::result R = GetContentProviders(page, query);
	int result_count = GetContentProvidersCount(query);
	int pageCount = (result_count / OFFSET_COUNT) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree content_provider_node;
	boost::property_tree::ptree content_providers_node;

	for (size_t i = 0; i < R.size(); i++) {
		content_provider_node.put("id", R[i][0]);
		content_provider_node.put("name", R[i][1]);
		content_provider_node.put("title", R[i][2]);
		content_provider_node.put("code", R[i][3]);
		content_provider_node.put("phone", R[i][4]);
		content_provider_node.put("email", R[i][5]);
		content_provider_node.put("created_at", R[i][6]);
		content_provider_node.put("updated_at", R[i][7]);
		content_provider_node.put("details", R[i][8]);
		content_provider_node.put("status", R[i][9]);
		content_provider_node.put("description", R[i][10]);
		content_providers_node.push_back(std::make_pair("", content_provider_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("offset", OFFSET_COUNT);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("content_providers", content_providers_node);
	return result_node;
}

pqxx::result ContentProviderModel::GetContentProvider(int id){
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
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				description  FROM content_providers where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree ContentProviderModel::GetContentProviderJson(int id){
	pqxx::result R = GetContentProvider(id);
	boost::property_tree::ptree content_provider_node;

	if(R.size() == 1){
		content_provider_node.put("id", R[0][0]);
		content_provider_node.put("name", R[0][1]);
		content_provider_node.put("title", R[0][2]);
		content_provider_node.put("code", R[0][3]);
		content_provider_node.put("phone", R[0][4]);
		content_provider_node.put("email", R[0][5]);
		content_provider_node.put("created_at", R[0][6]);
		content_provider_node.put("updated_at", R[0][7]);
		content_provider_node.put("details", R[0][8]);
		content_provider_node.put("status", R[0][9]);
		content_provider_node.put("description", R[0][10]);
	}
	return content_provider_node;
}

std::string ContentProviderModel::AddContentProvider(
													std::string	name,
													std::string	title,
													std::string	code,
													std::string	phone,
													std::string	email,
													std::string	details,
													int	status,
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
	C.prepare("insert", "INSERT INTO content_providers( \
													id, \
													name, \
													title, \
													code, \
													phone, \
													email, \
													created_at, \
													deleted_at, \
													updated_at, \
													details, \
													status, \
													description	) VALUES (\
												   DEFAULT, \
												   $1, \
												   $2, \
												   $3, \
												   $4, \
												   $5, \
												   now(), \
												   NULL, \
												   NULL, \
												   $6, \
												   $7, \
												   $8 ) RETURNING id");

  pqxx::result R = W.prepared("insert")
                 (name)
                 (title)
                 (code)
                 (phone)
                 (email)
                 (details)
                 (status)
                 (description)
         .exec();
  W.commit();
	std::string id="";
	if(R.size() == 1){
		id = R[0][0].as<std::string>();
	}
	return id;
}

void ContentProviderModel::UpdateContentProvider(
													int	id,
													std::string	name,
													std::string	title,
													std::string	code,
													std::string	phone,
													std::string	email,
													std::string	details,
													int	status,
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
	C.prepare("update", "UPDATE content_providers SET \
													name = $2, \
													title = $3, \
													code = $4, \
													phone = $5, \
													email = $6, \
													updated_at = now(), \
													details = $7, \
													status = $8, \
													description = $9	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (name)
                 (title)
                 (code)
                 (phone)
                 (email)
                 (details)
                 (status)
                 (description)
         .exec();
	W.commit();
}

void ContentProviderModel::DeleteContentProvider(int id){
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
	 C.prepare("update", "UPDATE content_providers SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
