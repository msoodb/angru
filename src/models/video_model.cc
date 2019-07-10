#include "models/video_model.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "wrappers/csv_writer.h"
#include "tools/global.h"

namespace angru{
namespace mvc{
namespace model{

VideoModel::VideoModel(){}
VideoModel::~VideoModel(){}


pqxx::result VideoModel::GetVideos(int page, int limit, std::string query, std::string order){
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
									      				main.id , \
																main.content , \
									      				main.name , \
									      				main.title , \
									      				main.path , \
									      				main.size , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				main.created_at , \
									      				main.updated_at , \
									      				main.details , \
									      				main.status , \
									      				main.situation , \
																main.description, \
																(select name from services where id = contents.service) as  service , \
																(select name from channels where id = contents.channel) as  channel , \
																(select name from publishers where id = contents.publisher) as  publisher \
									      				FROM videos AS main join contents \
																	on main.content = contents.id \
																where main.deleted_at is NULL ";
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

int VideoModel::GetVideosCount(std::string query){
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
	std::string complete_query = "SELECT count(main.id) \
																FROM videos AS main join contents on main.content = contents.id\
																where main.deleted_at is NULL ";
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

boost::property_tree::ptree VideoModel::GetVideosJson(int page, int limit, std::string query, std::string order){
	pqxx::result R = GetVideos(page, limit, query, order);
	int result_count = GetVideosCount(query);
	int pageCount = ((result_count - 1) / limit) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree video_node;
	boost::property_tree::ptree videos_node;

	for (size_t i = 0; i < R.size(); i++) {
		video_node.put("id", R[i][0]);
		video_node.put("content", R[i][1]);
		video_node.put("name", R[i][2]);
		video_node.put("title", R[i][3]);
		video_node.put("path", R[i][4]);
		video_node.put("size", R[i][5]);
		video_node.put("created_by", R[i][6]);
		video_node.put("updated_by", R[i][7]);
		video_node.put("created_at", R[i][8]);
		video_node.put("updated_at", R[i][9]);
		video_node.put("details", R[i][10]);
		video_node.put("status", R[i][11]);
		video_node.put("situation", R[i][12]);
		video_node.put("description", R[i][13]);
		video_node.put("service", R[i][14]);
		video_node.put("channel", R[i][15]);
		video_node.put("publisher", R[i][16]);
		videos_node.push_back(std::make_pair("", video_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("limit", limit);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", videos_node);
	return result_node;
}

pqxx::result VideoModel::GetVideo(std::string id){
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
											main.id , \
											main.content , \
											main.name , \
											main.title , \
											main.path , \
											main.path as url , \
											main.size , \
											(select username from users where id = main.created_by) as  created_by , \
											(select username from users where id = main.updated_by) as  updated_by , \
											main.created_at , \
											main.updated_at , \
											main.details , \
											main.status , \
											main.situation , \
											main.description, \
											contents.service , \
											contents.channel , \
											contents.publisher \
											FROM videos AS main join contents \
												on main.content = contents.id \
											where main.id = $1 and main.deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

std::string VideoModel::GetContent(std::string id){
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
											content \
											FROM videos \
											where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	std::string content_id = "";
	if(R.size() == 1){
		content_id = R[0][0].as<std::string>();
	}
	return content_id;
}


boost::property_tree::ptree VideoModel::GetVideoJson(std::string id){
	pqxx::result R = GetVideo(id);
	boost::property_tree::ptree video_node;

	if(R.size() == 1){
		video_node.put("id", R[0][0]);
		video_node.put("content", R[0][1]);
		video_node.put("name", R[0][2]);
		video_node.put("title", R[0][3]);
		video_node.put("path", R[0][4]);
		video_node.put("url", angru::tools::global::m_cdn + R[0][5].as<std::string>());
		video_node.put("size", R[0][6]);
		video_node.put("created_by", R[0][7]);
		video_node.put("updated_by", R[0][8]);
		video_node.put("created_at", R[0][9]);
		video_node.put("updated_at", R[0][10]);
		video_node.put("details", R[0][11]);
		video_node.put("status", R[0][12]);
		video_node.put("situation", R[0][13]);
		video_node.put("description", R[0][14]);
		video_node.put("service", R[0][15]);
		video_node.put("channel", R[0][16]);
		video_node.put("publisher", R[0][17]);
	}
	return video_node;
}

std::string VideoModel::AddVideo(
													std::string	content,
													std::string	name,
													std::string	title,
													std::string	path,
													float	size,
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
	C.prepare("insert", "INSERT INTO videos( \
													id, \
													content, \
													name, \
													title, \
													path, \
													size, \
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
                 (content)
                 (name)
                 (title)
                 (path)
                 (size)
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

void VideoModel::UpdateVideo(
													std::string	id,
													std::string	content,
													std::string	name,
													std::string	title,
													std::string	path,
													float	size,
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
	C.prepare("update", "UPDATE videos SET \
													content = $2, \
													name = $3, \
													title = $4, \
													path = $5, \
													size = $6, \
													updated_by = $7, \
													updated_at = now(), \
													details = $8, \
													status = $9, \
													situation = $10, \
													description = $11	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (content)
                 (name)
                 (title)
                 (path)
                 (size)
                 (updated_by)
                 (details)
                 (status)
                 (situation)
                 (description)
         .exec();
	W.commit();
}

void VideoModel::DeleteVideo(std::string id){
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
	 C.prepare("update", "UPDATE videos SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
