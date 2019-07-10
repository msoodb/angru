#include "models/tags_playlist_model.h"

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

TagsPlaylistModel::TagsPlaylistModel(){}
TagsPlaylistModel::~TagsPlaylistModel(){}

pqxx::result TagsPlaylistModel::GetTagsPlaylists(int page, int limit, std::string query, std::string order){
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
									      				(select name from tags where id = main.tag) as  tag , \
									      				(select name from playlists where id = main.playlist) as  playlist , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				status , \
									      				situation , \
									      				description  FROM tags_playlists AS main where deleted_at is NULL ";
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

int TagsPlaylistModel::GetTagsPlaylistsCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM tags_playlists where deleted_at is NULL ";
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

boost::property_tree::ptree TagsPlaylistModel::GetTagsPlaylistsJson(int page, int limit, std::string query, std::string order){
	pqxx::result R = GetTagsPlaylists(page, limit, query, order);
	int result_count = GetTagsPlaylistsCount(query);
	int pageCount = ((result_count - 1) / limit) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree tags_playlist_node;
	boost::property_tree::ptree tags_playlists_node;

	for (size_t i = 0; i < R.size(); i++) {
		tags_playlist_node.put("id", R[i][0]);
		tags_playlist_node.put("tag", R[i][1]);
		tags_playlist_node.put("playlist", R[i][2]);
		tags_playlist_node.put("created_by", R[i][3]);
		tags_playlist_node.put("updated_by", R[i][4]);
		tags_playlist_node.put("created_at", R[i][5]);
		tags_playlist_node.put("updated_at", R[i][6]);
		tags_playlist_node.put("status", R[i][7]);
		tags_playlist_node.put("situation", R[i][8]);
		tags_playlist_node.put("description", R[i][9]);
		tags_playlists_node.push_back(std::make_pair("", tags_playlist_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("limit", limit);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", tags_playlists_node);
	return result_node;
}

pqxx::result TagsPlaylistModel::GetTagsPlaylist(std::string id){
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
									      				tag , \
									      				playlist , \
(select username from users where id = main.created_by) as  created_by , \
(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				status , \
									      				situation , \
									      				description  FROM tags_playlists AS main where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree TagsPlaylistModel::GetTagsPlaylistJson(std::string id){
	pqxx::result R = GetTagsPlaylist(id);
	boost::property_tree::ptree tags_playlist_node;

	if(R.size() == 1){
		tags_playlist_node.put("id", R[0][0]);
		tags_playlist_node.put("tag", R[0][1]);
		tags_playlist_node.put("playlist", R[0][2]);
		tags_playlist_node.put("created_by", R[0][3]);
		tags_playlist_node.put("updated_by", R[0][4]);
		tags_playlist_node.put("created_at", R[0][5]);
		tags_playlist_node.put("updated_at", R[0][6]);
		tags_playlist_node.put("status", R[0][7]);
		tags_playlist_node.put("situation", R[0][8]);
		tags_playlist_node.put("description", R[0][9]);
	}
	return tags_playlist_node;
}

std::string TagsPlaylistModel::AddTagsPlaylist(
													std::string	tag,
													std::string	playlist,
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
	C.prepare("insert", "INSERT INTO tags_playlists( \
													id, \
													tag, \
													playlist, \
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
                 (tag)
                 (playlist)
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

void TagsPlaylistModel::UpdateTagsPlaylist(
													std::string	id,
													std::string	tag,
													std::string	playlist,
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
	C.prepare("update", "UPDATE tags_playlists SET \
													tag = $2, \
													playlist = $3, \
													updated_by = $4, \
													updated_at = now(), \
													status = $5, \
													situation = $6, \
													description = $7	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (tag)
                 (playlist)
                 (updated_by)
                 (status)
                 (situation)
                 (description)
         .exec();
	W.commit();
}

void TagsPlaylistModel::DeleteTagsPlaylist(std::string id){
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
	 C.prepare("update", "UPDATE tags_playlists SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
