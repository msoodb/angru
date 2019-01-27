#include "controllers/file_controller.h"

#include <iostream>
#include <string>
#include <chrono>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/file_model.h"

namespace angru{
namespace mvc{
namespace controller{

FileController::FileController(){}
FileController::~FileController(){}
void FileController::doGetFile(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*") ;
    response.headers().add<Pistache::Http::Header::AccessControlAllowHeaders>("DNT,X-CustomHeader,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,dataType,Content-Type,api_type,Authorization") ;
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    //angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    // boost::property_tree::ptree file = angru::mvc::model::FileModel::GetFileJson(id);
    // std::ostringstream oss;
    // boost::property_tree::write_json(oss, file);
    //
    // std::string inifile_text = oss.str();
    //
    // if (inifile_text.empty()) {
    //   response.send(Pistache::Http::Code::Not_Found, "Files not found.");
    // } else {
    //   response.send(Pistache::Http::Code::Ok, inifile_text);
    // }
    response.send(Pistache::Http::Code::Ok, "File.");
}
void FileController::doDeleteFile(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.headers().add<Pistache::Http::Header::AccessControlAllowMethods>("OPTIONS, GET, POST, DELETE, PUT");
    response.headers().add<Pistache::Http::Header::AccessControlAllowHeaders>("DNT,X-CustomHeader,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,dataType,Content-Type,api_type,Authorization") ;
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    //angru::mvc::model::FileModel::DeleteFile(id);
    response.send(Pistache::Http::Code::Ok, "File deleted.");
}
void FileController::doAddFile(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*") ;
    response.headers().add<Pistache::Http::Header::AccessControlAllowHeaders>("DNT,X-CustomHeader,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,dataType,Content-Type,api_type,Authorization") ;
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    //angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    auto body = request.body();

    std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch());


    std::string name = std::to_string(ms.count());
    std::string url= "/home/masoud/Projects/angru/files/"+name;
    try
    {
      FileController::writeToFile(url, body);
      response.send(Pistache::Http::Code::Ok, "{\"message\":\"success\", \"url\":\"" + url+name + "\"}");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Files not added.");
    }
}
void FileController::writeToFile(const std::string & url, const std::string & data) {
    std::cout << url <<'\n';
    std::ofstream out(url);
    //out.open(filename.c_str());
    out << data ;
    out.close();
}

} // controller
} // mvc
} // angru
