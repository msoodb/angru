#ifndef ANGRU_SUBSCRIPTION_MODEL_H_
#define ANGRU_SUBSCRIPTION_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class SubscriptionModel
{
public:
	SubscriptionModel();
	~SubscriptionModel();
	static pqxx::result GetSubscriptions(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
	static int GetSubscriptionsCount(std::string query="");
	static boost::property_tree::ptree GetSubscriptionsJson(int page=1, int limit=LIMIT_COUNT, std::string query="", std::string order="");
  static pqxx::result GetSubscription(std::string id);
	static boost::property_tree::ptree GetSubscriptionJson(std::string id);
	static std::string AddSubscription(
													std::string	member,
													std::string	service,
													std::string	last_login,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateSubscription(
													std::string	id,
													std::string	member,
													std::string	service,
													std::string	last_login,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteSubscription(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_SUBSCRIPTION_MODEL_H_
