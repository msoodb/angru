#ifndef ANGRU_AGGREGATOR_MODEL_H_
#define ANGRU_AGGREGATOR_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace angru{
namespace mvc{
namespace model{

class AggregatorModel
{
public:
	AggregatorModel();
	~AggregatorModel();
	static pqxx::result GetAggregators(int page=1, std::string query="");
	static int GetAggregatorsCount(std::string query="");
	static boost::property_tree::ptree GetAggregatorsJson(int page=1, std::string query="");
  static pqxx::result GetAggregator(std::string id);
	static boost::property_tree::ptree GetAggregatorJson(std::string id);
	static std::string AddAggregator(
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
	static void UpdateAggregator(
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
	static void DeleteAggregator(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_AGGREGATOR_MODEL_H_
