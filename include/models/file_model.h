#ifndef ANGRU_FILE_MODEL_H_
#define ANGRU_FILE_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace angru{
namespace mvc{
namespace model{

class FileModel
{
public:
	FileModel();
	~FileModel();
  static pqxx::result GetFile(int);
	static std::string AddFile(
														const std::string & filename,
														const std::string & data,
	      										size_t offset,
														size_t length);
	static bool DeleteFile(const std::string & path);
};

} // model
} // mvc
} // angru

#endif // ANGRU_FILE_MODEL_H_
