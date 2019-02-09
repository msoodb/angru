#include "controllers/user_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
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
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    auto headers = request.headers();
    auto content_type = headers.tryGet<Pistache::Http::Header::ContentType>();
    if (content_type != nullptr){
        if (content_type->mime() != MIME(Application, Json)){
          response.send(Pistache::Http::Code::Not_Found, "Invalid Username or Password.");
        }
    }
    auto body = request.body();
    std::string input;
    std::string password;
    std::string password_sha1;
    try
    {
        std::stringstream ss;
        ss << body;
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);
        input = pt.get<std::string>("input");
        password = pt.get<std::string>("password");
        password_sha1 = angru::security::cryptography::get_sha1(password);
        //ToDO Add sql injection guard
        std::string query = " ( user_name = '" + input + "' or email = '" + input + "') AND password = '" + password_sha1 + "'";
        pqxx::result R = angru::mvc::model::UserModel::GetUsers(1, query);
      	if (R.size() != 1){
          response.send(Pistache::Http::Code::Not_Found, "Invalid Username or Password.");
        }
        std::string user_id = R[0][0].as<std::string>();
        std::string password_jwt = angru::security::cryptography::get_jwt(user_id, input);
        std::string token =  password_jwt;
        if (token.empty()) {
          response.send(Pistache::Http::Code::Not_Found, "Invalid Username or Password.");
        } else {
          response.send(Pistache::Http::Code::Ok, token);
        }
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Invalid Username or Password.");
    }
}

void UserController::doGetUsers(const Pistache::Rest::Request& request,
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
    boost::property_tree::ptree users = angru::mvc::model::UserModel::GetUsersJson(page, filter);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, users);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "Users not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void UserController::doGetUser(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    boost::property_tree::ptree user = angru::mvc::model::UserModel::GetUserJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, user);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "Users not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void UserController::doDeleteUser(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    angru::mvc::model::UserModel::DeleteUser(id);
    response.send(Pistache::Http::Code::Ok, "User deleted.");
}

void UserController::doAddUser(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    auto body = request.body();
    std::string	first_name;
    std::string	middle_name;
    std::string	last_name;
    std::string	user_name;
    std::string	email;
    std::string	password;
    std::string password_sha1;
    int	type;
    std::string	details;
    int	status;
    std::string	description;
    try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      first_name = pt.get<std::string>("first_name");
      middle_name = pt.get<std::string>("middle_name");
      last_name = pt.get<std::string>("last_name");
      user_name = pt.get<std::string>("user_name");
      email = pt.get<std::string>("email");
      password = pt.get<std::string>("password");
      password_sha1 = angru::security::cryptography::get_sha1(password);
      type = pt.get<int>("type");
      if(type == 0){
        throw std::runtime_error("error");
      }
      details = pt.get<std::string>("details");
      status = pt.get<int>("status");
      description = pt.get<std::string>("description");

      angru::mvc::model::UserModel::AddUser(
                                                  first_name,
                                                  middle_name,
                                                  last_name,
                                                  user_name,
                                                  email,
                                                  password_sha1,
                                                  type,
                                                  details,
                                                  status,
                                                  description );
      response.send(Pistache::Http::Code::Ok, "User added.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Users not found.");
    }
}

void UserController::doUpdateUser(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    // if(id == -1){
    //   response.send(Pistache::Http::Code::Not_Found, "Users not found.");
    // }
    auto body = request.body();
    std::string	first_name;
    std::string	middle_name;
    std::string	last_name;
    std::string	user_name;
    std::string	email;
    std::string	password;
    int	type;
    std::string	details;
    int	status;
    std::string	description;
   try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      first_name = pt.get<std::string>("first_name");
      middle_name = pt.get<std::string>("middle_name");
      last_name = pt.get<std::string>("last_name");
      user_name = pt.get<std::string>("user_name");
      email = pt.get<std::string>("email");
      password = pt.get<std::string>("password");
      type = pt.get<int>("type");
      details = pt.get<std::string>("details");
      status = pt.get<int>("status");
      description = pt.get<std::string>("description");
      angru::mvc::model::UserModel::UpdateUser(
                                                  id,
                                                  first_name,
                                                  middle_name,
                                                  last_name,
                                                  user_name,
                                                  email,
                                                  password,
                                                  type,
                                                  details,
                                                  status,
                                                  description );
      response.send(Pistache::Http::Code::Ok, "Users updated.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Users not found.");
    }
 }

} // model
} // mvc
} // angru
