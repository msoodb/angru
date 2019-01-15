#include "wrappers/postgresql.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include "wrappers/json_reader.h"
#include "tools/system.h"



 namespace angru{
 namespace wrapper{

std::string Postgresql::dbname="";
std::string Postgresql::user="";
std::string Postgresql::password="";
std::string Postgresql::hostaddr="";
std::string Postgresql::port="";
std::string Postgresql::connection_str="";

Postgresql::Postgresql(){
}

void Postgresql::Setup()
{
	//JsonReader config_reader("/home/angru/angru/config/config.json");
  JsonReader config_reader("/home/masoud/Projects/angru/config/config.json");
	boost::property_tree::ptree config = config_reader.GetData();
	dbname = config.get<std::string>("connection_string.dbname");
	user = config.get<std::string>("connection_string.user");
	password = config.get<std::string>("connection_string.password");
	hostaddr = config.get<std::string>("connection_string.hostaddr");
	port = config.get<std::string>("connection_string.port");
	connection_str = "dbname = "+dbname+" user = "+user
			+" password = "+password+" hostaddr = "+hostaddr+" port = "+port;
}
std::string Postgresql::connection_string(){
		return connection_str;
}

} // wrapper
} // angru
