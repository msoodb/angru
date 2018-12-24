#ifndef ANGRU_JSONREADER_H_
#define ANGRU_JSONREADER_H_
#include <boost/property_tree/ptree.hpp>

class JSONReader
{
	std::string fileName;

public:
	JSONReader(std::string filename) :
			fileName(filename)
	{ }

	boost::property_tree::ptree getData();
};

#endif
