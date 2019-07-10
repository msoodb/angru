#include "models/subscription_model.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "wrappers/csv_writer.h"

namespace angru{
namespace mvc{
namespace model{

SubscriptionModel::SubscriptionModel(){}
SubscriptionModel::~SubscriptionModel(){}

pqxx::result SubscriptionModel::GetSubscriptions(int page, int limit, std::string query, std::string order){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (!C.is_open()) {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	pqxx::work W(C);
	std::string complete_query = "SELECT \
									      				id , \
									      				(select phone from members where id = main.member) as member , \
									      				(select name from services where id = main.service) as service , \
									      				last_login , \
																(select username from users where id = main.created_by) as  created_by , \
																(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM subscriptions AS main where deleted_at is NULL ";
	if(!query.empty())
	{
		complete_query += " AND ";
		complete_query +=  query;
	}
	if(!order.empty())
	{
		complete_query += " ORDER BY ";
		complete_query +=  order;
	}
	complete_query += " limit ";
	complete_query += std::to_string(limit);
	complete_query += " offset ";
	int offset = (page-1)* limit;
	complete_query += std::to_string(offset);
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find").exec();
  W.commit();
	return R;
}

int SubscriptionModel::GetSubscriptionsCount(std::string query){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (!C.is_open()) {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	pqxx::work W(C);
	std::string complete_query = "SELECT count(id) FROM subscriptions where deleted_at is NULL ";
	if(!query.empty())
	{
		complete_query += " AND ";
		complete_query +=  query;
	}
  C.prepare("find", complete_query);
  pqxx::result R = W.prepared("find").exec();
  W.commit();
	return (R[0][0]).as<int>();
}

boost::property_tree::ptree SubscriptionModel::GetSubscriptionsJson(int page, int limit, std::string query, std::string order){
	pqxx::result R = GetSubscriptions(page, limit, query, order);
	int result_count = GetSubscriptionsCount(query);
	int pageCount = ((result_count - 1) / limit) + 1;

	boost::property_tree::ptree result_node;
	boost::property_tree::ptree info_node;
	boost::property_tree::ptree subscription_node;
	boost::property_tree::ptree subscriptions_node;

	for (size_t i = 0; i < R.size(); i++) {
		subscription_node.put("id", R[i][0]);
		subscription_node.put("member", R[i][1]);
		subscription_node.put("service", R[i][2]);
		subscription_node.put("last_login", R[i][3]);
		subscription_node.put("created_by", R[i][4]);
		subscription_node.put("updated_by", R[i][5]);
		subscription_node.put("created_at", R[i][6]);
		subscription_node.put("updated_at", R[i][7]);
		subscription_node.put("details", R[i][8]);
		subscription_node.put("status", R[i][9]);
		subscription_node.put("situation", R[i][10]);
		subscription_node.put("description", R[i][11]);
		subscriptions_node.push_back(std::make_pair("", subscription_node));
	}
	info_node.put<int>("page", page);
	info_node.put<int>("limit", limit);
	info_node.put<int>("page_count", pageCount);
	info_node.put<int>("result_count", result_count);

	result_node.add_child("info", info_node);
	result_node.add_child("items", subscriptions_node);
	return result_node;
}

pqxx::result SubscriptionModel::GetSubscription(std::string id){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (!C.is_open()) {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	pqxx::work W(C);
  C.prepare("find", "SELECT \
									      				id , \
									      				member , \
									      				service , \
									      				last_login , \
(select username from users where id = main.created_by) as  created_by , \
(select username from users where id = main.updated_by) as  updated_by , \
									      				created_at , \
									      				updated_at , \
									      				details , \
									      				status , \
									      				situation , \
									      				description  FROM subscriptions AS main where id = $1 and deleted_at is NULL ");
  pqxx::result R = W.prepared("find")(id).exec();
	W.commit();
	return R;
}

boost::property_tree::ptree SubscriptionModel::GetSubscriptionJson(std::string id){
	pqxx::result R = GetSubscription(id);
	boost::property_tree::ptree subscription_node;

	if(R.size() == 1){
		subscription_node.put("id", R[0][0]);
		subscription_node.put("member", R[0][1]);
		subscription_node.put("service", R[0][2]);
		subscription_node.put("last_login", R[0][3]);
		subscription_node.put("created_by", R[0][4]);
		subscription_node.put("updated_by", R[0][5]);
		subscription_node.put("created_at", R[0][6]);
		subscription_node.put("updated_at", R[0][7]);
		subscription_node.put("details", R[0][8]);
		subscription_node.put("status", R[0][9]);
		subscription_node.put("situation", R[0][10]);
		subscription_node.put("description", R[0][11]);
	}
	return subscription_node;
}

std::string SubscriptionModel::AddSubscription(
													std::string	member,
													std::string	service,
													std::string	last_login,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (!C.is_open()) {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	pqxx::work W(C);
	C.prepare("insert", "INSERT INTO subscriptions( \
													id, \
													member, \
													service, \
													last_login, \
													created_by, \
													deleted_by, \
													updated_by, \
													created_at, \
													deleted_at, \
													updated_at, \
													details, \
													status, \
													situation, \
													description	) VALUES (\
												   DEFAULT, \
												   $1, \
												   $2, \
												   $3, \
												   $4, \
												   NULL, \
												   NULL, \
												   now(), \
												   NULL, \
												   NULL, \
												   $5, \
												   $6, \
												   $7, \
												   $8 ) RETURNING id");

  pqxx::result R = W.prepared("insert")
                 (member)
                 (service)
                 (last_login)
                 (created_by)
                 (details)
                 (status)
                 (situation)
                 (description)
         .exec();
  W.commit();
	std::string id="";
	if(R.size() == 1){
		id = R[0][0].as<std::string>();
	}
	return id;
}

void SubscriptionModel::UpdateSubscription(
													std::string	id,
													std::string	member,
													std::string	service,
													std::string	last_login,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description ){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (!C.is_open()) {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	pqxx::work W(C);
	C.prepare("update", "UPDATE subscriptions SET \
													member = $2, \
													service = $3, \
													last_login = $4, \
													updated_by = $5, \
													updated_at = now(), \
													details = $6, \
													status = $7, \
													situation = $8, \
													description = $9	WHERE id = $1");
	W.prepared("update")
                 (id)
                 (member)
                 (service)
                 (last_login)
                 (updated_by)
                 (details)
                 (status)
                 (situation)
                 (description)
         .exec();
	W.commit();
}

void SubscriptionModel::DeleteSubscription(std::string id){
	pqxx::connection C(angru::wrapper::Postgresql::connection_string());
	try {
		if (!C.is_open()) {
			 LOG_ERROR << "Can't open database: " << C.dbname();
		}
		C.disconnect ();
	} catch (const angru::system::exception::error &e) {
			LOG_ERROR << e.what();
	}
	 pqxx::work W(C);
	 C.prepare("update", "UPDATE subscriptions SET \
												deleted_at = now()  \
												WHERE id = $1");
   W.prepared("update")(id).exec();
   W.commit();
  }

} // model
} // mvc
} // angru
