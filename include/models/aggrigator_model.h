#ifndef ANGRU_AGGRIGATOR_MODEL_H_
#define ANGRU_AGGRIGATOR_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace angru{
namespace mvc{
namespace model{

class AggrigatorModel
{
public:
	AggrigatorModel();
	~AggrigatorModel();
	static pqxx::result GetAggrigators(int page=1, std::string query="");
	static int GetAggrigatorsCount(std::string query="");
	static boost::property_tree::ptree GetAggrigatorsJson(int page=1, std::string query="");
  static pqxx::result GetAggrigator(std::string id);
	static boost::property_tree::ptree GetAggrigatorJson(std::string id);
	static std::string AddAggrigator(
													std::string	name,
													std::string	title,
													std::string	code,
													std::string	phone,
													std::string	email,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateAggrigator(
													std::string	id,
													std::string	name,
													std::string	title,
													std::string	code,
													std::string	phone,
													std::string	email,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteAggrigator(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_AGGRIGATOR_MODEL_H_
