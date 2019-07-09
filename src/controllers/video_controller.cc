#include "controllers/video_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/video_model.h"
#include "models/content_model.h"
#include "models/privilege_model.h"

namespace angru{
namespace mvc{
namespace controller{

VideoController::VideoController(){}
VideoController::~VideoController(){}

void VideoController::doGetVideos(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "videos", GET_ITEMS);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    std::string channel_id = "";
    if (request.hasParam(":channel_id")) {
        auto value = request.param(":channel_id");
        channel_id = value.as<std::string>();
    }
    std::string service_id = "";
    if (request.hasParam(":service_id")) {
        auto value = request.param(":service_id");
        service_id = value.as<std::string>();
    }
    std::string filter;
    auto query = request.query();
    int page = 1;
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
      if(channel_id != ""){
        filter = filter + " AND contents.channel = '" + channel_id + "'";
      }
      if(service_id != ""){
        filter = filter + " AND contents.service = '" + service_id + "'";
      }
    }
    else{
      if(channel_id != ""){
        filter = " contents.channel = '" + channel_id + "'";
      }
      if(service_id != ""){
        filter = " contents.service = '" + service_id + "'";
      }
    }
    std::string order;
    if(query.has("order")) {
      auto value = query.get("order").get();
      order = angru::security::cryptography::decode_base64(value);
    }
    boost::property_tree::ptree videos = angru::mvc::model::VideoModel::GetVideosJson(page, limit, filter, order);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, videos);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"Videos not found..\"}");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void VideoController::doGetVideo(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "videos", GET_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    boost::property_tree::ptree video = angru::mvc::model::VideoModel::GetVideoJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, video);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"Videos not found..\"}");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void VideoController::doDeleteVideo(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "videos", DELETE_ITEM);
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
    angru::mvc::model::VideoModel::DeleteVideo(id);
    response.send(Pistache::Http::Code::Ok, "Video deleted.");
}

void VideoController::doAddVideo(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "videos", ADD_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    auto body = request.body();
    std::string created_by = user_id;
    std::string	service;
    std::string	channel;
    std::string	publisher;
    int	type = 0; // 0 for video
    std::string	name;
    std::string	title;
    std::string	path;
    float	size;
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
      service = pt.get<std::string>("service");
      channel = pt.get<std::string>("channel");
      publisher = pt.get<std::string>("publisher");
      name = pt.get<std::string>("name");
      title = pt.get<std::string>("title");
      path = pt.get<std::string>("path");
      size = pt.get<float>("size");
      details = pt.get<std::string>("details");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");

      std::string content = angru::mvc::model::ContentModel::AddContent(
                                                  service,
                                                  channel,
                                                  publisher,
                                                  type,
                                                  created_by,
                                                  details,
                                                  status,
                                                  situation,
                                                  description );
      std::string id = angru::mvc::model::VideoModel::AddVideo(
                                                  content,
                                                  name,
                                                  title,
                                                  path,
                                                  size,
                                                  created_by,
                                                  details,
                                                  status,
                                                  situation,
                                                  description );
      std::string message = "{\"message\":\"Video Added.\", \"id\":\"" + id + "\",\"content\":\"" + content + "\"}";
      response.send(Pistache::Http::Code::Ok, message);
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"Videos not found..\"}");
    }
}

void VideoController::doUpdateVideo(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "videos", UPDATE_ITEM);
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
    std::string	service;
    std::string	channel;
    std::string	publisher;
    int	type = 0; // 0 for video
    std::string	name;
    std::string	title;
    std::string	path;
    float	size;
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
      service = pt.get<std::string>("service");
      channel = pt.get<std::string>("channel");
      publisher = pt.get<std::string>("publisher");
      name = pt.get<std::string>("name");
      title = pt.get<std::string>("title");
      path = pt.get<std::string>("path");
      size = pt.get<float>("size");
      details = pt.get<std::string>("details");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");

      std::string content = angru::mvc::model::VideoModel::GetContent(id);
      angru::mvc::model::ContentModel::UpdateContent(
                                                  content,
                                                  service,
                                                  channel,
                                                  publisher,
                                                  type,
                                                  updated_by,
                                                  details,
                                                  status,
                                                  situation,
                                                  description );
      angru::mvc::model::VideoModel::UpdateVideo(
                                                  id,
                                                  content,
                                                  name,
                                                  title,
                                                  path,
                                                  size,
                                                  updated_by,
                                                  details,
                                                  status,
                                                  situation,
                                                  description );
      response.send(Pistache::Http::Code::Ok, "{\"message\":\"Videos updated.\"}");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"Videos not found..\"}");
    }
 }

} // model
} // mvc
} // angru
