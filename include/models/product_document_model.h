#ifndef ANGRU_PRODUCT_DOCUMENT_MODEL_H_
#define ANGRU_PRODUCT_DOCUMENT_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace angru{
namespace mvc{
namespace model{

class ProductDocumentModel
{
public:
	ProductDocumentModel();
	~ProductDocumentModel();
	static pqxx::result GetProductDocuments(int page=1, std::string query="");
	static int GetProductDocumentsCount(std::string query="");
	static boost::property_tree::ptree GetProductDocumentsJson(int page=1, std::string query="");
  static pqxx::result GetProductDocument(int);
	static boost::property_tree::ptree GetProductDocumentJson(int);
	static std::string AddProductDocument(
													int	product_id,
													std::string	name,
													std::string	title,
													std::string	path,
													float	size,
													std::string	tags,
													std::string	details,
													int	status,
													std::string	description);
	static void UpdateProductDocument(
													int	id,
													int	product_id,
													std::string	name,
													std::string	title,
													std::string	path,
													float	size,
													std::string	tags,
													std::string	details,
													int	status,
													std::string	description);
	static void DeleteProductDocument(int);
};

} // model
} // mvc
} // angru

#endif // ANGRU_PRODUCT_DOCUMENT_MODEL_H_
