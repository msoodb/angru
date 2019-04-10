#include "controllers/tags_channel_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/tags_channel_model.h"
#include "models/tag_model.h"
#include "models/privilege_model.h"

namespace angru{
namespace mvc{
namespace controller{

TagsChannelController::TagsChannelController(){}
TagsChannelController::~TagsChannelController(){}

void TagsChannelController::doGetTagsChannels(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "tags_channels", GET_ITEMS);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    std::string channel_id = "";
    if (request.hasParam(":channel_id")) {
        auto value = request.param(":channel_id");
        channel_id = value.as<std::string>();
    }
    else{
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"TagsChannels not found.\"}");
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
      filter = filter + " AND channel = '" + channel_id + "'";
    }
    else{
      filter = " channel = '" + channel_id + "'";
    }
    std::string order;
    if(query.has("order")) {
      auto value = query.get("order").get();
      order = angru::security::cryptography::decode_base64(value);
    }
    boost::property_tree::ptree tags_channels = angru::mvc::model::TagsChannelModel::GetTagsChannelsJson(page, limit, filter, order);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, tags_channels);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"TagsChannels not found.\"}");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void TagsChannelController::doGetTagsChannel(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "tags_channels", GET_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    boost::property_tree::ptree tags_channel = angru::mvc::model::TagsChannelModel::GetTagsChannelJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, tags_channel);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "TagsChannels not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void TagsChannelController::doDeleteTagsChannel(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "tags_channels", DELETE_ITEM);
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
    angru::mvc::model::TagsChannelModel::DeleteTagsChannel(id);
    response.send(Pistache::Http::Code::Ok, "{\"message\":\"TagsChannel deleted.\"}");
}

void TagsChannelController::doAddTagsChannel(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "tags_channels", ADD_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    std::string channel_id = "";
    if (request.hasParam(":channel_id")) {
        auto value = request.param(":channel_id");
        channel_id = value.as<std::string>();
    }
    else{
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"TagsChannels not found.\"}");
      return;
    }
    auto body = request.body();
    std::string created_by = user_id;
    std::string	tag_name;
    std::string	channel;
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
      channel = pt.get<std::string>("channel");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");

      std::string id = angru::mvc::model::TagsChannelModel::AddTagsChannel(
                                                  tag,
                                                  channel,
                                                  created_by,
                                                  status,
                                                  situation,
                                                  description );
      std::string message = "{\"message\":\"TagsChannel Added.\", \"id\":\"" + id + "\"}";
      response.send(Pistache::Http::Code::Ok, message);
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"TagsChannels not found.\"}");
    }
}

void TagsChannelController::doUpdateTagsChannel(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "tags_channels", UPDATE_ITEM);
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
    std::string	channel;
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
      channel = pt.get<std::string>("channel");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");
      angru::mvc::model::TagsChannelModel::UpdateTagsChannel(
                                                  id,
                                                  tag,
                                                  channel,
                                                  updated_by,
                                                  status,
                                                  situation,
                                                  description );
      response.send(Pistache::Http::Code::Ok, "TagsChannels updated.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "TagsChannels not found.");
    }
 }

} // model
} // mvc
} // angru
