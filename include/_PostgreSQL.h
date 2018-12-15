// This is start of the header guard.  CSVREADER_H can be any unique name.  By convention, we use the name of the header file.
#ifndef _PostgreSQL_H
#define _PostgreSQL_H

#include <pqxx/pqxx>


//#define POSTGRES_CONN pqxx::connection
// This is the content of the .h file, which is where the declarations go
#define DBNAME std::string
#define USER std::string
#define PASSWORD std::string
#define HOSTADDR std::string
#define PORT std::string
#define OFFSET_COUNT 20


class _PostgreSQL
{
private:
	static std::string _dbname;
	static std::string _user;
  static std::string _password;
  static std::string _hostaddr;
  static std::string _port;
	static std::string _connection_string;
public:
	_PostgreSQL();
	static void setup();
	static std::string connection_string();
};
// This is the end of the header guard
#endif
