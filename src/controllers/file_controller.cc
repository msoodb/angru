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

namespace angru{
namespace mvc{
namespace controller{

FileController::FileController(){}
FileController::~FileController(){}
void FileController::doGetFile(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    //angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
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
    angru::security::authorization::AuthorizationCheck(request,response);
    try
    {
      auto body = request.body();
      auto headers = request.headers();
      auto content_type = headers.tryGet<Pistache::Http::Header::ContentType>();
      std::string boundary;
      MultipartFiles files;

      if (content_type != nullptr && content_type->mime() == MIME(Multipart, FormData)){
        std::cout << "content_type is: " << content_type->mime().toString() << '\n';
        parse_multipart_boundary(content_type->mime().toString(), boundary);
        std::cout << "boundary is: " << boundary <<'\n';

        parse_multipart_formdata(boundary, body, files);

        for (MultipartFileIterator it = files.begin(); it != files.end(); it++){
          std::cout << "name : " << it->first << '\n';
          std::cout << "filename : " << it->second.filename << '\n';
          std::cout << "content_type : " << it->second.content_type << '\n';
          std::cout << "offset : " << it->second.offset << '\n';
          std::cout << "length : " << it->second.length << '\n';
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

bool FileController::parse_multipart_boundary(const std::string& content_type, std::string& boundary)
{
    auto pos = content_type.find("boundary=");
    if (pos == std::string::npos) {
        return false;
    }

    boundary = content_type.substr(pos + 9);
    return true;
}

bool FileController::parse_multipart_formdata(
    const std::string& boundary, const std::string& body, MultipartFiles& files)
{
    static std::string dash = "--";
    static std::string crlf = "\r\n";

    static std::regex re_content_type(
        "Content-Type: (.*?)", std::regex_constants::icase);

    static std::regex re_content_disposition(
        "Content-Disposition: form-data; name=\"(.*?)\"(?:; filename=\"(.*?)\")?",
        std::regex_constants::icase);

    auto dash_boundary = dash + boundary;

    auto pos = body.find(dash_boundary);
    if (pos != 0) {
        return false;
    }

    pos += dash_boundary.size();

    auto next_pos = body.find(crlf, pos);
    if (next_pos == std::string::npos) {
        return false;
    }

    pos = next_pos + crlf.size();

    while (pos < body.size()) {
        next_pos = body.find(crlf, pos);
        if (next_pos == std::string::npos) {
            return false;
        }

        std::string name;
        MultipartFile file;

        auto header = body.substr(pos, (next_pos - pos));

        while (pos != next_pos) {
            std::smatch m;
            if (std::regex_match(header, m, re_content_type)) {
                file.content_type = m[1];
            } else if (std::regex_match(header, m, re_content_disposition)) {
                name = m[1];
                file.filename = m[2];
            }

            pos = next_pos + crlf.size();

            next_pos = body.find(crlf, pos);
            if (next_pos == std::string::npos) {
                return false;
            }

            header = body.substr(pos, (next_pos - pos));
        }

        pos = next_pos + crlf.size();

        next_pos = body.find(crlf + dash_boundary, pos);

        if (next_pos == std::string::npos) {
            return false;
        }

        file.offset = pos;
        file.length = next_pos - pos;

        pos = next_pos + crlf.size() + dash_boundary.size();

        next_pos = body.find(crlf, pos);
        if (next_pos == std::string::npos) {
            return false;
        }

        files.emplace(name, file);

        pos = next_pos + crlf.size();
    }
    return true;
}

} // controller
} // mvc
} // angru
