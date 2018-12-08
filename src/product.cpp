#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <pqxx/pqxx>
#include "product.h"
#include "_error.h"
#include "_log.h"
#include "_PostgreSQL.h"

Product::Product()
{
}
Product::~Product()
{
}
void Product::setData()
{
}
void Product::print()
{
}
pqxx::result Product::getProducts()
{
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
pqxx::result Product::getProduct(int id)
{
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
  W.commit();
	return R;
}
void Product::addProduct( int id,
													std::string title,
													float price,
													std::string  created_at,
													std::string  deleted_at,
													std::string  tags)
{
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
  /*C.prepare("insert", "INSERT INTO products (id, title, price, created_at, deleted_at, tags) \
	 										 VALUES($1, $2, $3, $4, $5, $6");*/
	C.prepare("insert", "INSERT INTO products \
												(id, title, price, created_at, deleted_at, tags) VALUES \
												($1, $2, $3, $4, $5, $6)");
  std::cout << "gholi" << '\n';
	//W.prepared("insert")(id)(title)(price)(created_at)(deleted_at)(tags);
	//std::cout<< W.prepared("insert");
  pqxx::result R = W.prepared("insert")(id)(title)(price)(created_at)(deleted_at)(tags).exec();
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
