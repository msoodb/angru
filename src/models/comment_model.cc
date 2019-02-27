#include "models/comment_model.h"

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

CommentModel::CommentModel(){}
CommentModel::~CommentModel(){}

pqxx::result CommentModel::GetComments(int page, int limit, std::string query){
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
									      				member , \
									      				content , \
									      				comment , \
									      				reply_to , \
(select username from users where id = main.created_by) as  created_by , \
(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM comments AS main where deleted_at is NULL ";
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
  pqxx::result R = W.prepared("find").exec();
  W.commit();
	return R;
}

int CommentModel::GetCommentsCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM comments where deleted_at is NULL ";
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

boost::property_tree::ptree CommentModel::GetCommentsJson(int page, int limit, std::string query){
	pqxx::result R = GetComments(page, limit, query);
	int result_count = GetCommentsCount(query);
	int pageCount = (result_count / limit) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree comment_node;
	boost::property_tree::ptree comments_node;

	for (size_t i = 0; i < R.size(); i++) {
		comment_node.put("id", R[i][0]);
		comment_node.put("member", R[i][1]);
		comment_node.put("content", R[i][2]);
		comment_node.put("comment", R[i][3]);
		comment_node.put("reply_to", R[i][4]);
		comment_node.put("created_by", R[i][5]);
		comment_node.put("updated_by", R[i][6]);
		comment_node.put("created_at", R[i][7]);
		comment_node.put("updated_at", R[i][8]);
		comment_node.put("details", R[i][9]);
		comment_node.put("status", R[i][10]);
		comment_node.put("situation", R[i][11]);
		comment_node.put("description", R[i][12]);
		comments_node.push_back(std::make_pair("", comment_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("limit", limit);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", comments_node);
	return result_node;
}

pqxx::result CommentModel::GetComment(std::string id){
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
									      				member , \
									      				content , \
									      				comment , \
									      				reply_to , \
(select username from users where id = main.created_by) as  created_by , \
(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM comments AS main where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree CommentModel::GetCommentJson(std::string id){
	pqxx::result R = GetComment(id);
	boost::property_tree::ptree comment_node;

	if(R.size() == 1){
		comment_node.put("id", R[0][0]);
		comment_node.put("member", R[0][1]);
		comment_node.put("content", R[0][2]);
		comment_node.put("comment", R[0][3]);
		comment_node.put("reply_to", R[0][4]);
		comment_node.put("created_by", R[0][5]);
		comment_node.put("updated_by", R[0][6]);
		comment_node.put("created_at", R[0][7]);
		comment_node.put("updated_at", R[0][8]);
		comment_node.put("details", R[0][9]);
		comment_node.put("status", R[0][10]);
		comment_node.put("situation", R[0][11]);
		comment_node.put("description", R[0][12]);
	}
	return comment_node;
}

std::string CommentModel::AddComment(
													std::string	member,
													std::string	content,
													std::string	comment,
													std::string	reply_to,
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
	C.prepare("insert", "INSERT INTO comments( \
													id, \
													member, \
													content, \
													comment, \
													reply_to, \
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
                 (member)
                 (content)
                 (comment)
                 (reply_to)
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

void CommentModel::UpdateComment(
													std::string	id,
													std::string	member,
													std::string	content,
													std::string	comment,
													std::string	reply_to,
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
	C.prepare("update", "UPDATE comments SET \
													member = $2, \
													content = $3, \
													comment = $4, \
													reply_to = $5, \
													updated_by = $6, \
													updated_at = now(), \
													details = $7, \
													status = $8, \
													situation = $9, \
													description = $10	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (member)
                 (content)
                 (comment)
                 (reply_to)
                 (updated_by)
                 (details)
                 (status)
                 (situation)
                 (description)
         .exec();
	W.commit();
}

void CommentModel::DeleteComment(std::string id){
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
	 C.prepare("update", "UPDATE comments SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
