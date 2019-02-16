#include "controllers/file_controller.h"

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
#include "models/file_model.h"
#include "tools/body_parser.h"

namespace angru{
namespace mvc{
namespace controller{

FileController::FileController(){}
FileController::~FileController(){}
void FileController::doGetFile(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::AuthenticationCheck(request,response);
    // int id = -1;
    // if (request.hasParam(":id")) {
    //     auto value = request.param(":id");
    //     id = value.as<int>();
    // }
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
void FileController::doAddFile(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::AuthenticationCheck(request,response);
    try
    {
      auto body = request.body();
      auto headers = request.headers();
      auto content_type = headers.tryGet<Pistache::Http::Header::ContentType>();
      std::string boundary;
      angru::tools::parser::MultipartFiles files;

      if (content_type != nullptr && content_type->mime() == MIME(Multipart, FormData)){
        angru::tools::parser::parse_multipart_boundary(content_type->mime().toString(), boundary);
        angru::tools::parser::parse_multipart_formdata(boundary, body, files);

        for (angru::tools::parser::MultipartFileIterator it = files.begin(); it != files.end(); it++){
          std::string path = angru::mvc::model::FileModel::AddFile(
                                                  it->second.filename,
                                                  body,
                                                  it->second.offset,
                                                  it->second.length);
          response.send(Pistache::Http::Code::Ok, "{\"message\":\"success\", \"path\":\"" + path + "\"}");
        }
      }
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Files not added.");
    }
  }
} // controller
} // mvc
} // angru
