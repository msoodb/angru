#include "models/file_model.h"

#include <iostream>
#include <string>

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

pqxx::result FileModel::GetFile(int id){

}
void FileModel::AddFile(){

}

void FileModel::DeleteFile(int id){

}


} // model
} // mvc
} // angru
