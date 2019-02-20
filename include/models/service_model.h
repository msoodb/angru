#ifndef ANGRU_SERVICE_MODEL_H_
#define ANGRU_SERVICE_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace angru{
namespace mvc{
namespace model{

class ServiceModel
{
public:
	ServiceModel();
	~ServiceModel();
	static pqxx::result GetServices(int page=1, std::string query="");
	static int GetServicesCount(std::string query="");
	static boost::property_tree::ptree GetServicesJson(int page=1, std::string query="");
  static pqxx::result GetService(std::string id);
	static boost::property_tree::ptree GetServiceJson(std::string id);
	static std::string AddService(
													std::string	pendar,
													std::string	mobile_operator,
													std::string	aggrigator,
													std::string	content_provider,
													std::string	name,
													std::string	title,
													std::string	code,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateService(
													std::string	id,
													std::string	pendar,
													std::string	mobile_operator,
													std::string	aggrigator,
													std::string	content_provider,
													std::string	name,
													std::string	title,
													std::string	code,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteService(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_SERVICE_MODEL_H_
