#include "models/product_document_model.h"

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

ProductDocumentModel::ProductDocumentModel(){}
ProductDocumentModel::~ProductDocumentModel(){}

pqxx::result ProductDocumentModel::GetProductDocuments(int page, std::string query){
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
									      				product_id , \
									      				name , \
									      				title , \
									      				path , \
									      				size , \
									      				created_at , \
									      				updated_at , \
									      				tags , \
									      				details , \
									      				status , \
									      				description  FROM product_documents where deleted_at is NULL ";
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

int ProductDocumentModel::GetProductDocumentsCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM product_documents where deleted_at is NULL ";
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

boost::property_tree::ptree ProductDocumentModel::GetProductDocumentsJson(int page, std::string query){
	pqxx::result R = GetProductDocuments(page, query);
	int result_count = GetProductDocumentsCount(query);
	int pageCount = (result_count / OFFSET_COUNT) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree product_document_node;
	boost::property_tree::ptree product_documents_node;

	for (size_t i = 0; i < R.size(); i++) {
		product_document_node.put("id", R[i][0]);
		product_document_node.put("product_id", R[i][1]);
		product_document_node.put("name", R[i][2]);
		product_document_node.put("title", R[i][3]);
		product_document_node.put("path", R[i][4]);
		product_document_node.put("size", R[i][5]);
		product_document_node.put("created_at", R[i][6]);
		product_document_node.put("updated_at", R[i][7]);
		product_document_node.put("tags", R[i][8]);
		product_document_node.put("details", R[i][9]);
		product_document_node.put("status", R[i][10]);
		product_document_node.put("description", R[i][11]);
		product_documents_node.push_back(std::make_pair("", product_document_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("offset", OFFSET_COUNT);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", product_documents_node);
	return result_node;
}

pqxx::result ProductDocumentModel::GetProductDocument(int id){
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
									      				product_id , \
									      				name , \
									      				title , \
									      				path , \
									      				size , \
									      				created_at , \
									      				updated_at , \
									      				tags , \
									      				details , \
									      				status , \
									      				description  FROM product_documents where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree ProductDocumentModel::GetProductDocumentJson(int id){
	pqxx::result R = GetProductDocument(id);
	boost::property_tree::ptree product_document_node;

	if(R.size() == 1){
		product_document_node.put("id", R[0][0]);
		product_document_node.put("product_id", R[0][1]);
		product_document_node.put("name", R[0][2]);
		product_document_node.put("title", R[0][3]);
		product_document_node.put("path", R[0][4]);
		product_document_node.put("size", R[0][5]);
		product_document_node.put("created_at", R[0][6]);
		product_document_node.put("updated_at", R[0][7]);
		product_document_node.put("tags", R[0][8]);
		product_document_node.put("details", R[0][9]);
		product_document_node.put("status", R[0][10]);
		product_document_node.put("description", R[0][11]);
	}
	return product_document_node;
}

std::string ProductDocumentModel::AddProductDocument(
													int	product_id,
													std::string	name,
													std::string	title,
													std::string	path,
													float	size,
													std::string	tags,
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
	C.prepare("insert", "INSERT INTO product_documents( \
													id, \
													product_id, \
													name, \
													title, \
													path, \
													size, \
													created_at, \
													deleted_at, \
													updated_at, \
													tags, \
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
												   $8, \
												   $9 ) RETURNING id");

  pqxx::result R = W.prepared("insert")
                 (product_id)
                 (name)
                 (title)
                 (path)
                 (size)
                 (tags)
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

void ProductDocumentModel::UpdateProductDocument(
													int	id,
													int	product_id,
													std::string	name,
													std::string	title,
													std::string	path,
													float	size,
													std::string	tags,
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
	C.prepare("update", "UPDATE product_documents SET \
													product_id = $2, \
													name = $3, \
													title = $4, \
													path = $5, \
													size = $6, \
													updated_at = now(), \
													tags = $7, \
													details = $8, \
													status = $9, \
													description = $10	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (product_id)
                 (name)
                 (title)
                 (path)
                 (size)
                 (tags)
                 (details)
                 (status)
                 (description)
         .exec();
	W.commit();
}

void ProductDocumentModel::DeleteProductDocument(int id){
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
	 C.prepare("update", "UPDATE product_documents SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
