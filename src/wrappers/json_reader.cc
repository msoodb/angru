#include "wrappers/json_reader.h"

#include <iostream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"

namespace angru{
namespace wrapper{

boost::property_tree::ptree JsonReader::GetData()
{
  // Create a root
  boost::property_tree::ptree iroot;

  boost::property_tree::read_json(fileName, iroot);

  // Return
	return iroot;
}

} // wrapper
} // angru
