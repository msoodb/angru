#ifndef ANGRU_CONTENT_MODEL_H_
#define ANGRU_CONTENT_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class ContentModel
{
public:
	ContentModel();
	~ContentModel();
	static pqxx::result GetContents(int page=1, int limit=LIMIT_COUNT, std::string query="");
	static int GetContentsCount(std::string query="");
	static boost::property_tree::ptree GetContentsJson(int page=1, int limit=LIMIT_COUNT, std::string query="");
  static pqxx::result GetContent(std::string id);
	static boost::property_tree::ptree GetContentJson(std::string id);
	static std::string AddContent(
													std::string	service,
													std::string	channel,
													std::string	publisher,
													int	type,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateContent(
													std::string	id,
													std::string	service,
													std::string	channel,
													std::string	publisher,
													int	type,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteContent(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_CONTENT_MODEL_H_
