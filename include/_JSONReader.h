// This is start of the header guard. JSONREADER_H can be any unique name.  By convention, we use the name of the header file.
#ifndef JSONREADER_H
#define JSONREADER_H
#include <boost/property_tree/ptree.hpp>

// This is the content of the .h file, which is where the declarations go
class JSONReader
{
	std::string fileName;

public:
	JSONReader(std::string filename) :
			fileName(filename)
	{ }

	// Function to fetch data from a json File
	boost::property_tree::ptree getData();
};

// This is the end of the header guard
#endif
