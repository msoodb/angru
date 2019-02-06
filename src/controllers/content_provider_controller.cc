#include "controllers/content_provider_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/content_provider_model.h"

namespace angru{
namespace mvc{
namespace controller{

Content_providerController::Content_providerController(){}
Content_providerController::~Content_providerController(){}

void Content_providerController::doGetContent_providers(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    int page = 1;
    auto query = request.query();
    if(query.has("page")) {
      auto value = query.get("page").get();
      page = std::stoi(value);
    }
    boost::property_tree::ptree content_providers = angru::mvc::model::Content_providerModel::GetContent_providersJson(page);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, content_providers);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "Content_providers not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void Content_providerController::doGetContent_provider(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    boost::property_tree::ptree content_provider = angru::mvc::model::Content_providerModel::GetContent_providerJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, content_provider);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "Content_providers not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void Content_providerController::doDeleteContent_provider(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    angru::mvc::model::Content_providerModel::DeleteContent_provider(id);
    response.send(Pistache::Http::Code::Ok, "Content_provider deleted.");
}

void Content_providerController::doAddContent_provider(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    auto body = request.body();
    std::string	name;
    std::string	title;
    std::string	phone;
    std::string	email;
    std::string	details;
    std::string	description;
    try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      name = pt.get<std::string>("name");
      title = pt.get<std::string>("title");
      phone = pt.get<std::string>("phone");
      email = pt.get<std::string>("email");
      details = pt.get<std::string>("details");
      description = pt.get<std::string>("description");

      angru::mvc::model::Content_providerModel::AddContent_provider(
                                                  name, 
                                                  title, 
                                                  phone, 
                                                  email, 
                                                  details, 
                                                  description );
      response.send(Pistache::Http::Code::Ok, "Content_provider added.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Content_providers not found.");
    }
}

void Content_providerController::doUpdateContent_provider(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
      id = value.as<int>();
    }
    if(id == -1){
      response.send(Pistache::Http::Code::Not_Found, "Content_providers not found.");
    }
    auto body = request.body();
    std::string	name;
    std::string	title;
    std::string	phone;
    std::string	email;
    std::string	details;
    std::string	description;
   try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      name = pt.get<std::string>("name");
      title = pt.get<std::string>("title");
      phone = pt.get<std::string>("phone");
      email = pt.get<std::string>("email");
      details = pt.get<std::string>("details");
      description = pt.get<std::string>("description");
      angru::mvc::model::Content_providerModel::UpdateContent_provider(
                                                  id, 
                                                  name, 
                                                  title, 
                                                  phone, 
                                                  email, 
                                                  details, 
                                                  description );
      response.send(Pistache::Http::Code::Ok, "Content_providers updated.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Content_providers not found.");
    }
 }

} // model
} // mvc
} // angru
