#include "models/channel_model.h"

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

ChannelModel::ChannelModel(){}
ChannelModel::~ChannelModel(){}

pqxx::result ChannelModel::GetChannels(int page, std::string query){
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
									      				(select name from services where id = main.service) as  service , \
									      				(select name from channels where id = main.parent) as  parent , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM channels AS main where deleted_at is NULL ";
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

int ChannelModel::GetChannelsCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM channels where deleted_at is NULL ";
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

boost::property_tree::ptree ChannelModel::GetChannelsJson(int page, std::string query){
	pqxx::result R = GetChannels(page, query);
	int result_count = GetChannelsCount(query);
	int pageCount = (result_count / OFFSET_COUNT) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree channel_node;
	boost::property_tree::ptree channels_node;

	for (size_t i = 0; i < R.size(); i++) {
		channel_node.put("id", R[i][0]);
		channel_node.put("name", R[i][1]);
		channel_node.put("title", R[i][2]);
		channel_node.put("service", R[i][3]);
		channel_node.put("parent", R[i][4]);
		channel_node.put("created_by", R[i][5]);
		channel_node.put("updated_by", R[i][6]);
		channel_node.put("created_at", R[i][7]);
		channel_node.put("updated_at", R[i][8]);
		channel_node.put("details", R[i][9]);
		channel_node.put("status", R[i][10]);
		channel_node.put("situation", R[i][11]);
		channel_node.put("description", R[i][12]);
		channels_node.push_back(std::make_pair("", channel_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("offset", OFFSET_COUNT);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", channels_node);
	return result_node;
}

pqxx::result ChannelModel::GetChannel(std::string id){
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
									      				service , \
									      				parent , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM channels AS main where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree ChannelModel::GetChannelJson(std::string id){
	pqxx::result R = GetChannel(id);
	boost::property_tree::ptree channel_node;

	if(R.size() == 1){
		channel_node.put("id", R[0][0]);
		channel_node.put("name", R[0][1]);
		channel_node.put("title", R[0][2]);
		channel_node.put("service", R[0][3]);
		channel_node.put("parent", R[0][4]);
		channel_node.put("created_by", R[0][5]);
		channel_node.put("updated_by", R[0][6]);
		channel_node.put("created_at", R[0][7]);
		channel_node.put("updated_at", R[0][8]);
		channel_node.put("details", R[0][9]);
		channel_node.put("status", R[0][10]);
		channel_node.put("situation", R[0][11]);
		channel_node.put("description", R[0][12]);
	}
	return channel_node;
}

std::string ChannelModel::AddChannel(
													std::string	name,
													std::string	title,
													std::string	service,
													std::string	parent,
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
	C.prepare("insert", "INSERT INTO channels( \
													id, \
													name, \
													title, \
													service, \
													parent, \
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
												   (CASE WHEN $4 = '' THEN NULL ELSE $4 END)::uuid, \
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
                 (name)
                 (title)
                 (service)
                 (parent)
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

void ChannelModel::UpdateChannel(
													std::string	id,
													std::string	name,
													std::string	title,
													std::string	service,
													std::string	parent,
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
	C.prepare("update", "UPDATE channels SET \
													name = $2, \
													title = $3, \
													service = $4, \
													parent = (CASE WHEN $5 = '' THEN  NULL ELSE $5 END)::uuid, \
													updated_by = $6, \
													updated_at = now(), \
													details = $7, \
													status = $8, \
													situation = $9, \
													description = $10	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (name)
                 (title)
                 (service)
                 (parent)
                 (updated_by)
                 (details)
                 (status)
                 (situation)
                 (description)
         .exec();
	W.commit();
}

void ChannelModel::DeleteChannel(std::string id){
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
	 C.prepare("update", "UPDATE channels SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
