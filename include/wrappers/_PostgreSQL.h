#ifndef ANGRU_POSTGRESQL_H_
#define ANGRU_POSTGRESQL_H_

#include <pqxx/pqxx>

#define DBNAME std::string
#define USER std::string
#define PASSWORD std::string
#define HOSTADDR std::string
#define PORT std::string
#define OFFSET_COUNT 20

namespace angru{
namespace wrapper{

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

} // wrapper
} // angru

#endif // ANGRU_POSTGRESQL_H_
