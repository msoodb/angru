#ifndef ANGRU_FILE_CONTROLLER_H_
#define ANGRU_FILE_CONTROLLER_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/description.h>
#include <pistache/router.h>
#include <pistache/serializer/rapidjson.h>

namespace angru{
namespace mvc{
namespace controller{

class FileController
{
public:
	FileController();
	~FileController();
	static void doGetFile(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void doDeleteFile(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void doAddFile(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void writeToFile(const std::string & url, const std::string & data);
};

} // controller
} // mvc
} // angru

#endif // ANGRU_FILE_CONTROLLER_H_
