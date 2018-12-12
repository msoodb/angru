#include <iostream>
#include <string>
#include <pqxx/pqxx>

#include "_error.h"
#include "_log.h"
#include "_PostgreSQL.h"

#include "product.h"


Product::Product(){
}
Product::~Product(){
}
pqxx::result Product::getProducts(){
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
	pqxx::result R =
		W.exec("SELECT id, title, price, created_at, deleted_at, tags FROM products");
		return R;
}
pqxx::result Product::getProducts(std::string query){
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
																deleted_at, tags FROM products where " + query;
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find").exec();
  W.commit();
	return R;
}
pqxx::row Product::getProduct(int id){
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
  C.prepare("find", "SELECT id, title, price, created_at, deleted_at, tags FROM products where id = $1");
  pqxx::result R = W.prepared("find")(id).exec();
	pqxx::row r;
	if (R.size() == 1){
		r = R[0];
	}
  W.commit();
	return r;
}
void Product::addProduct( int id,
													std::string title,
													float price,
													std::string  created_at,
													std::string  deleted_at,
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
												($1, $2, $3, $4, $5, $6)");
  pqxx::result R = W.prepared("insert")(id)(title)(price)(created_at)(deleted_at)(tags).exec();
  W.commit();
}
void Product::updateProduct( int id,
													std::string title,
													float price,
													std::string  created_at,
													std::string  deleted_at,
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
												title = $2, price = $3, created_at = $4, deleted_at = $5, tags = $6 \
												WHERE id = $1");
  W.prepared("update")(id)(title)(price)(created_at)(deleted_at)(tags).exec();
  W.commit();
}
void Product::deleteProduct(int id){
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
  C.prepare("delete", "DELETE FROM products where id = $1");
  W.prepared("delete")(id).exec();
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

/*pqxx::result R = Product::getProducts(" id <= 12 ");
CSVWriter writer("products12.csv");
writer.addData(R);

Product::updateProduct(30, "m12", 11.5,
					"2016-06-22 19:10:25-07", "2016-06-22 19:10:25-07", "{gun, mechinegun}");

Product::deleteProduct(33);
*/
