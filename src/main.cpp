#include <iostream>
#include <vector>
#include <algorithm>
#include <pthread.h>
#include <future>
#include <chrono>
#include <thread>

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


#include "_PostgreSQL.h"
#include "_CSVWriter.h"
#include "_CSVReader.h"
#include "_JSONWriter.h"
#include "_JSONReader.h"
#include "_RESTServer.h"
#include "_HTTPClient.h"
#include "_cryptography.h"

#include "_localize.h"
#include "_error.h"
#include "_log.h"
#include "_math.h"


#include "productModel.h"
#include "async_structure.h"

void hello() {
	for (size_t i = 0; i < 10; i++) {
		std::cout << "hello world!" << '\n';
	}
}

int main(int argc, char const *argv[])
{
	std::cout<<"angru version .010"<<std::endl;
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
		//------------------------------------------------------------------
		LOG_INFO << "setup logfile using boost...";
		LOG_INFO << "setup database connection_string using pqxx...";
		_PostgreSQL::setup();
		LOG_INFO << "setup datetime and calendar using boost...";
		_localize::setup();
		LOG_INFO << "setup HTTP_Client using pistache...";
		//HTTP_Client::setup();
		LOG_INFO << "setup REST_Server using pistache...";
		REST_Server::setup(port, thr);
		//------------------------------------------------------------------
		std::thread t(hello);
		std::cout << "before join" << '\n';
		t.join();
		std::cout << "after join thread" << '\n';
	}
	catch(const _error& e)
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
