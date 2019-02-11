#include "controllers/avatar_controller.h"

#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <cstdio>


#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/avatar_model.h"
#include "tools/body_parser.h"


namespace angru{
namespace mvc{
namespace controller{

AvatarController::AvatarController(){}
AvatarController::~AvatarController(){}
void AvatarController::doGetAvatar(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    // int id = -1;
    // if (request.hasParam(":id")) {
    //     auto value = request.param(":id");
    //     id = value.as<int>();
    // }
    // boost::property_tree::ptree avatar = angru::mvc::model::AvatarModel::GetAvatarJson(id);
    // std::ostringstream oss;
    // boost::property_tree::write_json(oss, avatar);
    //
    // std::string iniavatar_text = oss.str();
    //
    // if (iniavatar_text.empty()) {
    //   response.send(Pistache::Http::Code::Not_Found, "Avatars not found.");
    // } else {
    //   response.send(Pistache::Http::Code::Ok, iniavatar_text);
    // }
    response.send(Pistache::Http::Code::Ok, "Avatar.");
}
void AvatarController::doAddAvatar(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    try
    {
      auto body = request.body();
      auto headers = request.headers();
      std::string id = "";
      if (request.hasParam(":id")) {
          auto value = request.param(":id");
        id = value.as<std::string>();
      }
      auto content_type = headers.tryGet<Pistache::Http::Header::ContentType>();
      std::string boundary;
      angru::tools::parser::MultipartFiles files;

      if (content_type != nullptr && content_type->mime() == MIME(Multipart, FormData)){
        angru::tools::parser::parse_multipart_boundary(content_type->mime().toString(), boundary);
        angru::tools::parser::parse_multipart_formdata(boundary, body, files);

        for (angru::tools::parser::MultipartFileIterator it = files.begin(); it != files.end(); it++){
          std::string path = angru::mvc::model::AvatarModel::AddAvatar(
                                                  id,
                                                  body,
                                                  it->second.offset,
                                                  it->second.length);
          response.send(Pistache::Http::Code::Ok, "{\"message\":\"success\", \"path\":\"" + path + "\"}");
        }
      }
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Avatar not added.");
    }
}

} // controller
} // mvc
} // angru
