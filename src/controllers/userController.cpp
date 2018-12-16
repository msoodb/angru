#include <iostream>
#include <string>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "_error.h"
#include "_log.h"
#include "_PostgreSQL.h"

#include "userController.h"
#include "userModel.h"
#include "_cryptography.h"


UserController::UserController(){}
UserController::~UserController(){}
void UserController::doGetUsers(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    int page = 1;
    auto query = request.query();
    if(query.has("page")) {
      auto value = query.get("page").get();
      page = std::stoi(value);
    }
    boost::property_tree::ptree user_ = UserModel::getUsers_json(page);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, user_);

    //response.headers().add<Header::ContentType>(MIME(Application, Json));
    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
        response.send(Pistache::Http::Code::Not_Found, "Users does not exist");
    } else {
        response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}
void UserController::doGetUser(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
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
        response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}
void UserController::doDeleteUser(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
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
    auto body = request.body();
    int id;
    std::string email;
    std::string password;
    std::string password_sha1;
    std::string details;
    std::string created_at;
    std::string deleted_at;
    if(true /*Content-Type: multipart/form-data*/)
    {
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
    }
    UserModel::addUser(id,email,password_sha1,details,created_at,deleted_at);
    response.send(Pistache::Http::Code::Ok, "User added.");
}
void UserController::doUpdateUser(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
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
    if(true /*Content-Type: multipart/form-data*/)
    {
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
    }
    UserModel::updateUser(id,email,password_sha1,details,created_at,deleted_at);
    response.send(Pistache::Http::Code::Ok, "User updated.");
}
