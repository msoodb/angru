#include <iostream>
#include <string>
#include <pqxx/pqxx>

#include "_PostgreSQL.h"

/*
 * This Function accepts a range and appends all the elements in the range
 * to the last row, seperated by delimeter (Default is comma)
 */
_PostgreSQL::_PostgreSQL()
{
}

void _PostgreSQL::setup()
{
	//std::cout << _connectionstring<<std::endl;
	//return new pqxx::basic_connection<connect_direct>(C);
	//pqxx::connection C(_connectionstring);
	//return C;
}
std::string _PostgreSQL::connection_string()
{
	std::string _dbname;
	std::string _user;
  std::string _password;
  std::string _hostaddr;
  std::string _port;

	_dbname = "angrudb";
	_user = "angru";
  _password = "1235";
  _hostaddr = "127.0.0.1";
  _port = "5432";

	std::string _connectionstring =
		"dbname = " + _dbname
		+ " user = " + _user
		+ " password = " + _password
		+ " hostaddr = " + _hostaddr
		+ " port = " + _port;
		return _connectionstring;
}
