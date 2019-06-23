#include "models/file_model.h"

#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <cstdio>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "wrappers/csv_writer.h"

namespace angru{
namespace mvc{
namespace model{

FileModel::FileModel(){}
FileModel::~FileModel(){}

std::string FileModel::AddFile(const std::string & filename, const std::string & data,
      size_t offset, size_t length)
{
  std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(
      std::chrono::system_clock::now().time_since_epoch());
  std::string name = std::to_string(ms.count()) + filename;
  //std::string path = "/home/angru/angru/files/" + name;
  //std::string path = "/home/masoud/Projects/angru/files/" + name;
  std::string path = name;
  std::ofstream out(path);
  out << data.substr(offset,length);
  out.close();
  return path;
}

bool FileModel::DeleteFile(const std::string & path){
  std::string deleted_path = path + ".deleted";
  int result = std::rename(path.c_str(), deleted_path.c_str());
  if( result != 0 ){
    return false;
  }
  return true;
}


} // model
} // mvc
} // angru
