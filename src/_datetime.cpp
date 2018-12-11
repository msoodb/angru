#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "_datetime.h"
#include "_math.h"


void _datetime::init()
{
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

void _datetime::sample()
{
  auto start = std::chrono::system_clock::now();
  std::cout << "f(44) = " << _math::fibonacci(44) << '\n';
  auto end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end-start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished computation at " << std::ctime(&end_time)
            << "elapsed time: " << elapsed_seconds.count() << "s\n";
}

void _datetime::sampleII()
{
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
