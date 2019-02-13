#include "models/product_model.h"

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

ProductModel::ProductModel(){}
ProductModel::~ProductModel(){}

pqxx::result ProductModel::GetProducts(int page, std::string query){
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
									      				price , \
									      				created_at , \
									      				updated_at , \
									      				expirable , \
									      				taxable , \
									      				tags , \
									      				details , \
									      				status , \
									      				description, \
																(select count(product_documents.id) from product_documents where product_id = products.id \
																		and deleted_at is NULL) as attachments \
																FROM products where deleted_at is NULL ";
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

int ProductModel::GetProductsCount(std::string query){
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
	std::string complete_query = "SELECT count(id) FROM products where deleted_at is NULL ";
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

boost::property_tree::ptree ProductModel::GetProductsJson(int page, std::string query){
	pqxx::result R = GetProducts(page, query);
	int result_count = GetProductsCount(query);
	int pageCount = (result_count / OFFSET_COUNT) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree product_node;
	boost::property_tree::ptree products_node;

	for (size_t i = 0; i < R.size(); i++) {
		product_node.put("id", R[i][0]);
		product_node.put("name", R[i][1]);
		product_node.put("title", R[i][2]);
		product_node.put("code", R[i][3]);
		product_node.put("price", R[i][4]);
		product_node.put("created_at", R[i][5]);
		product_node.put("updated_at", R[i][6]);
		product_node.put("expirable", R[i][7]);
		product_node.put("taxable", R[i][8]);
		product_node.put("tags", R[i][9]);
		product_node.put("details", R[i][10]);
		product_node.put("status", R[i][11]);
		product_node.put("description", R[i][12]);
		product_node.put("attachments", R[i][13]);
		products_node.push_back(std::make_pair("", product_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("offset", OFFSET_COUNT);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("products", products_node);
	return result_node;
}

pqxx::result ProductModel::GetProduct(int id){
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
									      				price , \
									      				created_at , \
									      				updated_at , \
									      				expirable , \
									      				taxable , \
									      				tags , \
									      				details , \
									      				status , \
									      				description  FROM products where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree ProductModel::GetProductJson(int id){
	pqxx::result R = GetProduct(id);
	boost::property_tree::ptree product_node;

	if(R.size() == 1){
		product_node.put("id", R[0][0]);
		product_node.put("name", R[0][1]);
		product_node.put("title", R[0][2]);
		product_node.put("code", R[0][3]);
		product_node.put("price", R[0][4]);
		product_node.put("created_at", R[0][5]);
		product_node.put("updated_at", R[0][6]);
		product_node.put("expirable", R[0][7]);
		product_node.put("taxable", R[0][8]);
		product_node.put("tags", R[0][9]);
		product_node.put("details", R[0][10]);
		product_node.put("status", R[0][11]);
		product_node.put("description", R[0][12]);
	}
	return product_node;
}

std::string ProductModel::AddProduct(
													std::string	name,
													std::string	title,
													std::string	code,
													float	price,
													bool	expirable,
													bool	taxable,
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
	C.prepare("insert", "INSERT INTO products( \
													id, \
													name, \
													title, \
													code, \
													price, \
													created_at, \
													deleted_at, \
													updated_at, \
													expirable, \
													taxable, \
													tags, \
													details, \
													status, \
													description	) VALUES (\
												   DEFAULT, \
												   $1, \
												   $2, \
												   $3, \
												   $4, \
												   now(), \
												   NULL, \
												   NULL, \
												   $5, \
												   $6, \
												   $7, \
												   $8, \
												   $9, \
												   $10 ) RETURNING id");

  pqxx::result R = W.prepared("insert")
                 (name)
                 (title)
                 (code)
                 (price)
                 (expirable)
                 (taxable)
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

void ProductModel::UpdateProduct(
													int	id,
													std::string	name,
													std::string	title,
													std::string	code,
													float	price,
													bool	expirable,
													bool	taxable,
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
	C.prepare("update", "UPDATE products SET \
													name = $2, \
													title = $3, \
													code = $4, \
													price = $5, \
													updated_at = now(), \
													expirable = $6, \
													taxable = $7, \
													tags = $8, \
													details = $9, \
													status = $10, \
													description = $11	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (name)
                 (title)
                 (code)
                 (price)
                 (expirable)
                 (taxable)
                 (tags)
                 (details)
                 (status)
                 (description)
         .exec();
	W.commit();
}

void ProductModel::DeleteProduct(int id){
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
	 C.prepare("update", "UPDATE products SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
