#include "wrappers/json_writer.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>

#include <boost/algorithm/string.hpp>
#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"

namespace angru{
namespace wrapper{

template<typename T>
void JsonWriter::addDatainRow(T first, T last)
{
	std::fstream file;
	// Open the file in truncate mode if first line else in Append Mode
	file.open(fileName, std::ios::out | (linesCount ? std::ios::app : std::ios::trunc));

	// Iterate over the range and add each lement to file seperated by delimeter.
	for (; first != last; )
	{
		file << *first;
		if (++first != last)
			file << delimeter;
	}
	file << "\n";
	linesCount++;

	// Close the file
	file.close();
}
template void JsonWriter::addDatainRow(std::vector<std::string>::iterator, std::vector<std::string>::iterator);
template void JsonWriter::addDatainRow(std::deque<std::string>::iterator, std::deque<std::string>::iterator);
template void JsonWriter::addDatainRow(std::list<std::string>::iterator, std::list<std::string>::iterator);
template void JsonWriter::addDatainRow(pqxx::row::iterator, pqxx::row::iterator);

void JsonWriter::addData(boost::property_tree::ptree oroot){
	LOG_INFO << "start writing data in json: "<<fileName;
  boost::property_tree::write_json(fileName, oroot);
	LOG_INFO << "end writing data in json: "<<fileName;
}

} // wrapper
} // angru

/*template<typename T>
void JSONWriter::addData(T data)
{
	LOG_INFO << "start writing data in csv: "<<fileName;
	for (auto row : data)
	{
		addDatainRow(row.begin(), row.end());
	}
	LOG_INFO << "end writing data in csv: "<<fileName;
}
template void JSONWriter::addData(pqxx::result);*/
