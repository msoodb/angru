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

class ContentProviderModel
{
public:
	ContentProviderModel();
	~ContentProviderModel();
	static pqxx::result GetContentProviders(int page=1, std::string query="");
	static int GetContentProvidersCount(std::string query="");
	static boost::property_tree::ptree GetContentProvidersJson(int page=1, std::string query="");
  static pqxx::result GetContentProvider(int);
	static boost::property_tree::ptree GetContentProviderJson(int);
	static std::string AddContentProvider(
													std::string	name,
													std::string	title,
													std::string	code,
													std::string	phone,
													std::string	email,
													std::string	details,
													int	status,
													std::string	description);
	static void UpdateContentProvider(
													int	id,
													std::string	name,
													std::string	title,
													std::string	code,
													std::string	phone,
													std::string	email,
													std::string	details,
													int	status,
													std::string	description);
	static void DeleteContentProvider(int);
};

} // model
} // mvc
} // angru

#endif // ANGRU_CONTENT_PROVIDER_MODEL_H_
