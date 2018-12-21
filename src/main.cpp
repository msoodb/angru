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
#include "boost/date_time/gregorian/gregorian.hpp"

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

#include "productModel.h"


int main(int argc, char const *argv[])
{
	std::cout<<"angru version .010"<<std::endl;
	try
	{
		int thr = 2;
		int port = 9080;
    if (argc >= 2) {
        port = std::stol(argv[1]);
        if (argc == 3)
            thr = std::stol(argv[2]);
    }
		//------------------------------------------------------------------
		std::cout<<"setup logfile using boost..."<<std::endl;

		std::cout<<"setup database connection_string using pqxx..."<<std::endl;
		_PostgreSQL::setup();

		std::cout<<"setup datetime and calendar using boost..."<<std::endl;
		_localize::setup();

		//std::cout<<"setup HTTP_Client using pistache..."<<std::endl;
		//HTTP_Client::setup();

		//std::cout<<"setup REST_Server using pistache..."<<std::endl;
		//REST_Server::setup(port, thr);
		//------------------------------------------------------------------

		std::cout << "----------------------------------------------------" << '\n';
		boost::locale::date_time now;
		std::cout << "Now is "<< now << std::endl;
		std::cout << "The current weekday is "<< boost::locale::as::ftime("%A") << now << std::endl;

		boost::locale::date_time tomorrow = now + boost::locale::period::day();
		std::cout << "Tomarrow is " << boost::locale::as::date << tomorrow << '\n';

		boost::locale::date_time next_month = now + boost::locale::period::month();
		std::cout << "Next month is "<<boost::locale::as::datetime << next_month << '\n';
		//boost::gregorian::date d1 = boost::gregorian::date_from_iso_string("2016-06-23 06:40:25+04:30");
		//std::cout << d1 << '\n';

		std::cout << "-----------------------------------------------------" << '\n';
		_localize::output();
		//std::cout << "The language code is " << std::use_facet<boost::locale::info>(some_locale).language() << std::endl;

		/*std::string grussen = "grüßEN";
		std::cout   <<"Upper "<< boost::locale::to_upper(grussen) << std::endl
            <<"Lower "<< boost::locale::to_lower(grussen) << std::endl
            <<"Title "<< boost::locale::to_title(grussen) << std::endl
            <<"Fold  "<< boost::locale::fold_case(grussen) << std::endl;*/

		//std::cout << boost::locale::as::currency << 1235.6 <<'\n';

		//ProductModel::addProduct("mmm1911", 120.5,
						//	"2016-06-22 19:10:25-07", "2016-06-22 19:10:25-07", "{gunl}");
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
