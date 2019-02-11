#include "models/avatar_model.h"

#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <cstdio>
#include <sys/types.h>
#include <dirent.h>

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

std::string AvatarModel::GetAvatar(std::string & filename){
  std::string path= "/home/masoud/Projects/angru/avatars/";
  DIR* dirp = opendir(path.c_str());
  struct dirent * dp;
  while ((dp = readdir(dirp)) != NULL) {
    std::string fn(dp->d_name);
    if (fn.find(filename) != std::string::npos) {
      closedir(dirp);
      return path+fn;
    }
    // if(dp->d_name == filename){
    //   closedir(dirp);
    //   return path+filename;
    // }
  }
  closedir(dirp);
  return path+"default_male.jpg";
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
