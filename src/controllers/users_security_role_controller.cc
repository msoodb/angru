#include "controllers/users_security_role_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/users_security_role_model.h"
#include "models/privilege_model.h"


namespace angru{
namespace mvc{
namespace controller{

UsersSecurityRoleController::UsersSecurityRoleController(){}
UsersSecurityRoleController::~UsersSecurityRoleController(){}

void UsersSecurityRoleController::doGetUsersSecurityRoles(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "users_security_roles", GET_ITEMS);
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
    boost::property_tree::ptree users_security_roles = angru::mvc::model::UsersSecurityRoleModel::GetUsersSecurityRolesJson(page, filter);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, users_security_roles);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "UsersSecurityRoles not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void UsersSecurityRoleController::doGetUsersSecurityRole(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "users_security_roles", GET_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    boost::property_tree::ptree users_security_role = angru::mvc::model::UsersSecurityRoleModel::GetUsersSecurityRoleJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, users_security_role);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "UsersSecurityRoles not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void UsersSecurityRoleController::doDeleteUsersSecurityRole(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "users_security_roles", DELETE_ITEM);
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
    angru::mvc::model::UsersSecurityRoleModel::DeleteUsersSecurityRole(id);
    response.send(Pistache::Http::Code::Ok, "UsersSecurityRole deleted.");
}

void UsersSecurityRoleController::doAddUsersSecurityRole(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "users_security_roles", ADD_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    auto body = request.body();
    std::string created_by = user_id;
    std::string	_user_;
    std::string	security_role;
    int	status;
    int	situation;
    std::string	description;
    try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      _user_ = pt.get<std::string>("_user_");
      security_role = pt.get<std::string>("security_role");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");

      angru::mvc::model::UsersSecurityRoleModel::AddUsersSecurityRole(
                                                  _user_,
                                                  security_role,
                                                  created_by,
                                                  status,
                                                  situation,
                                                  description );
      response.send(Pistache::Http::Code::Ok, "UsersSecurityRole added.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "UsersSecurityRoles not found.");
    }
}

void UsersSecurityRoleController::doUpdateUsersSecurityRole(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "users_security_roles", UPDATE_ITEM);
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
    std::string	_user_;
    std::string	security_role;
    int	status;
    int	situation;
    std::string	description;
   try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      _user_ = pt.get<std::string>("_user_");
      security_role = pt.get<std::string>("security_role");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");
      angru::mvc::model::UsersSecurityRoleModel::UpdateUsersSecurityRole(
                                                  id,
                                                  _user_,
                                                  security_role,
                                                  updated_by,
                                                  status,
                                                  situation,
                                                  description );
      response.send(Pistache::Http::Code::Ok, "UsersSecurityRoles updated.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "UsersSecurityRoles not found.");
    }
 }

} // model
} // mvc
} // angru
