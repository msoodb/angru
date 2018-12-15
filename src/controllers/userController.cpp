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
