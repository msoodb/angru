#ifndef ANGRU_CONTENT_PROVIDER_MODEL_H_
#define ANGRU_CONTENT_PROVIDER_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace angru{
namespace mvc{
namespace model{

class Content_providerModel
{
public:
	Content_providerModel();
	~Content_providerModel();
	static pqxx::result GetContent_providers(int page=1, std::string query="");
	static int GetContent_providersCount(std::string query="");
	static boost::property_tree::ptree GetContent_providersJson(int page=1, std::string query="");
  static pqxx::result GetContent_provider(int);
	static boost::property_tree::ptree GetContent_providerJson(int);
	static std::string AddContent_provider(
													std::string	name,
													std::string	title,
													std::string	phone,
													std::string	email,
													std::string	details,
													std::string	description);
	static void UpdateContent_provider(
													int	id,
													std::string	name,
													std::string	title,
													std::string	phone,
													std::string	email,
													std::string	details,
													std::string	description);
	static void DeleteContent_provider(int);
};

} // model
} // mvc
} // angru

#endif // ANGRU_CONTENT_PROVIDER_MODEL_H_
