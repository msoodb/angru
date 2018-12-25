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

class Postgresql
{
private:
	static std::string dbname;
	static std::string user;
  static std::string password;
  static std::string hostaddr;
  static std::string port;
	static std::string connection_str;
public:
	Postgresql();
	static void setup();
	static std::string connection_string();
};

} // wrapper
} // angru

#endif // ANGRU_POSTGRESQL_H_
