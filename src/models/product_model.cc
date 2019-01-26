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
	std::string complete_query = "SELECT id, name, title, code, price, details, expirable, \
																		taxable, active, description, created_at, updated_at, \
																		tags, \
																		(select count(product_documents.id) from product_documents where product_id = products.id \
																		and deleted_at is NULL) as attachments \
																		FROM products where deleted_at is NULL ";
	if(!query.empty())
	{
		complete_query += " AND ";
		complete_query +=  query;
	}
	complete_query += " order by id ";
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
		product_node.put("details", R[i][5]);
		product_node.put("expirable", R[i][6]);
		product_node.put("taxable", R[i][7]);
		product_node.put("active", R[i][8]);
		product_node.put("description", R[i][9]);
		product_node.put("created_at", R[i][10]);
		product_node.put("updated_at", R[i][11]);
		product_node.put("tags", R[i][12]);
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
  C.prepare("find", "SELECT id, name, title, code, price, details, expirable, \
										  		taxable, active, description, created_at, updated_at, \
														tags FROM products where id = $1 and deleted_at is NULL ");
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
		product_node.put("details", R[0][5]);
		product_node.put("expirable", R[0][6]);
		product_node.put("taxable", R[0][7]);
		product_node.put("active", R[0][8]);
		product_node.put("description", R[0][9]);
		product_node.put("created_at", R[0][10]);
		product_node.put("updated_at", R[0][11]);
		product_node.put("tags", R[0][12]);
	}
	return product_node;
}
void ProductModel::AddProduct( std::string title,
																float price,
																std::string  tags,
																bool expirable,
																std::string details,
																std::string name,
																std::string code,
																bool active,
																bool taxable,
																std::string description	){
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
												(id, title, price, created_at, deleted_at, tags, expirable, details, updated_at, name, code, active, taxable, description) VALUES \
												(DEFAULT, $1, $2, now(), NULL, $3, $4, $5, NULL, $6, $7, $8, $9, $10)");
  pqxx::result R = W.prepared("insert")(title)(price)(tags)(expirable)(details)(name)(code)(active)(taxable)(description).exec();
  W.commit();
}
void ProductModel::UpdateProduct( int id,
																	std::string title,
																	float price,
																	std::string  tags,
																	bool expirable,
																	std::string details,
																	std::string name,
																	std::string code,
																	bool active,
																	bool taxable,
																	std::string description ){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (C.is_open()) {
			 LOG_INFO << "Opened database successfully: " << C.dbname();
			 LOG_INFO << "Connected to database: " << C.dbname();
		 	pqxx::work W(C);
		 	C.prepare("update", "UPDATE products SET \
		 												title = $2, \
														price = $3, \
														tags = $4, \
														expirable = $5, \
														details = $6, \
														updated_at = now(), \
														name = $7, \
														code = $8, \
														active = $9, \
														taxable = $10, \
														description = $11 \
		 												WHERE id = $1");
		   W.prepared("update")(id)(title)(price)(tags)(expirable)(details)(name)(code)(active)(taxable)(description).exec();
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
