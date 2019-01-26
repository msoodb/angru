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
pqxx::result ProductDocumentModel::GetProductDocuments(int product_id){
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
	std::string complete_query = "SELECT id, name, title, path, \
                                        extention, size, created_at, \
                                        updated_at, tags, details, active, description \
                                        FROM product_documents \
                                        where deleted_at is NULL and product_id=$1 \
                                        order by id";
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find")(product_id).exec();
  W.commit();
	return R;
}
int ProductDocumentModel::GetProductDocumentsCount(int product_id){
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
	std::string complete_query = "SELECT count(id) FROM product_documents where product_id=$1 and deleted_at is NULL";
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find")(product_id).exec();
  W.commit();
	return (R[0][0]).as<int>();
}
boost::property_tree::ptree ProductDocumentModel::GetProductDocumentsJson(int product_id){
	pqxx::result R = GetProductDocuments(product_id);
	int result_count = GetProductDocumentsCount(product_id);

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree product_document_node;
	boost::property_tree::ptree product_documents_node;

	for (size_t i = 0; i < R.size(); i++) {
		product_document_node.put("id", R[i][0]);
		product_document_node.put("name", R[i][1]);
		product_document_node.put("title", R[i][2]);
		product_document_node.put("path", R[i][3]);
		product_document_node.put("extention", R[i][4]);
		product_document_node.put("size", R[i][5]);
		product_document_node.put("created_at", R[i][6]);
		product_document_node.put("updated_at", R[i][7]);
		product_document_node.put("tags", R[i][8]);
		product_document_node.put("details", R[i][9]);
		product_document_node.put("active", R[i][10]);
		product_document_node.put("description", R[i][11]);
		product_documents_node.push_back(std::make_pair("", product_document_node));
	}
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("product_documents", product_documents_node);
	return result_node;
}
pqxx::result ProductDocumentModel::GetProductDocument(int id, int product_id){
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
  std::string complete_query = "SELECT id, name, title, path, \
                                        extention, size, created_at, \
                                        updated_at, tags, details, active, description \
                                        FROM product_documents \
                                        where deleted_at is NULL and id=$1 and product_id=$2";
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find")(id)(product_id).exec();
	W.commit();
	return R;
}
boost::property_tree::ptree ProductDocumentModel::GetProductDocumentJson(int id, int product_id){
	pqxx::result R = GetProductDocument(id, product_id);
	boost::property_tree::ptree product_document_node;

	if(R.size() == 1){
		product_document_node.put("id", R[0][0]);
	  product_document_node.put("name", R[0][1]);
	  product_document_node.put("title", R[0][2]);
	  product_document_node.put("path", R[0][3]);
	  product_document_node.put("extention", R[0][4]);
	  product_document_node.put("size", R[0][5]);
	  product_document_node.put("created_at", R[0][6]);
	  product_document_node.put("updated_at", R[0][7]);
	  product_document_node.put("tags", R[0][8]);
	  product_document_node.put("details", R[0][9]);
	  product_document_node.put("active", R[0][10]);
	  product_document_node.put("description", R[0][11]);
	}
	return product_document_node;
}
void ProductDocumentModel::AddProductDocument( int product_id,
																			std::string name,
																			std::string title,
																			std::string path,
																			std::string extention,
																			float size,
																			std::string tags,
																			std::string details,
																			bool active,
																			std::string description){
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
	C.prepare("insert", "INSERT INTO product_documents \
												(id, product_id, name, title, path, extention, size, created_at, deleted_at, \
												updated_at, tags, details, active, description) VALUES \
												(DEFAULT, $1, $2, $3, $4, $5, $6, now(), NULL, NULL, $7, $8, $9, $10)");
  pqxx::result R = W.prepared("insert")(product_id)(name)(title)(path)(extention)(size)(tags)(details)(active)(description).exec();
  W.commit();
}
void ProductDocumentModel::UpdateProductDocument( int id,
												int product_id,
												std::string name,
												std::string title,
												std::string path,
												std::string extention,
												float size,
												std::string tags,
												std::string details,
												bool active,
												std::string description){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
			 LOG_INFO << "Connected to database: " << C.dbname();
		 	pqxx::work W(C);
		 	C.prepare("update", "UPDATE product_documents SET \
		 												name = $3, \
														title = $4, \
														path = $5, \
														extention = $6, \
														size = $7, \
														updated_at = now(), \
														tags = $8, \
														details = $9, \
														active = $10, \
														description = $11 \
		 												WHERE id = $1 and product_id = $2");
		   W.prepared("update")(id)(product_id)(name)(title)(path)(extention)(size)(tags)(details)(active)(description).exec();
		   W.commit();
		} else {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
		std::cout << e.what() << '\n';
		LOG_ERROR << e.what();
	}
}
void ProductDocumentModel::DeleteProductDocument(int id, int product_id){
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
												WHERE id = $1 and product_id=$2");
  W.prepared("update")(id)(product_id).exec();
  W.commit();
}

} // model
} // mvc
} // angru
