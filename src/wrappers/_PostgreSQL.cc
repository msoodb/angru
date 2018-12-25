#include "wrappers/_PostgreSQL.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include "wrappers/_JSONReader.h"
#include "tools/_system.h"

 std::string _PostgreSQL::_dbname="";
 std::string _PostgreSQL::_user="";
 std::string _PostgreSQL::_password="";
 std::string _PostgreSQL::_hostaddr="";
 std::string _PostgreSQL::_port="";
 std::string _PostgreSQL::_connection_string="";

_PostgreSQL::_PostgreSQL(){
}

void _PostgreSQL::setup()
{
	JSONReader config_reader("../config/config.json");
	boost::property_tree::ptree config = config_reader.getData();
	_dbname = config.get<std::string>("connection_string._dbname");
	_user = config.get<std::string>("connection_string._user");
	_password = config.get<std::string>("connection_string._password");
	_hostaddr = config.get<std::string>("connection_string._hostaddr");
	_port = config.get<std::string>("connection_string._port");
	_connection_string = "dbname = "+_dbname+" user = "+_user
			+" password = "+_password+" hostaddr = "+_hostaddr+" port = "+_port;
}
std::string _PostgreSQL::connection_string(){
		return _connection_string;
}
