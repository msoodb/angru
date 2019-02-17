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
  static pqxx::result GetContentProvider(std::string id);
	static boost::property_tree::ptree GetContentProviderJson(std::string id);
	static std::string AddContentProvider(
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
	static void UpdateContentProvider(
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
	static void DeleteContentProvider(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_CONTENT_PROVIDER_MODEL_H_
