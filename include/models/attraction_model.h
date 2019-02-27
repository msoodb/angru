#ifndef ANGRU_ATTRACTION_MODEL_H_
#define ANGRU_ATTRACTION_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class AttractionModel
{
public:
	AttractionModel();
	~AttractionModel();
	static pqxx::result GetAttractions(int page=1, int limit=LIMIT_COUNT, std::string query="");
	static int GetAttractionsCount(std::string query="");
	static boost::property_tree::ptree GetAttractionsJson(int page=1, int limit=LIMIT_COUNT, std::string query="");
  static pqxx::result GetAttraction(std::string id);
	static boost::property_tree::ptree GetAttractionJson(std::string id);
	static std::string AddAttraction(
													std::string	member,
													std::string	content,
													int	attraction,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateAttraction(
													std::string	id,
													std::string	member,
													std::string	content,
													int	attraction,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteAttraction(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_ATTRACTION_MODEL_H_
