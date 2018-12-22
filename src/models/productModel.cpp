#include <iostream>
#include <string>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "_error.h"
#include "_log.h"
#include "_PostgreSQL.h"

#include "productModel.h"


ProductModel::ProductModel(){}
ProductModel::~ProductModel(){}
pqxx::result ProductModel::getProducts(int page, std::string query){
	pqxx::connection C(_PostgreSQL::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
		} else {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const _error &e) {
			LOG_ERROR << e.what();
	}
	LOG_INFO << "Connected to database: " << C.dbname();
	pqxx::work W(C);
	std::string complete_query = "SELECT id, title, price, created_at, \
																tags FROM products where deleted_at is NULL ";
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
boost::property_tree::ptree ProductModel::getProducts_json(int page, std::string query){
	pqxx::result R = getProducts(page, query);
	int count = R.size();
	int pageCount = count / OFFSET_COUNT;
	boost::property_tree::ptree products_node;
	boost::property_tree::ptree product_node;
	for(pqxx::row r : R)
	{
		product_node.put<int>("id", r[0].as<int>());
		product_node.put("title", r[1]);
		product_node.put("price", r[2]);
		product_node.put("created_at", r[3]);
		product_node.put("tags", r[4]);
		products_node.push_back(std::make_pair(r[0].c_str(), product_node));
	}
	return products_node;
}
pqxx::row ProductModel::getProduct(int id){
	pqxx::connection C(_PostgreSQL::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
		} else {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const _error &e) {
			LOG_ERROR << e.what();
	}
	LOG_INFO << "Connected to database: " << C.dbname();
	pqxx::work W(C);
  C.prepare("find", "SELECT id, title, price, created_at, \
								tags FROM products where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	pqxx::row r;
	if (R.size() == 1){
		r = R[0];
	}
  W.commit();
	return r;
}
boost::property_tree::ptree ProductModel::getProduct_json(int id){
	pqxx::row r = getProduct(id);
	boost::property_tree::ptree products_node;
	boost::property_tree::ptree product_node;
	product_node.put("id", r[0]);
	product_node.put("title", r[1]);
	product_node.put("price", r[2]);
	product_node.put("created_at", r[3]);
	product_node.put("tags", r[4]);
	products_node.push_back(std::make_pair(r[0].c_str(), product_node));
	return products_node;
}
void ProductModel::addProduct( std::string title,
													float price,
													std::string  tags){
	pqxx::connection C(_PostgreSQL::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
		} else {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const _error &e) {
			LOG_ERROR << e.what();
	}
	LOG_INFO << "Connected to database: " << C.dbname();
	pqxx::work W(C);
	C.prepare("insert", "INSERT INTO products \
												(id, title, price, created_at, deleted_at, tags) VALUES \
												(DEFAULT, $1, $2, now(), NULL, $4)");
  pqxx::result R = W.prepared("insert")(title)(price)(tags).exec();
  W.commit();
}
void ProductModel::updateProduct( int id,
													std::string title,
													float price,
													std::string  tags){
	pqxx::connection C(_PostgreSQL::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
		} else {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const _error &e) {
			LOG_ERROR << e.what();
	}
	LOG_INFO << "Connected to database: " << C.dbname();
	pqxx::work W(C);
	C.prepare("update", "UPDATE products SET \
												title = $2, price = $3, tags = $5 \
												WHERE id = $1");
  W.prepared("update")(id)(title)(price)(tags).exec();
  W.commit();
}
void ProductModel::deleteProduct(int id){
	pqxx::connection C(_PostgreSQL::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
		} else {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const _error &e) {
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

//              Retrieve data in main file
/*
pqxx::result R = Product::getProducts();
CSVWriter writer("products.csv");
writer.addData(R);
pqxx::result R2 = Product::getProduct(1);
writer.addData(R2);
//Product::addProduct(32, "m1911", 720.5, weekstart, weekstart, "{book}");
*/
/*Product::addProduct(30, "m1911", 720.5,
					"2016-06-22 19:10:25-07", "2016-06-22 19:10:25-07", "{gun, handgun, pistol}");*/

/*
int count = 100000;
for (size_t i = 0; i < count; i++) {
	Product::addProduct(i+30, "m1911", 17.5,
						"2016-06-22 19:10:25-07", "2016-06-22 19:10:25-07", "{gun, handgun, pistol}");
						std::cout << "record : "<< i << '\n';
}*/

/*
try
{
	std::cout<<"setup database connection_string..."<<std::endl;
	_PostgreSQL::setup();

	Product::deleteProduct(30);
	pqxx::result R = Product::getProducts("id<15");
	CSVWriter writer("products8.csv");
	writer.addData(R);

	boost::property_tree::ptree product_root = Product::getProducts_json("id>15 AND id<100");
	JSONWriter product_json_writer("products.json");
	product_json_writer.addData(product_root);

	boost::property_tree::ptree product_root_1230 = Product::getProduct_json(1230);
	JSONWriter product_json_writer2("products1230.json");
	product_json_writer2.addData(product_root_1230);
}
*/

/*pqxx::result R = Product::getProducts(" id <= 12 ");
CSVWriter writer("products12.csv");
writer.addData(R);

Product::updateProduct(30, "m12", 11.5,
					"2016-06-22 19:10:25-07", "2016-06-22 19:10:25-07", "{gun, mechinegun}");

Product::deleteProduct(33);
*/
