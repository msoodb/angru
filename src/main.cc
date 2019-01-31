#include <iostream>
#include <vector>
#include <algorithm>
#include <pthread.h>
#include <future>
#include <chrono>
#include <thread>
#include <locale>
#include <clocale>
#include <experimental/filesystem>

#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/locale.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "wrappers/postgresql.h"
#include "wrappers/csv_writer.h"
#include "wrappers/csv_reader.h"
#include "wrappers/json_writer.h"
#include "wrappers/json_reader.h"
#include "wrappers/rest_server.h"
#include "wrappers/http_client.h"
#include "tools/security.h"
#include "tools/system.h"
#include "tools/log.h"
#include "tools/math.h"
#include "models/product_model.h"
#include "structures/async_structure.h"

int main(int argc, char const *argv[])
{
	std::cout<<"angru version .011"<<std::endl;
	try
	{
		int thr = 2;
		int port = 9080;
    if (argc >= 2) {
        port = std::stol(argv[1]);
        if (argc == 3){
					thr = std::stol(argv[2]);
				}
    }
		LOG_INFO << "setup logfile using boost...";
		LOG_INFO << "setup database connection_string using pqxx...";
		angru::wrapper::Postgresql::Setup();
		LOG_INFO << "setup datetime and calendar using boost...";
		angru::system::localization::Setup();
		LOG_INFO << "setup RestServer using pistache...";
		//angru::wrapper::RestServer::Setup(port, thr);
		LOG_INFO << "setup HttpClient using pistache...";
		//angru::wrapper::HttpClient::Setup();
//---------------------------------------------------------------------------
		//std::string page="http://api.timezonedb.com:80/v2.1/get-time-zone";
		std::string page="http://jsonplaceholder.typicode.com:80/todos/1";
    Pistache::Http::Uri::Query query;
    query.add("key","97IQ2W4BJCT5");
    query.add("format","json");
    query.add("by","zone");
    query.add("zone","America/Chicago");
		std::string body;
		Pistache::Http::Code code;
		angru::wrapper::HttpClient::Get(page, body, code);

	}
	catch(const angru::system::exception::error & e)
	{
    LOG_ERROR << e.what();
		return 1;
	}
	catch(const std::exception& e)
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
