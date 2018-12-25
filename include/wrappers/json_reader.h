#ifndef ANGRU_JSONREADER_H_
#define ANGRU_JSONREADER_H_
#include <boost/property_tree/ptree.hpp>

namespace angru{
namespace wrapper{

class JsonReader
{
	std::string fileName;

public:
	JsonReader(std::string filename) :
			fileName(filename)
	{ }

	boost::property_tree::ptree GetData();
};

} // wrapper
} // angru

#endif // ANGRU_JSONREADER_H_
