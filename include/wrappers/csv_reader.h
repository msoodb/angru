#ifndef ANGRU_CSVREADER_H_
#define ANGRU_CSVREADER_H_

#include <iostream>
#include <vector>

namespace angru{
namespace wrapper{

class CsvReader
{
	std::string fileName;
	std::string delimeter;

public:
	CsvReader(std::string filename, std::string delm = ",") :
			fileName(filename), delimeter(delm)
	{ }

	std::vector<std::vector<std::string> > GetData();
};

} // wrapper
} // angru

#endif // ANGRU_CSVREADER_H_
