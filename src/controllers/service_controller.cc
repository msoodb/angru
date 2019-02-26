#include "controllers/service_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/service_model.h"
#include "models/privilege_model.h"

namespace angru{
namespace mvc{
namespace controller{

ServiceController::ServiceController(){}
ServiceController::~ServiceController(){}

void ServiceController::doGetServices(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "services", GET_ITEMS);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    int page = 1;
    std::string filter;
    auto query = request.query();
    if(query.has("page")) {
      auto value = query.get("page").get();
      page = std::stoi(value);
    }
    if(query.has("filter")) {
      auto value = query.get("filter").get();
      filter = angru::security::cryptography::decode_base64(value);
    }
    boost::property_tree::ptree services = angru::mvc::model::ServiceModel::GetServicesJson(page, filter);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, services);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "Services not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void ServiceController::doGetService(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "services", GET_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    boost::property_tree::ptree service = angru::mvc::model::ServiceModel::GetServiceJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, service);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "Services not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void ServiceController::doDeleteService(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "services", DELETE_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    std::string deleted_by = user_id;
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    angru::mvc::model::ServiceModel::DeleteService(id);
    response.send(Pistache::Http::Code::Ok, "Service deleted.");
}

void ServiceController::doAddService(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "services", ADD_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    auto body = request.body();
    std::string created_by = user_id;
    std::string	pendar;
    std::string	mobile_operator;
    std::string	aggregator;
    std::string	content_provider;
    std::string	name;
    std::string	title;
    std::string	code;
    std::string	details;
    int	status;
    int	situation;
    std::string	description;
    try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      pendar = pt.get<std::string>("pendar");
      mobile_operator = pt.get<std::string>("mobile_operator");
      aggregator = pt.get<std::string>("aggregator");
      content_provider = pt.get<std::string>("content_provider");
      name = pt.get<std::string>("name");
      title = pt.get<std::string>("title");
      code = pt.get<std::string>("code");
      details = pt.get<std::string>("details");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");

      angru::mvc::model::ServiceModel::AddService(
                                                  pendar, 
                                                  mobile_operator, 
                                                  aggregator, 
                                                  content_provider, 
                                                  name, 
                                                  title, 
                                                  code, 
                                                  created_by, 
                                                  details, 
                                                  status, 
                                                  situation, 
                                                  description );
      response.send(Pistache::Http::Code::Ok, "Service added.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Services not found.");
    }
}

void ServiceController::doUpdateService(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "services", UPDATE_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    std::string updated_by = user_id;
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
      id = value.as<std::string>();
    }
    auto body = request.body();
    std::string	pendar;
    std::string	mobile_operator;
    std::string	aggregator;
    std::string	content_provider;
    std::string	name;
    std::string	title;
    std::string	code;
    std::string	details;
    int	status;
    int	situation;
    std::string	description;
   try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      pendar = pt.get<std::string>("pendar");
      mobile_operator = pt.get<std::string>("mobile_operator");
      aggregator = pt.get<std::string>("aggregator");
      content_provider = pt.get<std::string>("content_provider");
      name = pt.get<std::string>("name");
      title = pt.get<std::string>("title");
      code = pt.get<std::string>("code");
      details = pt.get<std::string>("details");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");
      angru::mvc::model::ServiceModel::UpdateService(
                                                  id, 
                                                  pendar, 
                                                  mobile_operator, 
                                                  aggregator, 
                                                  content_provider, 
                                                  name, 
                                                  title, 
                                                  code, 
                                                  updated_by, 
                                                  details, 
                                                  status, 
                                                  situation, 
                                                  description );
      response.send(Pistache::Http::Code::Ok, "Services updated.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Services not found.");
    }
 }

} // model
} // mvc
} // angru
