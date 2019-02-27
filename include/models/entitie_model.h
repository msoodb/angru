#ifndef ANGRU_ENTITIE_MODEL_H_
#define ANGRU_ENTITIE_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class EntitieModel
{
public:
	EntitieModel();
	~EntitieModel();
	static pqxx::result GetEntities(int page=1, int limit=LIMIT_COUNT, std::string query="");
	static int GetEntitiesCount(std::string query="");
	static boost::property_tree::ptree GetEntitiesJson(int page=1, int limit=LIMIT_COUNT, std::string query="");
  static pqxx::result GetEntitie(std::string id);
	static boost::property_tree::ptree GetEntitieJson(std::string id);
	static std::string AddEntitie(
													std::string	name,
													std::string	title,
													std::string	created_by,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateEntitie(
													std::string	id,
													std::string	name,
													std::string	title,
													std::string	updated_by,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteEntitie(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_ENTITIE_MODEL_H_
