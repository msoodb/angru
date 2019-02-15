#include "controllers/privilege_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/privilege_model.h"

namespace angru{
namespace mvc{
namespace controller{

PrivilegeController::PrivilegeController(){}
PrivilegeController::~PrivilegeController(){}

void PrivilegeController::doGetPrivileges(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthorizationCheck(request,response);
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
    boost::property_tree::ptree privileges = angru::mvc::model::PrivilegeModel::GetPrivilegesJson(page, filter);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, privileges);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "Privileges not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void PrivilegeController::doGetPrivilege(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthorizationCheck(request,response);
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    boost::property_tree::ptree privilege = angru::mvc::model::PrivilegeModel::GetPrivilegeJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, privilege);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "Privileges not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void PrivilegeController::doDeletePrivilege(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthorizationCheck(request,response);
    std::string deleted_by = user_id;
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    angru::mvc::model::PrivilegeModel::DeletePrivilege(id);
    response.send(Pistache::Http::Code::Ok, "Privilege deleted.");
}

void PrivilegeController::doAddPrivilege(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthorizationCheck(request,response);
    auto body = request.body();
    std::string created_by = user_id;
    std::string	security_role;
    std::string	entity;
    std::string	privilege_string;
    int	status;
    int	situation;
    std::string	description;
    try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      security_role = pt.get<std::string>("security_role");
      entity = pt.get<std::string>("entity");
      privilege_string = pt.get<std::string>("privilege_string");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");

      angru::mvc::model::PrivilegeModel::AddPrivilege(
                                                  security_role, 
                                                  entity, 
                                                  privilege_string, 
                                                  created_by, 
                                                  status, 
                                                  situation, 
                                                  description );
      response.send(Pistache::Http::Code::Ok, "Privilege added.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Privileges not found.");
    }
}

void PrivilegeController::doUpdatePrivilege(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthorizationCheck(request,response);
    std::string updated_by = user_id;
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
      id = value.as<std::string>();
    }
    auto body = request.body();
    std::string	security_role;
    std::string	entity;
    std::string	privilege_string;
    int	status;
    int	situation;
    std::string	description;
   try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      security_role = pt.get<std::string>("security_role");
      entity = pt.get<std::string>("entity");
      privilege_string = pt.get<std::string>("privilege_string");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");
      angru::mvc::model::PrivilegeModel::UpdatePrivilege(
                                                  id, 
                                                  security_role, 
                                                  entity, 
                                                  privilege_string, 
                                                  updated_by, 
                                                  status, 
                                                  situation, 
                                                  description );
      response.send(Pistache::Http::Code::Ok, "Privileges updated.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Privileges not found.");
    }
 }

} // model
} // mvc
} // angru
