#ifndef ANGRU_BODY_PARSER_H_
#define ANGRU_BODY_PARSER_H_

#include <iostream>
#include <vector>
#include <map>
#include <regex>

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/description.h>
#include <pistache/router.h>
#include <pistache/serializer/rapidjson.h>

namespace angru{
namespace tools{
namespace parser{

  struct MultipartFile {
    std::string filename;
    std::string content_type;
    size_t offset = 0;
    size_t length = 0;
  };
  typedef std::multimap<std::string, MultipartFile> MultipartFiles;
  typedef std::multimap<std::string, MultipartFile>::iterator MultipartFileIterator;

  bool parse_multipart_boundary(const std::string& content_type, std::string& boundary);
	bool parse_multipart_formdata(const std::string& boundary,
		const std::string& body, MultipartFiles& files);

} // namespace parser
} // namespace tools
} // namespace angru

#endif // ANGRU_BODY_PARSER_H_
