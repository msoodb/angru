#ifndef ANGRU_MOBILE_OPERATOR_MODEL_H_
#define ANGRU_MOBILE_OPERATOR_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class MobileOperatorModel
{
public:
	MobileOperatorModel();
	~MobileOperatorModel();
	static pqxx::result GetMobileOperators(int page=1, int limit=LIMIT_COUNT, std::string query="");
	static int GetMobileOperatorsCount(std::string query="");
	static boost::property_tree::ptree GetMobileOperatorsJson(int page=1, int limit=LIMIT_COUNT, std::string query="");
  static pqxx::result GetMobileOperator(std::string id);
	static boost::property_tree::ptree GetMobileOperatorJson(std::string id);
	static std::string AddMobileOperator(
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
	static void UpdateMobileOperator(
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
	static void DeleteMobileOperator(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_MOBILE_OPERATOR_MODEL_H_
