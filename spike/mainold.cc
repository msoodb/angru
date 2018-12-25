#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <chrono>
#include <csignal>

#include <pistache/endpoint.h>
#include <pistache/net.h>
#include <pqxx/pqxx>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "postgresql.h"
#include "_rapidjson.h"
#include "_boostjson.h"
#include "csv_writer.h"
#include "_log.h"
#include "_math.h"
#include "_datetime.h"
#include "_signal.h"
#include "_thread.h"

#include "product.h"

struct HelloHandler : public Pistache::Http::Handler {
    HTTP_PROTOTYPE(HelloHandler)

    void onRequest(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter writer) {
        writer.send(Pistache::Http::Code::Ok, "Hello, World!");
    }
};

int main(int argc, char const *argv[])
{
	std::cout<<"Insomnai version .013. Check Logfile."<<std::endl;

	try
	{
		Pistache::Http::listenAndServe<HelloHandler>("*:9080");	  return 0;
	}
	catch(const angru::system::exception::error& e)
	{
    LOG_ERROR << e.what();
		return 1;
	}
	catch(...)
	{
    LOG_ERROR << "Error: unknown exception";
		return 2;
	}
	return 0;
}
