#include "controllers/channel_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/channel_model.h"
#include "models/privilege_model.h"

namespace angru{
namespace mvc{
namespace controller{

ChannelController::ChannelController(){}
ChannelController::~ChannelController(){}

void ChannelController::doGetChannels(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "channels", GET_ITEMS);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    std::string service_id = "";
    if (request.hasParam(":service_id")) {
        auto value = request.param(":service_id");
        service_id = value.as<std::string>();
    }
    else{
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"Channels not found.\"}");
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
    std::string parent="";
    if(query.has("parent")) {
      auto value = query.get("parent").get();
      parent = value;
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
    boost::property_tree::ptree channels = angru::mvc::model::ChannelModel::GetChannelsJson(page, limit, service_id, parent, filter);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, channels);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"Channels not found.\"}");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void ChannelController::doGetAllChannels(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "channels", GET_ITEMS);
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
    boost::property_tree::ptree channels = angru::mvc::model::ChannelModel::GetAllChannelsJson(page, limit, filter, order);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, channels);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"Channels not found.\"}");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void ChannelController::doGetChannel(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "channels", GET_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    boost::property_tree::ptree channel = angru::mvc::model::ChannelModel::GetChannelJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, channel);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"Channels not found.\"}");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void ChannelController::doDeleteChannel(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "channels", DELETE_ITEM);
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
    angru::mvc::model::ChannelModel::DeleteChannel(id);
    response.send(Pistache::Http::Code::Ok, "Channel deleted.");
}

void ChannelController::doAddChannel(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "channels", ADD_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    auto body = request.body();
    std::string created_by = user_id;
    std::string	name;
    std::string	title;
    std::string	service;
    std::string	parent;
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
      service = pt.get<std::string>("service");
      parent = pt.get<std::string>("parent");
      details = pt.get<std::string>("details");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");

      std::string id = angru::mvc::model::ChannelModel::AddChannel(
                                                  name,
                                                  title,
                                                  service,
                                                  parent,
                                                  created_by,
                                                  details,
                                                  status,
                                                  situation,
                                                  description );
      std::string message = "{\"message\":\"Channel Added.\", \"id\":\"" + id + "\"}";
      response.send(Pistache::Http::Code::Ok, message);
    }
    catch (std::exception const& e){
      std::cout << e.what() << '\n';
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"Channel not found.\"}");
    }
}

void ChannelController::doUpdateChannel(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "channels", UPDATE_ITEM);
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
    std::string	service;
    std::string	parent;
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
      service = pt.get<std::string>("service");
      parent = pt.get<std::string>("parent");
      details = pt.get<std::string>("details");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");
      angru::mvc::model::ChannelModel::UpdateChannel(
                                                  id,
                                                  name,
                                                  title,
                                                  service,
                                                  parent,
                                                  updated_by,
                                                  details,
                                                  status,
                                                  situation,
                                                  description );
      response.send(Pistache::Http::Code::Ok, "Channels updated.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"Channels not found.\"}");
    }
 }

} // model
} // mvc
} // angru
