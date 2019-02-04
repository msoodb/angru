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
	static pqxx::result GetProducts(int page=1, std::string query="");
	static int GetProductsCount(std::string query="");
	static boost::property_tree::ptree GetProductsJson(int page=1, std::string query="");
  static pqxx::result GetProduct(int);
	static boost::property_tree::ptree GetProductJson(int);
	static std::string AddProduct(
													std::string	title,
													float	price,
													std::string	tags,
													bool	expirable,
													std::string	details,
													std::string	name,
													std::string	code,
													bool	active,
													bool	taxable,
													std::string	description);
	static void UpdateProduct(
													int	id,
													std::string	title,
													float	price,
													std::string	tags,
													bool	expirable,
													std::string	details,
													std::string	name,
													std::string	code,
													bool	active,
													bool	taxable,
													std::string	description);
	static void DeleteProduct(int);
};

} // model
} // mvc
} // angru

#endif // ANGRU_PRODUCT_MODEL_H_
