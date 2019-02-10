#ifndef ANGRU_FILE_CONTROLLER_H_
#define ANGRU_FILE_CONTROLLER_H_

#include <iostream>
#include <vector>
#include <map>
#include <regex>

#include <pqxx/pqxx>

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/description.h>
#include <pistache/router.h>
#include <pistache/serializer/rapidjson.h>

namespace angru{
namespace mvc{
namespace controller{

struct MultipartFile {
  std::string filename;
  std::string content_type;
  size_t offset = 0;
  size_t length = 0;
};
typedef std::multimap<std::string, MultipartFile> MultipartFiles;
typedef std::multimap<std::string, MultipartFile>::iterator MultipartFileIterator;

class FileController
{
public:
	FileController();
	~FileController();
	static void doGetFile(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void doAddFile(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static bool parse_multipart_boundary(const std::string& content_type, std::string& boundary);
	static bool parse_multipart_formdata(const std::string& boundary,
		const std::string& body, MultipartFiles& files);
};

} // controller
} // mvc
} // angru

#endif // ANGRU_FILE_CONTROLLER_H_
