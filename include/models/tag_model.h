#ifndef ANGRU_TAG_MODEL_H_
#define ANGRU_TAG_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class TagModel
{
public:
	TagModel();
	~TagModel();
	static pqxx::result GetTags(int page=1, int limit=LIMIT_COUNT, std::string query="");
	static int GetTagsCount(std::string query="");
	static boost::property_tree::ptree GetTagsJson(int page=1, int limit=LIMIT_COUNT, std::string query="");
  static pqxx::result GetTag(std::string id);
	static boost::property_tree::ptree GetTagJson(std::string id);
	static std::string AddTag(
													std::string	name,
													std::string	title,
													int	type,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateTag(
													std::string	id,
													std::string	name,
													std::string	title,
													int	type,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteTag(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_TAG_MODEL_H_
