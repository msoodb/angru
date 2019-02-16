#include "controllers/security_role_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/security_role_model.h"

namespace angru{
namespace mvc{
namespace controller{

SecurityRolesController::SecurityRolesController(){}
SecurityRolesController::~SecurityRolesController(){}

void SecurityRolesController::doGetSecurityRoless(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
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
    boost::property_tree::ptree security_roles = angru::mvc::model::SecurityRolesModel::GetSecurityRolessJson(page, filter);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, security_roles);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "SecurityRoless not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void SecurityRolesController::doGetSecurityRoles(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    boost::property_tree::ptree security_role = angru::mvc::model::SecurityRolesModel::GetSecurityRolesJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, security_role);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "SecurityRoless not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void SecurityRolesController::doDeleteSecurityRoles(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    std::string deleted_by = user_id;
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    angru::mvc::model::SecurityRolesModel::DeleteSecurityRoles(id);
    response.send(Pistache::Http::Code::Ok, "SecurityRoles deleted.");
}

void SecurityRolesController::doAddSecurityRoles(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    auto body = request.body();
    std::string created_by = user_id;
    std::string	name;
    std::string	title;
    int	status;
    int	situation;
    std::string	description;
    try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      name = pt.get<std::string>("name");
      title = pt.get<std::string>("title");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");

      angru::mvc::model::SecurityRolesModel::AddSecurityRoles(
                                                  name, 
                                                  title, 
                                                  created_by, 
                                                  status, 
                                                  situation, 
                                                  description );
      response.send(Pistache::Http::Code::Ok, "SecurityRoles added.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "SecurityRoless not found.");
    }
}

void SecurityRolesController::doUpdateSecurityRoles(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    std::string updated_by = user_id;
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
      id = value.as<std::string>();
    }
    auto body = request.body();
    std::string	name;
    std::string	title;
    int	status;
    int	situation;
    std::string	description;
   try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      name = pt.get<std::string>("name");
      title = pt.get<std::string>("title");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");
      angru::mvc::model::SecurityRolesModel::UpdateSecurityRoles(
                                                  id, 
                                                  name, 
                                                  title, 
                                                  updated_by, 
                                                  status, 
                                                  situation, 
                                                  description );
      response.send(Pistache::Http::Code::Ok, "SecurityRoless updated.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "SecurityRoless not found.");
    }
 }

} // model
} // mvc
} // angru
