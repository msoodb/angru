#include "tools/body_parser.h"

#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/uuid/sha1.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/remove_whitespace.hpp>
#include <jwt/jwt.hpp>



namespace angru{
namespace tools{
namespace parser{

  bool parse_multipart_boundary(const std::string& content_type, std::string& boundary)
  {
      auto pos = content_type.find("boundary=");
      if (pos == std::string::npos) {
          return false;
      }

      boundary = content_type.substr(pos + 9);
      return true;
  }

  bool parse_multipart_formdata(
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

} // namespace parser
} // namespace tools
} // namespace angru
