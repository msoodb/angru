#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <pqxx/pqxx>

#include "_CSVWriter.h"
#include "_error.h"
#include "_log.h"
/*
 * This Function accepts a range and appends all the elements in the range
 * to the last row, seperated by delimeter (Default is comma)
 */
template<typename T>
void CSVWriter::addDatainRow(T first, T last)
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
template void CSVWriter::addDatainRow(std::vector<std::string>::iterator, std::vector<std::string>::iterator);
template void CSVWriter::addDatainRow(std::deque<std::string>::iterator, std::deque<std::string>::iterator);
template void CSVWriter::addDatainRow(std::list<std::string>::iterator, std::list<std::string>::iterator);
template void CSVWriter::addDatainRow(pqxx::row::iterator, pqxx::row::iterator);

template<typename T>
void CSVWriter::addData(T data)
{
	LOG_INFO << "start writing data in csv: "<<fileName;
	for (auto row : data)
	{
		addDatainRow(row.begin(), row.end());
	}
	LOG_INFO << "end writing data in csv: "<<fileName;
}
template void CSVWriter::addData(pqxx::result);
