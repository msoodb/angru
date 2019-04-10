#include "controllers/tags_content_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/tags_content_model.h"
#include "models/tag_model.h"
#include "models/privilege_model.h"

namespace angru{
namespace mvc{
namespace controller{

TagsContentController::TagsContentController(){}
TagsContentController::~TagsContentController(){}

void TagsContentController::doGetTagsContents(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "tags_contents", GET_ITEMS);
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
    std::string order;
    if(query.has("order")) {
      auto value = query.get("order").get();
      order = angru::security::cryptography::decode_base64(value);
    }
    boost::property_tree::ptree tags_contents = angru::mvc::model::TagsContentModel::GetTagsContentsJson(page, limit, filter, order);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, tags_contents);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "TagsContents not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void TagsContentController::doGetTagsContent(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "tags_contents", GET_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    boost::property_tree::ptree tags_content = angru::mvc::model::TagsContentModel::GetTagsContentJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, tags_content);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "TagsContents not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void TagsContentController::doDeleteTagsContent(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "tags_contents", DELETE_ITEM);
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
    angru::mvc::model::TagsContentModel::DeleteTagsContent(id);
    response.send(Pistache::Http::Code::Ok, "TagsContent deleted.");
}

void TagsContentController::doAddTagsContent(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "tags_contents", ADD_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    std::string content_id = "";
    if (request.hasParam(":content_id")) {
        auto value = request.param(":content_id");
        content_id = value.as<std::string>();
    }
    else{
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"TagsContents not found.\"}");
      return;
    }
    auto body = request.body();
    std::string created_by = user_id;
    std::string	tag_name;
    std::string	content;
    int	status;
    int	situation;
    std::string	description;
    try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      tag_name = pt.get<std::string>("tag");
      std::string	tag = angru::mvc::model::TagModel::ReturnTagId(user_id, tag_name);
      content = pt.get<std::string>("content");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");

      std::string id = angru::mvc::model::TagsContentModel::AddTagsContent(
                                                  tag,
                                                  content,
                                                  created_by,
                                                  status,
                                                  situation,
                                                  description );
      std::string message = "{\"message\":\"TagsContent Added.\", \"id\":\"" + id + "\"}";
      response.send(Pistache::Http::Code::Ok, message);
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "TagsContents not found.");
    }
}

void TagsContentController::doUpdateTagsContent(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "tags_contents", UPDATE_ITEM);
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
    std::string	tag;
    std::string	content;
    int	status;
    int	situation;
    std::string	description;
   try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      tag = pt.get<std::string>("tag");
      content = pt.get<std::string>("content");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");
      angru::mvc::model::TagsContentModel::UpdateTagsContent(
                                                  id,
                                                  tag,
                                                  content,
                                                  updated_by,
                                                  status,
                                                  situation,
                                                  description );
      response.send(Pistache::Http::Code::Ok, "TagsContents updated.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "TagsContents not found.");
    }
 }

} // model
} // mvc
} // angru
