#include <iostream>
#include <vector>
#include <algorithm>
#include <pthread.h>

#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>

#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "_PostgreSQL.h"
#include "_CSVWriter.h"
#include "_CSVReader.h"
#include "_JSONWriter.h"
#include "_JSONReader.h"
#include "_RESTServer.h"

#include "_error.h"
#include "_log.h"

#include "student.h"
#include "product.h"

int main(int argc, char const *argv[])
{
	std::cout<<"angru version .010 Check Logfile..."<<std::endl;
	try
	{
		std::cout<<"setup database connection_string..."<<std::endl;
		_PostgreSQL::setup();

		Pistache::Port port(9080);

    int thr = 2;

    if (argc >= 2) {
        port = std::stol(argv[1]);

        if (argc == 3)
            thr = std::stol(argv[2]);
    }
		Pistache::Address addr(Pistache::Ipv4::any(), port);
		std::cout << "Cores = " << std::thread::hardware_concurrency() << std::endl;
		std::cout << "Using " << thr << " threads" << std::endl;
		REST_Server rest_server(addr);
		rest_server.init();
		rest_server.start();
		rest_server.shutdown();
	}
	catch(const _error& e)
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
