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
	static pqxx::result GetProductDocuments(int product_id);
	static int GetProductDocumentsCount(int product_id);
	static boost::property_tree::ptree GetProductDocumentsJson(int product_id);
  static pqxx::result GetProductDocument(int id, int product_id);
	static boost::property_tree::ptree GetProductDocumentJson(int id, int product_id);
	static std::string AddProductDocument(int product_id,
													std::string name,
													std::string path,
													float size,
													std::string tags,
													std::string details,
													bool active,
													std::string description);
	static void UpdateProductDocument(int id,
													int product_id,
													std::string name,
													std::string path,
													float size,
													std::string tags,
													std::string details,
													bool active,
													std::string description);
	static void DeleteProductDocument(int id, int product_id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_PRODUCT_DOCUMENT_MODEL_H_
