#ifndef ANGRU_PRODUCT_MODEL_H_
#define ANGRU_PRODUCT_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace angru{
namespace mvc{
namespace model{

class ProductModel
{
public:
	ProductModel();
	~ProductModel();
	static pqxx::result GetProducts(int page=1, std::string query="", bool paging=false);
	static boost::property_tree::ptree GetProductsJson(int page=1, std::string query="");
  static pqxx::result GetProduct(int);
	static boost::property_tree::ptree GetProductJson(int);
	static void AddProduct(std::string, float, std::string);
	static void UpdateProduct(int, std::string, float, std::string);
	static void DeleteProduct(int);
	static void CreateReport();
};

} // model
} // mvc
} // angru

#endif // ANGRU_PRODUCT_MODEL_H_
