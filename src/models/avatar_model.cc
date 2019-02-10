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
std::string AvatarModel::AddAvatar(std::string id, std::string ext, const std::string & data){

  std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(
      std::chrono::system_clock::now().time_since_epoch());
  std::string name = std::to_string(ms.count());
  std::string path= "/home/masoud/Projects/angru/avatars/" + id + "." + ext;
  std::ofstream out(path);
  out << data ;
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
