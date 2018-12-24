#ifndef ANGRU_PRODUCT_MODEL_H_
#define ANGRU_PRODUCT_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class ProductModel
{
public:
	ProductModel();
	~ProductModel();
	static pqxx::result getProducts(int page=1, std::string query="", bool paging=false);
	static boost::property_tree::ptree getProducts_json(int page=1, std::string query="");
  static pqxx::row getProduct(int);
	static boost::property_tree::ptree getProduct_json(int);
	static void addProduct(std::string, float, std::string);
	static void updateProduct(int, std::string, float, std::string);
	static void deleteProduct(int);
	static void createReport();
};

#endif // ANGRU_PRODUCT_MODEL_H_
