#ifndef ANGRU_PRODUCT_MODEL_H_
#define ANGRU_PRODUCT_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class ProductModel
{
public:
	ProductModel();
	~ProductModel();
	static pqxx::result GetProducts(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
	static int GetProductsCount(std::string query="");
	static boost::property_tree::ptree GetProductsJson(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
  static pqxx::result GetProduct(int);
	static boost::property_tree::ptree GetProductJson(int);
	static std::string AddProduct(
													std::string	name,
													std::string	title,
													std::string	code,
													float	price,
													bool	expirable,
													bool	taxable,
													std::string	tags,
													std::string	details,
													int	status,
													std::string	description);
	static void UpdateProduct(
													int	id,
													std::string	name,
													std::string	title,
													std::string	code,
													float	price,
													bool	expirable,
													bool	taxable,
													std::string	tags,
													std::string	details,
													int	status,
													std::string	description);
	static void DeleteProduct(int);
};

} // model
} // mvc
} // angru

#endif // ANGRU_PRODUCT_MODEL_H_
