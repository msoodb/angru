#include "controllers/tag_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/tag_model.h"
#include "models/privilege_model.h"

namespace angru{
namespace mvc{
namespace controller{

TagController::TagController(){}
TagController::~TagController(){}

void TagController::doGetTags(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "tags", GET_ITEMS);
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
    int limit = LIMIT_COUNT;
    if(query.has("limit")) {
      auto value = query.get("limit").get();
      limit = std::stoi(value);
    }
    if(query.has("filter")) {
      auto value = query.get("filter").get();
      filter = angru::security::cryptography::decode_base64(value);
    }
    boost::property_tree::ptree tags = angru::mvc::model::TagModel::GetTagsJson(page, limit, filter);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, tags);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "Tags not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void TagController::doGetTag(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "tags", GET_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    boost::property_tree::ptree tag = angru::mvc::model::TagModel::GetTagJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, tag);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "Tags not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void TagController::doDeleteTag(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "tags", DELETE_ITEM);
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
    angru::mvc::model::TagModel::DeleteTag(id);
    response.send(Pistache::Http::Code::Ok, "Tag deleted.");
}

void TagController::doAddTag(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "tags", ADD_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    auto body = request.body();
    std::string created_by = user_id;
    std::string	name;
    std::string	title;
    int	type;
    std::string	details;
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
      type = pt.get<int>("type");
      details = pt.get<std::string>("details");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");

      angru::mvc::model::TagModel::AddTag(
                                                  name,
                                                  title,
                                                  type,
                                                  created_by,
                                                  details,
                                                  status,
                                                  situation,
                                                  description );
      response.send(Pistache::Http::Code::Ok, "Tag added.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Tags not found.");
    }
}

void TagController::doUpdateTag(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "tags", UPDATE_ITEM);
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
    std::string	name;
    std::string	title;
    int	type;
    std::string	details;
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
      type = pt.get<int>("type");
      details = pt.get<std::string>("details");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");
      angru::mvc::model::TagModel::UpdateTag(
                                                  id,
                                                  name,
                                                  title,
                                                  type,
                                                  updated_by,
                                                  details,
                                                  status,
                                                  situation,
                                                  description );
      response.send(Pistache::Http::Code::Ok, "Tags updated.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Tags not found.");
    }
 }

} // model
} // mvc
} // angru