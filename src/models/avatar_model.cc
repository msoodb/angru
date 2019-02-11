#include "models/avatar_model.h"

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

AvatarModel::AvatarModel(){}
AvatarModel::~AvatarModel(){}

pqxx::result AvatarModel::GetAvatar(int id){

}
std::string AvatarModel::AddAvatar(const std::string & filename, const std::string & data,
      size_t offset, size_t length){
  std::string path= "/home/masoud/Projects/angru/avatars/" + filename;
  std::ofstream out(path);
  out << data.substr(offset, length);
  out.close();
  return path;
}

bool AvatarModel::DeleteAvatar(const std::string & path){
  std::string deleted_path = path + ".deleted";
  int result = std::rename(path.c_str(), deleted_path.c_str());
  if( result != 0 ){
    return false;
  }
  else{
    return true;
  }
}


} // model
} // mvc
} // angru
