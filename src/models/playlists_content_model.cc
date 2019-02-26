#include "models/playlists_content_model.h"

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

PlaylistsContentModel::PlaylistsContentModel(){}
PlaylistsContentModel::~PlaylistsContentModel(){}

pqxx::result PlaylistsContentModel::GetPlaylistsContents(int page, std::string query){
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
									      				playlist , \
									      				content , \
(select username from users where id = main.created_by) as  created_by , \
(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM playlists_contents AS main where deleted_at is NULL ";
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

int PlaylistsContentModel::GetPlaylistsContentsCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM playlists_contents where deleted_at is NULL ";
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

boost::property_tree::ptree PlaylistsContentModel::GetPlaylistsContentsJson(int page, std::string query){
	pqxx::result R = GetPlaylistsContents(page, query);
	int result_count = GetPlaylistsContentsCount(query);
	int pageCount = (result_count / OFFSET_COUNT) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree playlists_content_node;
	boost::property_tree::ptree playlists_contents_node;

	for (size_t i = 0; i < R.size(); i++) {
		playlists_content_node.put("id", R[i][0]);
		playlists_content_node.put("playlist", R[i][1]);
		playlists_content_node.put("content", R[i][2]);
		playlists_content_node.put("created_by", R[i][3]);
		playlists_content_node.put("updated_by", R[i][4]);
		playlists_content_node.put("created_at", R[i][5]);
		playlists_content_node.put("updated_at", R[i][6]);
		playlists_content_node.put("details", R[i][7]);
		playlists_content_node.put("status", R[i][8]);
		playlists_content_node.put("situation", R[i][9]);
		playlists_content_node.put("description", R[i][10]);
		playlists_contents_node.push_back(std::make_pair("", playlists_content_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("offset", OFFSET_COUNT);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", playlists_contents_node);
	return result_node;
}

pqxx::result PlaylistsContentModel::GetPlaylistsContent(std::string id){
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
									      				playlist , \
									      				content , \
(select username from users where id = main.created_by) as  created_by , \
(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM playlists_contents AS main where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree PlaylistsContentModel::GetPlaylistsContentJson(std::string id){
	pqxx::result R = GetPlaylistsContent(id);
	boost::property_tree::ptree playlists_content_node;

	if(R.size() == 1){
		playlists_content_node.put("id", R[0][0]);
		playlists_content_node.put("playlist", R[0][1]);
		playlists_content_node.put("content", R[0][2]);
		playlists_content_node.put("created_by", R[0][3]);
		playlists_content_node.put("updated_by", R[0][4]);
		playlists_content_node.put("created_at", R[0][5]);
		playlists_content_node.put("updated_at", R[0][6]);
		playlists_content_node.put("details", R[0][7]);
		playlists_content_node.put("status", R[0][8]);
		playlists_content_node.put("situation", R[0][9]);
		playlists_content_node.put("description", R[0][10]);
	}
	return playlists_content_node;
}

std::string PlaylistsContentModel::AddPlaylistsContent(
													std::string	playlist,
													std::string	content,
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
	C.prepare("insert", "INSERT INTO playlists_contents( \
													id, \
													playlist, \
													content, \
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
												   NULL, \
												   NULL, \
												   now(), \
												   NULL, \
												   NULL, \
												   $4, \
												   $5, \
												   $6, \
												   $7 ) RETURNING id");

  pqxx::result R = W.prepared("insert")
                 (playlist)
                 (content)
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

void PlaylistsContentModel::UpdatePlaylistsContent(
													std::string	id,
													std::string	playlist,
													std::string	content,
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
	C.prepare("update", "UPDATE playlists_contents SET \
													playlist = $2, \
													content = $3, \
													updated_by = $4, \
													updated_at = now(), \
													details = $5, \
													status = $6, \
													situation = $7, \
													description = $8	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (playlist)
                 (content)
                 (updated_by)
                 (details)
                 (status)
                 (situation)
                 (description)
         .exec();
	W.commit();
}

void PlaylistsContentModel::DeletePlaylistsContent(std::string id){
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
	 C.prepare("update", "UPDATE playlists_contents SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
