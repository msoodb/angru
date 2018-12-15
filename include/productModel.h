// This is start of the header guard. PRODUCT_MODEL_H can be any unique name.  By convention, we use the name of the header file.
#ifndef PRODUCT_MODEL_H
#define PRODUCT_MODEL_H

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>



// This is the content of the .h file, which is where the declarations go
class ProductModel
{
public:
	ProductModel();
	~ProductModel();
	static pqxx::result getProducts(int page=1, std::string query="");
	static boost::property_tree::ptree getProducts_json(int page=1, std::string query="");
  static pqxx::row getProduct(int);
	static boost::property_tree::ptree getProduct_json(int);
	static void addProduct(int, std::string, float, std::string, std::string, std::string);
	static void updateProduct(int, std::string, float, std::string, std::string, std::string);
	static void deleteProduct(int);
};

// This is the end of the header guard
#endif