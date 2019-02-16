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

ContentProviderController::ContentProviderController(){}
ContentProviderController::~ContentProviderController(){}

void ContentProviderController::doGetContentProviders(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthenticationCheck(request,response);
    int page = 1;
    auto query = request.query();
    if(query.has("page")) {
      auto value = query.get("page").get();
      page = std::stoi(value);
    }
    boost::property_tree::ptree content_providers = angru::mvc::model::ContentProviderModel::GetContentProvidersJson(page);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, content_providers);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "ContentProviders not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void ContentProviderController::doGetContentProvider(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthenticationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    boost::property_tree::ptree content_provider = angru::mvc::model::ContentProviderModel::GetContentProviderJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, content_provider);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "ContentProviders not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void ContentProviderController::doDeleteContentProvider(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthenticationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    angru::mvc::model::ContentProviderModel::DeleteContentProvider(id);
    response.send(Pistache::Http::Code::Ok, "ContentProvider deleted.");
}

void ContentProviderController::doAddContentProvider(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthenticationCheck(request,response);
    auto body = request.body();
    std::string	name;
    std::string	title;
    std::string	code;
    std::string	phone;
    std::string	email;
    std::string	details;
    int	status;
    std::string	description;
    try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      name = pt.get<std::string>("name");
      title = pt.get<std::string>("title");
      code = pt.get<std::string>("code");
      phone = pt.get<std::string>("phone");
      email = pt.get<std::string>("email");
      details = pt.get<std::string>("details");
      status = pt.get<int>("status");
      description = pt.get<std::string>("description");

      angru::mvc::model::ContentProviderModel::AddContentProvider(
                                                  name, 
                                                  title, 
                                                  code, 
                                                  phone, 
                                                  email, 
                                                  details, 
                                                  status, 
                                                  description );
      response.send(Pistache::Http::Code::Ok, "ContentProvider added.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "ContentProviders not found.");
    }
}

void ContentProviderController::doUpdateContentProvider(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthenticationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
      id = value.as<int>();
    }
    if(id == -1){
      response.send(Pistache::Http::Code::Not_Found, "ContentProviders not found.");
    }
    auto body = request.body();
    std::string	name;
    std::string	title;
    std::string	code;
    std::string	phone;
    std::string	email;
    std::string	details;
    int	status;
    std::string	description;
   try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      name = pt.get<std::string>("name");
      title = pt.get<std::string>("title");
      code = pt.get<std::string>("code");
      phone = pt.get<std::string>("phone");
      email = pt.get<std::string>("email");
      details = pt.get<std::string>("details");
      status = pt.get<int>("status");
      description = pt.get<std::string>("description");
      angru::mvc::model::ContentProviderModel::UpdateContentProvider(
                                                  id, 
                                                  name, 
                                                  title, 
                                                  code, 
                                                  phone, 
                                                  email, 
                                                  details, 
                                                  status, 
                                                  description );
      response.send(Pistache::Http::Code::Ok, "ContentProviders updated.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "ContentProviders not found.");
    }
 }

} // model
} // mvc
} // angru
