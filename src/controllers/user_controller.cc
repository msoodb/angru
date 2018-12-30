#include "controllers/user_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <jwt/jwt.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/user_model.h"

namespace angru{
namespace mvc{
namespace controller{

UserController::UserController(){}
UserController::~UserController(){}

void UserController::doLogin(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    auto headers = request.headers();
    auto content_type = headers.tryGet<Pistache::Http::Header::ContentType>();
    if (content_type != nullptr){
        if (content_type->mime() != MIME(Application, Json)){
          response.send(Pistache::Http::Code::Not_Found, "Invalid Username or Password.");
        }
    }
    auto body = request.body();
    std::string email;
    std::string password;
    std::string password_sha1;
    try
    {
        std::stringstream ss;
        ss << body;
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);
        email = pt.get<std::string>("email");
        password = pt.get<std::string>("password");
        password_sha1 = angru::security::cryptography::get_sha1(password);
    }
    catch (std::exception const& e){
      LOG_ERROR << e.what();
      response.send(Pistache::Http::Code::Not_Found, "Invalid Username or Password.");
    }
    std::string query = " email = '" + email + "' and password = '" + password_sha1 + "'";
    pqxx::result R = angru::mvc::model::UserModel::GetUsers(1, query);
  	if (R.size() != 1){
      response.send(Pistache::Http::Code::Not_Found, "Invalid Username or Password.");
    }
    std::string password_jwt = angru::security::cryptography::get_jwt(email,email);
    std::string token =  password_jwt;
    if (token.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "Invalid Username or Password.");
    } else {
      response.send(Pistache::Http::Code::Ok, token);
    }
}
void UserController::doGetUsers(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::AuthorizationCheck(request,response);
    int page = 1;
    auto query = request.query();
    if(query.has("page")) {
      auto value = query.get("page").get();
      page = std::stoi(value);
    }
    boost::property_tree::ptree users = angru::mvc::model::UserModel::GetUsersJson(page);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, users);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "Users not found.");
    }
    else {
      response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}
void UserController::doGetUser(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    boost::property_tree::ptree user = angru::mvc::model::UserModel::GetUserJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, user);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "Users not found.");
    } else {
      response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}
void UserController::doDeleteUser(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    angru::mvc::model::UserModel::DeleteUser(id);
    response.send(Pistache::Http::Code::Ok, "User delet.");
}
void UserController::doAddUser(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    auto body = request.body();
    std::string email;
    std::string password;
    std::string password_sha1;
    std::string details;
    try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      email = pt.get<std::string>("email");
      password = pt.get<std::string>("password");
      password_sha1 = angru::security::cryptography::get_sha1(password);
      details = pt.get<std::string>("details");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Users not found.");
    }
    angru::mvc::model::UserModel::AddUser(email,password_sha1,details);
    response.send(Pistache::Http::Code::Ok, "User added.");
}
void UserController::doUpdateUser(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::AuthorizationCheck(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    if(id==-1){
      response.send(Pistache::Http::Code::Not_Found, "Users not found.");
    }
    auto body = request.body();
    std::string email;
    std::string password;
    std::string password_sha1;
    std::string details;
    try
    {
        std::stringstream ss;
        ss << body;
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);
        id = pt.get<int>("id");
        email = pt.get<std::string>("email");
        password = pt.get<std::string>("password");
        password_sha1 = angru::security::cryptography::get_sha1(password);
        details = pt.get<std::string>("details");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Users not found.");
    }
    angru::mvc::model::UserModel::UpdateUser(id,email,password_sha1,details);
    response.send(Pistache::Http::Code::Ok, "User updated.");
}

} // controller
} // mvc
} // angru
