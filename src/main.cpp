#include <iostream>
#include <vector>
#include <algorithm>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "_error.h"
#include "_log.h"
#include "student.h"
#include "_CSVWriter.h"
#include "_JSONWriter.h"
#include "product.h"
#include "_PostgreSQL.h"

int main(int argc, char const *argv[])
{
	std::cout<<"angru version .010 Check Logfile..."<<std::endl;
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
	catch(const _error& e)
	{
    LOG_ERROR << e.what();
		return 1;
	}
	catch(...)
	{
    LOG_ERROR << "Error: unknown exception";
		return 2;
	}
	return 0;
}
