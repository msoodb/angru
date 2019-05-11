#include "controllers/playlists_content_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/playlists_content_model.h"
#include "models/privilege_model.h"

namespace angru{
namespace mvc{
namespace controller{

PlaylistsContentController::PlaylistsContentController(){}
PlaylistsContentController::~PlaylistsContentController(){}

void PlaylistsContentController::doGetPlaylistsContents(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "playlists_contents", GET_ITEMS);
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
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"Playlists not found.\"}");
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
      filter = filter + " AND content = '" + content_id + "'";
    }
    else{
      filter = " content = '" + content_id + "'";
    }
    std::string order;
    if(query.has("order")) {
      auto value = query.get("order").get();
      order = angru::security::cryptography::decode_base64(value);
    }
    boost::property_tree::ptree playlists_contents = angru::mvc::model::PlaylistsContentModel::GetPlaylistsContentsJson(page, limit, filter, order);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, playlists_contents);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "PlaylistsContents not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void PlaylistsContentController::doGetPlaylistsContent(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "playlists_contents", GET_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    boost::property_tree::ptree playlists_content = angru::mvc::model::PlaylistsContentModel::GetPlaylistsContentJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, playlists_content);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "PlaylistsContents not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void PlaylistsContentController::doDeletePlaylistsContent(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "playlists_contents", DELETE_ITEM);
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
    angru::mvc::model::PlaylistsContentModel::DeletePlaylistsContent(id);
    response.send(Pistache::Http::Code::Ok, "PlaylistsContent deleted.");
}

void PlaylistsContentController::doAddPlaylistsContent(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "playlists_contents", ADD_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    auto body = request.body();
    std::string created_by = user_id;
    std::string	playlist;
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
      playlist = pt.get<std::string>("playlist");
      content = pt.get<std::string>("content");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");

      std::string id = angru::mvc::model::PlaylistsContentModel::AddPlaylistsContent(
                                                  playlist,
                                                  content,
                                                  created_by,
                                                  status,
                                                  situation,
                                                  description );
      std::string message = "{\"message\":\"PlaylistsContent Added.\", \"id\":\"" + id + "\"}";
      response.send(Pistache::Http::Code::Ok, message);
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "PlaylistsContents not found.");
    }
}

void PlaylistsContentController::doUpdatePlaylistsContent(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "playlists_contents", UPDATE_ITEM);
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
    std::string	playlist;
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
      playlist = pt.get<std::string>("playlist");
      content = pt.get<std::string>("content");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");
      angru::mvc::model::PlaylistsContentModel::UpdatePlaylistsContent(
                                                  id,
                                                  playlist,
                                                  content,
                                                  updated_by,
                                                  status,
                                                  situation,
                                                  description );
      response.send(Pistache::Http::Code::Ok, "PlaylistsContents updated.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "PlaylistsContents not found.");
    }
 }

} // model
} // mvc
} // angru
