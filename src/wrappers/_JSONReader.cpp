#include "wrappers/_JSONReader.h"

#include <iostream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/_error.h"
#include "tools/_log.h"

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
