#ifndef ANGRU_PUBLISHER_MODEL_H_
#define ANGRU_PUBLISHER_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class PublisherModel
{
public:
	PublisherModel();
	~PublisherModel();
	static pqxx::result GetPublishers(int page=1, int limit=LIMIT_COUNT, std::string query="");
	static int GetPublishersCount(std::string query="");
	static boost::property_tree::ptree GetPublishersJson(int page=1, int limit=LIMIT_COUNT, std::string query="");
  static pqxx::result GetPublisher(std::string id);
	static boost::property_tree::ptree GetPublisherJson(std::string id);
	static std::string AddPublisher(
													std::string	admin,
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
	static void UpdatePublisher(
													std::string	id,
													std::string	admin,
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
	static void DeletePublisher(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_PUBLISHER_MODEL_H_
