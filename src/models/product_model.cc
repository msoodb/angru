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
pqxx::result ProductModel::GetProducts(int page, std::string query, bool paging){
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
	std::string complete_query = "SELECT id, title, price, created_at, \
																tags FROM products where deleted_at is NULL ";
	if(!query.empty())
	{
		complete_query += " AND ";
		complete_query +=  query;
	}
	if(!paging){
		complete_query += " limit 20 offset ";
		int offset = (page-1)* OFFSET_COUNT ;
		complete_query += std::to_string(offset);
	}
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find").exec();
  W.commit();
	return R;
}
boost::property_tree::ptree ProductModel::GetProductsJson(int page, std::string query){
	pqxx::result R = GetProducts(page, query);
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
pqxx::row ProductModel::GetProduct(int id){
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
boost::property_tree::ptree ProductModel::GetProductJson(int id){
	pqxx::row r = GetProduct(id);
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
void ProductModel::AddProduct( std::string title,
													float price,
													std::string  tags){
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
	C.prepare("insert", "INSERT INTO products \
												(id, title, price, created_at, deleted_at, tags) VALUES \
												(DEFAULT, $1, $2, now(), NULL, $4)");
  pqxx::result R = W.prepared("insert")(title)(price)(tags).exec();
  W.commit();
}
void ProductModel::UpdateProduct( int id,
													std::string title,
													float price,
													std::string  tags){
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
												title = $2, price = $3, tags = $5 \
												WHERE id = $1");
  W.prepared("update")(id)(title)(price)(tags).exec();
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

void ProductModel::CreateReport() {
	pqxx::result R = GetProducts(1, "", true);
	angru::wrapper::CsvWriter writer("report/products.csv");
	writer.AddData(R);
	R = GetProducts(1, "", true);
	writer.AddData(R);
}

} // model
} // mvc
} // angru

/*
std::cout << "start creating report" << '\n';
std::future<void> rep = std::async(ProductModel::CreateReport);
std::cout << "end creating report" << '\n';
int n;
for (size_t i = 0; i < 10; i++) {
	std::cin >> n;
	std::cout << i+n << '\n';
}
rep.get();
*/

//              Retrieve data in main file
/*
pqxx::result R = Product::GetProducts();
CSVWriter writer("products.csv");
writer.AddData(R);
pqxx::result R2 = Product::GetProduct(1);
writer.AddData(R2);
//Product::AddProduct(32, "m1911", 720.5, weekstart, weekstart, "{book}");
*/
/*Product::AddProduct(30, "m1911", 720.5,
					"2016-06-22 19:10:25-07", "2016-06-22 19:10:25-07", "{gun, handgun, pistol}");*/

/*
int count = 100000;
for (size_t i = 0; i < count; i++) {
	Product::AddProduct(i+30, "m1911", 17.5,
						"2016-06-22 19:10:25-07", "2016-06-22 19:10:25-07", "{gun, handgun, pistol}");
						std::cout << "record : "<< i << '\n';
}*/

/*
try
{
	std::cout<<"setup database connection_string..."<<std::endl;
	angru::wrapper::Postgresql::setup();

	Product::DeleteProduct(30);
	pqxx::result R = Product::GetProducts("id<15");
	CSVWriter writer("products8.csv");
	writer.AddData(R);

	boost::property_tree::ptree product_root = Product::GetProductsJson("id>15 AND id<100");
	JSONWriter product_json_writer("products.json");
	product_json_writer.AddData(product_root);

	boost::property_tree::ptree product_root_1230 = Product::GetProductJson(1230);
	JSONWriter product_json_writer2("products1230.json");
	product_json_writer2.AddData(product_root_1230);
}
*/

/*pqxx::result R = Product::GetProducts(" id <= 12 ");
CSVWriter writer("products12.csv");
writer.AddData(R);

Product::UpdateProduct(30, "m12", 11.5,
					"2016-06-22 19:10:25-07", "2016-06-22 19:10:25-07", "{gun, mechinegun}");

Product::DeleteProduct(33);
*/
