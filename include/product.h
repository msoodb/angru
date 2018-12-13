// This is start of the header guard. PRODUCT_H can be any unique name.  By convention, we use the name of the header file.
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>



// This is the content of the .h file, which is where the declarations go
class Product
{
public:
	Product();
	~Product();
	static pqxx::result getProducts(std::string);
	static boost::property_tree::ptree getProducts_json(std::string);
  static pqxx::row getProduct(int);
	static boost::property_tree::ptree getProduct_json(int);
	static void addProduct(int, std::string, float, std::string, std::string, std::string);
	static void updateProduct(int, std::string, float, std::string, std::string, std::string);
	static void deleteProduct(int);
};

// This is the end of the header guard
#endif
