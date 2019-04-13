#include "models/playlist_model.h"

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

PlaylistModel::PlaylistModel(){}
PlaylistModel::~PlaylistModel(){}

pqxx::result PlaylistModel::GetAllPlaylists(int page, int limit, std::string query, std::string order){
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
									      				(select name from services where id = main.service) as service , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM playlists AS main where deleted_at is NULL ";
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

pqxx::result PlaylistModel::GetPlaylists(int page, int limit, std::string service, std::string query){
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
									      				(select name from services where id = main.service) as service , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM playlists AS main where deleted_at is NULL \
																AND (CASE WHEN $1 = '' THEN service is NULL ELSE service=$1::uuid END) ";
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
  pqxx::result R = W.prepared("find")(service).exec();
  W.commit();
	return R;
}

int PlaylistModel::GetAllPlaylistsCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM playlists where deleted_at is NULL ";
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

int PlaylistModel::GetPlaylistsCount(std::string service, std::string query){
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
	std::string complete_query = "SELECT count(id) FROM playlists where deleted_at is NULL \
																AND (CASE WHEN $1 = '' THEN service is NULL ELSE service=$1::uuid END) ";
	if(!query.empty())
	{
		complete_query += " AND ";
		complete_query +=  query;
	}
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find")(service).exec();
  W.commit();
	return (R[0][0]).as<int>();
}

boost::property_tree::ptree PlaylistModel::GetAllPlaylistsJson(int page, int limit, std::string query, std::string order){
	pqxx::result R = GetAllPlaylists(page, limit, query, order);
	int result_count = GetAllPlaylistsCount(query);
	int pageCount = ((result_count - 1) / limit) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree playlist_node;
	boost::property_tree::ptree playlists_node;

	for (size_t i = 0; i < R.size(); i++) {
		playlist_node.put("id", R[i][0]);
		playlist_node.put("name", R[i][1]);
		playlist_node.put("title", R[i][2]);
		playlist_node.put("service", R[i][3]);
		playlist_node.put("created_by", R[i][4]);
		playlist_node.put("updated_by", R[i][5]);
		playlist_node.put("created_at", R[i][6]);
		playlist_node.put("updated_at", R[i][7]);
		playlist_node.put("details", R[i][8]);
		playlist_node.put("status", R[i][9]);
		playlist_node.put("situation", R[i][10]);
		playlist_node.put("description", R[i][11]);
		playlists_node.push_back(std::make_pair("", playlist_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("limit", limit);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", playlists_node);
	return result_node;
}

boost::property_tree::ptree PlaylistModel::GetPlaylistsJson(int page, int limit, std::string service, std::string query){
	pqxx::result R = GetPlaylists(page, limit, service, query);
	int result_count = GetPlaylistsCount(service, query);
	int pageCount = ((result_count - 1) / limit) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree playlist_node;
	boost::property_tree::ptree playlists_node;

	for (size_t i = 0; i < R.size(); i++) {
		playlist_node.put("id", R[i][0]);
		playlist_node.put("name", R[i][1]);
		playlist_node.put("title", R[i][2]);
		playlist_node.put("service", R[i][3]);
		playlist_node.put("created_by", R[i][4]);
		playlist_node.put("updated_by", R[i][5]);
		playlist_node.put("created_at", R[i][6]);
		playlist_node.put("updated_at", R[i][7]);
		playlist_node.put("details", R[i][8]);
		playlist_node.put("status", R[i][9]);
		playlist_node.put("situation", R[i][10]);
		playlist_node.put("description", R[i][11]);
		playlists_node.push_back(std::make_pair("", playlist_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("limit", limit);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", playlists_node);
	return result_node;
}

pqxx::result PlaylistModel::GetPlaylist(std::string id){
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
(select username from users where id = main.created_by) as  created_by , \
(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM playlists AS main where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree PlaylistModel::GetPlaylistJson(std::string id){
	pqxx::result R = GetPlaylist(id);
	boost::property_tree::ptree playlist_node;

	if(R.size() == 1){
		playlist_node.put("id", R[0][0]);
		playlist_node.put("name", R[0][1]);
		playlist_node.put("title", R[0][2]);
		playlist_node.put("service", R[0][3]);
		playlist_node.put("created_by", R[0][4]);
		playlist_node.put("updated_by", R[0][5]);
		playlist_node.put("created_at", R[0][6]);
		playlist_node.put("updated_at", R[0][7]);
		playlist_node.put("details", R[0][8]);
		playlist_node.put("status", R[0][9]);
		playlist_node.put("situation", R[0][10]);
		playlist_node.put("description", R[0][11]);
	}
	return playlist_node;
}

std::string PlaylistModel::AddPlaylist(
													std::string	name,
													std::string	title,
													std::string	service,
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
	C.prepare("insert", "INSERT INTO playlists( \
													id, \
													name, \
													title, \
													service, \
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
												   NULL, \
												   NULL, \
												   now(), \
												   NULL, \
												   NULL, \
												   $5, \
												   $6, \
												   $7, \
												   $8 ) RETURNING id");

  pqxx::result R = W.prepared("insert")
                 (name)
                 (title)
                 (service)
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

void PlaylistModel::UpdatePlaylist(
													std::string	id,
													std::string	name,
													std::string	title,
													std::string	service,
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
	C.prepare("update", "UPDATE playlists SET \
													name = $2, \
													title = $3, \
													service = $4, \
													updated_by = $5, \
													updated_at = now(), \
													details = $6, \
													status = $7, \
													situation = $8, \
													description = $9	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (name)
                 (title)
                 (service)
                 (updated_by)
                 (details)
                 (status)
                 (situation)
                 (description)
         .exec();
	W.commit();
}

void PlaylistModel::DeletePlaylist(std::string id){
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
	 C.prepare("update", "UPDATE playlists SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
