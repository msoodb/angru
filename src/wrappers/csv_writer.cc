#include "wrappers/csv_writer.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>

#include <boost/algorithm/string.hpp>
#include <pqxx/pqxx>
#include "tools/system.h"
#include "tools/log.h"

namespace angru{
namespace wrapper{

template<typename T>
void CsvWriter::addDatainRow(T first, T last)
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
template void CsvWriter::addDatainRow(std::vector<std::string>::iterator, std::vector<std::string>::iterator);
template void CsvWriter::addDatainRow(std::deque<std::string>::iterator, std::deque<std::string>::iterator);
template void CsvWriter::addDatainRow(std::list<std::string>::iterator, std::list<std::string>::iterator);
template void CsvWriter::addDatainRow(pqxx::row::iterator, pqxx::row::iterator);

template<typename T>
void CsvWriter::addData(T data)
{
	LOG_INFO << "start writing data in csv: "<<fileName;
	for (auto row : data)
	{
		addDatainRow(row.begin(), row.end());
	}
	LOG_INFO << "end writing data in csv: "<<fileName;
}
template void CsvWriter::addData(pqxx::result);

} // wrapper
} // angru
