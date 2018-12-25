#include "wrappers/_CSVReader.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>

#include <boost/algorithm/string.hpp>
#include <boost/current_function.hpp>
#include "tools/_system.h"


/*
* Parses through csv file line by line and returns the data
* in vector of vector of strings.
*/
std::vector<std::vector<std::string> > CSVReader::getData()
{
  std::cout <<fileName<< '\n';
	std::ifstream file(fileName);
  std::cout << "Could not open file" << '\n';
	if(!file.is_open())
	{
		throw angru::system::exception::error("Could not open file " + fileName);
	}

	std::vector<std::vector<std::string> > dataList;

	std::string line = "";
	// Iterate through each line and split the content using delimeter
	while (getline(file, line))
	{
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
		dataList.push_back(vec);
	}
	// Close the File
	if(!file.eof())
	{
		throw angru::system::exception::error("Error reading dictionary file " + fileName);
	}
	file.close();

	return dataList;
}
