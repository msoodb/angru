#include <iostream>
#include <string>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <jwt/jwt.hpp>

#include "_error.h"
#include "_log.h"
#include "_PostgreSQL.h"

#include "userController.h"
#include "userModel.h"
#include "_cryptography.h"
#include "_authorization.h"

UserController::UserController(){}
UserController::~UserController(){}

void UserController::doLogin(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    auto headers = request.headers();
    auto content_type = headers.tryGet<Pistache::Http::Header::ContentType>();
    if (content_type != nullptr){
        if (content_type->mime() != MIME(Application, Json))
          response.send(Pistache::Http::Code::Not_Found, "Invalid Username or Password.");
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
        password_sha1 = _cryptography::get_sha1(password);
    }
    catch (std::exception const& e){
        std::cerr << e.what() << std::endl;
    }
    std::string query = " email = '" + email + "' and password = '" + password_sha1 + "'";
    pqxx::result R = UserModel::getUsers(1, query);
    pqxx::row r;
  	if (R.size() != 1){
      response.send(Pistache::Http::Code::Not_Found, "Invalid Username or Password.");
    }
		r = R[0];
    std::string password_jwt = _cryptography::get_jwt(email,email);
    std::string token =  password_jwt;
    if (token.empty()) {
        response.send(Pistache::Http::Code::Not_Found, "Invalid Username or Password.");
    } else {
        response.send(Pistache::Http::Code::Ok, token);
    }
}
void UserController::doGetUsers(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    _Authorization::AuthorizationCheck(request,response);
    int page = 1;
    auto query = request.query();
    if(query.has("page")) {
      auto value = query.get("page").get();
      page = std::stoi(value);
    }
    boost::property_tree::ptree user_ = UserModel::getUsers_json(page);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, user_);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
        response.send(Pistache::Http::Code::Not_Found, "Users does not exist");
    }
    else {
      response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}
void UserController::doGetUser(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    _Authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    boost::property_tree::ptree user_ = UserModel::getUser_json(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, user_);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
        response.send(Pistache::Http::Code::Not_Found, "User does not exist");
    } else {
        response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
        response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}
void UserController::doDeleteUser(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    _Authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    UserModel::deleteUser(id);
    response.send(Pistache::Http::Code::Ok, "User delet.");
}
void UserController::doAddUser(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    _Authorization::AuthorizationCheck(request,response);
    _Authorization::ContentTypeJSONCheck(request,response);
    auto body = request.body();
    int id;
    std::string email;
    std::string password;
    std::string password_sha1;
    std::string details;
    std::string created_at;
    std::string deleted_at;
    try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      id = pt.get<int>("id");
      email = pt.get<std::string>("email");
      password = pt.get<std::string>("password");
      password_sha1 = _cryptography::get_sha1(password);
    }
    catch (std::exception const& e){
        std::cerr << e.what() << std::endl;
    }
    UserModel::addUser(id,email,password_sha1,details,created_at,deleted_at);
    response.send(Pistache::Http::Code::Ok, "User added.");
}
void UserController::doUpdateUser(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    _Authorization::AuthorizationCheck(request,response);
    _Authorization::ContentTypeJSONCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    if(id==-1){
        response.send(Pistache::Http::Code::Not_Found, "User not found.");
    }
    auto body = request.body();
    std::string email;
    std::string password;
    std::string password_sha1;
    std::string details;
    std::string created_at;
    std::string deleted_at;
    try
    {
        std::stringstream ss;
        ss << body;
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);
        id = pt.get<int>("id");
        email = pt.get<std::string>("email");
        password = pt.get<std::string>("password");
        password_sha1 = _cryptography::get_sha1(password);
    }
    catch (std::exception const& e){
        std::cerr << e.what() << std::endl;
    }
    UserModel::updateUser(id,email,password_sha1,details,created_at,deleted_at);
    response.send(Pistache::Http::Code::Ok, "User updated.");
}
