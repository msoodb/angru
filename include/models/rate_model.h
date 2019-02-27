#ifndef ANGRU_RATE_MODEL_H_
#define ANGRU_RATE_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class RateModel
{
public:
	RateModel();
	~RateModel();
	static pqxx::result GetRates(int page=1, int limit=LIMIT_COUNT, std::string query="");
	static int GetRatesCount(std::string query="");
	static boost::property_tree::ptree GetRatesJson(int page=1, int limit=LIMIT_COUNT, std::string query="");
  static pqxx::result GetRate(std::string id);
	static boost::property_tree::ptree GetRateJson(std::string id);
	static std::string AddRate(
													std::string	member,
													std::string	content,
													int	rate,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateRate(
													std::string	id,
													std::string	member,
													std::string	content,
													int	rate,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteRate(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_RATE_MODEL_H_
