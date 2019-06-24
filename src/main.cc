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
#include "tools/file_generator_factory.h"
#include "tools/data_generator_factory.h"
#include "models/avatar_model.h"



int main(int argc, char const *argv[])
{
	std::cout<<"angru version .011"<<std::endl;
	try
	{
		std::string execute_path= "/home/masoud/Projects/angru";
		int port = 9080;
		int thr = 2;

    if (argc >= 2) {
			  execute_path = argv[1];
				if(argc >= 3){
					port = std::stol(argv[2]);
				}
        if (argc == 4){
					thr = std::stol(argv[3]);
				}
    }
		LOG_INFO << "setup logfile using boost...";
		LOG_INFO << "setup database connection_string using pqxx...";
		angru::wrapper::Postgresql::Setup(execute_path);
		LOG_INFO << "setup datetime and calendar using boost...";
		angru::system::localization::Setup();
		LOG_INFO << "setup AvatarModel path ...";
		angru::mvc::model::AvatarModel::Setup(execute_path);
		LOG_INFO << "setup RestServer using pistache...";
		angru::wrapper::RestServer::Setup(port, thr);



		LOG_INFO << "setup HttpClient using pistache...";
		//angru::wrapper::HttpClient::Setup();
		LOG_INFO << "generate files using file_generator_factory...";
		//angru::tools::factory::generate();
		LOG_INFO << "generate fake data using data_generator_factory...";
		//angru::tools::factory::GenerateFakeData();
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
