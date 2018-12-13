#include <iostream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "_JSONReader.h"
#include "_error.h"
#include "_log.h"


/*
* Parses through csv file line by line and returns the data
* in vector of vector of strings.
*/
boost::property_tree::ptree JSONReader::getData()
{
  // Create a root
  boost::property_tree::ptree iroot;

  // Load the json file in this ptree
  LOG_INFO << "start reading data from json: "<<fileName;
  boost::property_tree::read_json(fileName, iroot);
  LOG_INFO << "end reading data from json: "<<fileName;

  // Return
	return iroot;
}
