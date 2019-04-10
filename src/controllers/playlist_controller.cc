#include "controllers/playlist_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/playlist_model.h"
#include "models/privilege_model.h"

namespace angru{
namespace mvc{
namespace controller{

PlaylistController::PlaylistController(){}
PlaylistController::~PlaylistController(){}

void PlaylistController::doGetAllPlaylists(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "playlists", GET_ITEMS);
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
    boost::property_tree::ptree playlists = angru::mvc::model::PlaylistModel::GetAllPlaylistsJson(page, limit, filter, order);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, playlists);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"Playlists not found.\"}");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void PlaylistController::doGetPlaylists(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "playlists", GET_ITEMS);
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
    }
    boost::property_tree::ptree playlists = angru::mvc::model::PlaylistModel::GetPlaylistsJson(page, limit, service_id, filter);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, playlists);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"Playlists not found.\"}");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void PlaylistController::doGetPlaylist(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "playlists", GET_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    std::string id = "";
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<std::string>();
    }
    boost::property_tree::ptree playlist = angru::mvc::model::PlaylistModel::GetPlaylistJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, playlist);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "{\"message\":\"Playlist not found.\"}");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void PlaylistController::doDeletePlaylist(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "playlists", DELETE_ITEM);
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
    angru::mvc::model::PlaylistModel::DeletePlaylist(id);
    response.send(Pistache::Http::Code::Ok, "Playlist deleted.");
}

void PlaylistController::doAddPlaylist(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "playlists", ADD_ITEM);
    if(!authorized){
      response.send(Pistache::Http::Code::Forbidden, "{\"message\":\"Forbidden request.\"}");
      return;
    }
    auto body = request.body();
    std::string created_by = user_id;
    std::string	name;
    std::string	title;
    std::string	service;
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
      details = pt.get<std::string>("details");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");

      std::string id = angru::mvc::model::PlaylistModel::AddPlaylist(
                                                  name,
                                                  title,
                                                  service,
                                                  created_by,
                                                  details,
                                                  status,
                                                  situation,
                                                  description );
      std::string message = "{\"message\":\"Playlist Added.\", \"id\":\"" + id + "\"}";
      response.send(Pistache::Http::Code::Ok, message);
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Playlists not found.");
    }
}

void PlaylistController::doUpdatePlaylist(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    std::string user_id = angru::security::authorization::AuthenticationCheck(request,response);
    bool authorized = angru::mvc::model::PrivilegeModel::AuthorizationCheck(user_id, "playlists", UPDATE_ITEM);
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
      details = pt.get<std::string>("details");
      status = pt.get<int>("status");
      situation = pt.get<int>("situation");
      description = pt.get<std::string>("description");
      angru::mvc::model::PlaylistModel::UpdatePlaylist(
                                                  id,
                                                  name,
                                                  title,
                                                  service,
                                                  updated_by,
                                                  details,
                                                  status,
                                                  situation,
                                                  description );
      response.send(Pistache::Http::Code::Ok, "Playlists updated.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Playlists not found.");
    }
 }

} // model
} // mvc
} // angru
