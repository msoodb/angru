#ifndef ANGRU_CSVREADER_H_
#define ANGRU_CSVREADER_H_

#include <iostream>
#include <vector>

class CSVReader
{
	std::string fileName;
	std::string delimeter;

public:
	CSVReader(std::string filename, std::string delm = ",") :
			fileName(filename), delimeter(delm)
	{ }

	std::vector<std::vector<std::string> > getData();
};

#endif // ANGRU_CSVREADER_H_
