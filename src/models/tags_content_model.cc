#include "models/tags_content_model.h"

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

TagsContentModel::TagsContentModel(){}
TagsContentModel::~TagsContentModel(){}

pqxx::result TagsContentModel::GetTagsContents(int page, int limit, std::string query, std::string order){
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
									      				(select name from contents where id = main.content) as  content , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				status , \
									      				situation , \
									      				description  FROM tags_contents AS main where deleted_at is NULL ";
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

int TagsContentModel::GetTagsContentsCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM tags_contents where deleted_at is NULL ";
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

boost::property_tree::ptree TagsContentModel::GetTagsContentsJson(int page, int limit, std::string query, std::string order){
	pqxx::result R = GetTagsContents(page, limit, query, order);
	int result_count = GetTagsContentsCount(query);
	int pageCount = ((result_count - 1) / limit) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree tags_content_node;
	boost::property_tree::ptree tags_contents_node;

	for (size_t i = 0; i < R.size(); i++) {
		tags_content_node.put("id", R[i][0]);
		tags_content_node.put("tag", R[i][1]);
		tags_content_node.put("content", R[i][2]);
		tags_content_node.put("created_by", R[i][3]);
		tags_content_node.put("updated_by", R[i][4]);
		tags_content_node.put("created_at", R[i][5]);
		tags_content_node.put("updated_at", R[i][6]);
		tags_content_node.put("status", R[i][7]);
		tags_content_node.put("situation", R[i][8]);
		tags_content_node.put("description", R[i][9]);
		tags_contents_node.push_back(std::make_pair("", tags_content_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("limit", limit);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", tags_contents_node);
	return result_node;
}

pqxx::result TagsContentModel::GetTagsContent(std::string id){
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
									      				content , \
(select username from users where id = main.created_by) as  created_by , \
(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				status , \
									      				situation , \
									      				description  FROM tags_contents AS main where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree TagsContentModel::GetTagsContentJson(std::string id){
	pqxx::result R = GetTagsContent(id);
	boost::property_tree::ptree tags_content_node;

	if(R.size() == 1){
		tags_content_node.put("id", R[0][0]);
		tags_content_node.put("tag", R[0][1]);
		tags_content_node.put("content", R[0][2]);
		tags_content_node.put("created_by", R[0][3]);
		tags_content_node.put("updated_by", R[0][4]);
		tags_content_node.put("created_at", R[0][5]);
		tags_content_node.put("updated_at", R[0][6]);
		tags_content_node.put("status", R[0][7]);
		tags_content_node.put("situation", R[0][8]);
		tags_content_node.put("description", R[0][9]);
	}
	return tags_content_node;
}

std::string TagsContentModel::AddTagsContent(
													std::string	tag,
													std::string	content,
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
	C.prepare("insert", "INSERT INTO tags_contents( \
													id, \
													tag, \
													content, \
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
                 (content)
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

void TagsContentModel::UpdateTagsContent(
													std::string	id,
													std::string	tag,
													std::string	content,
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
	C.prepare("update", "UPDATE tags_contents SET \
													tag = $2, \
													content = $3, \
													updated_by = $4, \
													updated_at = now(), \
													status = $5, \
													situation = $6, \
													description = $7	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (tag)
                 (content)
                 (updated_by)
                 (status)
                 (situation)
                 (description)
         .exec();
	W.commit();
}

void TagsContentModel::DeleteTagsContent(std::string id){
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
	 C.prepare("update", "UPDATE tags_contents SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
