#include "_localize.h"

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>

#include <boost/locale.hpp>
#include <boost/locale/date_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "_math.h"
#include "_error.h"
#include "_log.h"

void _localize::setup(){
  //LOG_INFO << "set boost::locale::time_zone::global(\"GMT+3:30\")";
  //boost::locale::time_zone::global("GMT+3:30");
  boost::locale::generator gen;
  LOG_INFO << "set std::locale loc = gen(\"en-US.UTF-8\");";
  std::locale loc = gen("en-US.UTF-8");
  std::locale::global(loc);
  std::cout.imbue(loc);
  //boost::locale::calendar	cal(loc,"GMT+4:30");
}

void _localize::output() {
  //std::cout << "The language code is " << std::use_facet<boost::locale::info>(loc).language() << std::endl;
  //std::cout << "The language code is " << std::use_facet<boost::locale::info>(loc).name() << std::endl;
  //std::cout << "The language code is " << std::use_facet<boost::locale::info>(loc).country() << std::endl;
  //std::cout << "The language code is " << std::use_facet<boost::locale::info>(loc).variant() << std::endl;
  //std::cout << "The language code is " << std::use_facet<boost::locale::info>(loc).encoding() << std::endl;
  //std::cout << "The language code is " << std::use_facet<boost::locale::info>(loc).utf8() << std::endl;

  /*int first = cal.first_day_of_week();
  std::cout << first << '\n';
  if(cal.is_gregorian())
    std::cout << "is_gregorian" << '\n';
  else
    std::cout << "not gregorian" << '\n';
  std::cout << cal.get_time_zone() << '\n';
  */
  std::cout << "----------------------------------------------------" << '\n';
  boost::locale::date_time now;
  std::cout << "Now is "<< now << std::endl;
  std::cout << boost::locale::as::datetime << boost::locale::as::local_time << "Local time is: "<< now << std::endl;
  //std::cout << boost::locale::as::gmt << "GMT Time is: "<< now << std::endl;
  //std::cout << boost::locale::as::time_zone("EST") << "Eastern Standard Time is: "<< now << std::endl;

  std::cout <<boost::locale::format("Today {1,date} at {1,time} we had run our first localization example") % time(0)<<std::endl;
  std::cout<<"This is how we show numbers in this locale "<<boost::locale::as::number << 103.34 <<std::endl;
  std::cout<<"This is how we show currency in this locale "<<boost::locale::as::currency << 103.34 <<std::endl;
  std::cout<<"This is typical date in the locale "<<boost::locale::as::date << std::time(0) <<std::endl;
  std::cout<<"This is typical time in the locale "<<boost::locale::as::time << std::time(0) <<std::endl;
  std::cout<<"This is upper case "<<boost::locale::to_upper("Hello World!")<<std::endl;
  std::cout<<"This is lower case "<<boost::locale::to_lower("Hello World!")<<std::endl;
  std::cout<<"This is title case "<<boost::locale::to_title("Hello World!")<<std::endl;
  std::cout<<"This is fold case "<<boost::locale::fold_case("Hello World!")<<std::endl;
  std::cout << "----------------------------------------------------" << '\n';

  boost::locale::date_time now2;
  std::cout << "Now is "<< now2 << std::endl;
  std::cout << "The current weekday is "<< boost::locale::as::ftime("%A") << now2 << std::endl;

  boost::locale::date_time tomorrow = now2 + boost::locale::period::day();
  std::cout << "Tomarrow is " << boost::locale::as::date << tomorrow << '\n';

  boost::locale::date_time next_month = now + boost::locale::period::month();
  std::cout << "Next month is "<<boost::locale::as::datetime << next_month << '\n';
  //boost::gregorian::date d1 = boost::gregorian::date_from_iso_string("2016-06-23 06:40:25+04:30");
  //std::cout << d1 << '\n';

  /*
  boost::gregorian::date d{2014, 5, 12};
  boost::gregorian::date_facet *df = new boost::gregorian::date_facet{"%A, %d %B %Y"};
  std::cout.imbue(std::locale{std::cout.getloc(), df});
  std::cout << d << '\n';*/
}

void _localize::init(){
  // current date/time based on current system
  time_t now = time(0);

  // convert now to string form
  char* dt = ctime(&now);

  // convert now to string form
  std::string strdt = ctime(&now);

  // convert now to tm struct for UTC
  tm *gmtm = gmtime(&now);
  std::string strUTCdt = asctime(gmtm);

  //boost datetime
  boost::gregorian::date weekstart(2002,boost::gregorian::Feb,1);

  std::cout<< "(now)[time_t now = time(0);]: "<< now <<"\n";
  std::cout<< "(dt)[char* dt = ctime(&now);]: "<< dt <<"\n";
  std::cout<< "(strdt)[std::string strdt = ctime(&now);]: "<< strdt <<"\n";
  std::cout<< "(strdt)[std::string strUTCdt = asctime(gmtm);]: "<< strUTCdt <<"\n";
  std::cout<< "(now)[boost::gregorian::date weekstart(2002,Feb,1);]: "<< weekstart <<"\n";
}

void _localize::sample(){
  auto start = std::chrono::system_clock::now();
  std::cout << "f(44) = " << _math::fibonacci(44) << '\n';
  auto end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end-start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished computation at " << std::ctime(&end_time)
            << "elapsed time: " << elapsed_seconds.count() << "s\n";
}

void _localize::sampleII(){
  /* is an absolute time, represented as the integer number of seconds
  since the UNIX epoch (midnight GMT, 1 January 1970) */
  time_t now = time(0);
  std::cout<<"now : "<<now<<std::endl;

  std::string nowdate = ctime(&now);
  std::cout<<"nowdate : "<<nowdate<<std::endl;

  struct tm* timeinfo;
  timeinfo = localtime(&now);
  std::cout<<"timeinfo.sec : "<<timeinfo->tm_sec<<std::endl;
  std::cout<<"timeinfo.min : "<<timeinfo->tm_min<<std::endl;
  std::cout<<"timeinfo.hour : "<<timeinfo->tm_hour<<std::endl;
  std::cout<<"--------------------------------------------------"<<std::endl;
  std::cout<<"timeinfo.mday : "<<timeinfo->tm_mday<<std::endl;
  std::cout<<"timeinfo.mon : "<<timeinfo->tm_mon<<std::endl;
  std::cout<<"timeinfo.year : "<<timeinfo->tm_year<<std::endl;
  std::cout<<"--------------------------------------------------"<<std::endl;
  std::cout<<"timeinfo.wday : "<<timeinfo->tm_wday<<std::endl;
  std::cout<<"timeinfo.yday : "<<timeinfo->tm_yday<<std::endl;
  std::cout<<"timeinfo.isdst : "<<timeinfo->tm_isdst<<std::endl;

  struct tm* birthday;
  birthday = localtime(&now);
  birthday->tm_year = 81;
  birthday->tm_mon = 11;
  birthday->tm_mday = 6;
  mktime(birthday);
  std::cout<<"birthday.year : "<<birthday->tm_year<<std::endl;
  std::cout<<"birthday is : "<<asctime(birthday)<<std::endl;

  /*time_t now;
  time(&now);
  std::cout<<"now : "<<now<<std::endl;*/

  /*long d_timer;   //Problem Year_2038  32bit
  d_timer = time(NULL);
  std::cout<<"d_timer : "<<d_timer<<std::endl;*/

  //clock_t rawclock;
  //struct tm * timeinfo;
}
