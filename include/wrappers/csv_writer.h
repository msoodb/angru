#ifndef ANGRU_CSVWRITER_H_
#define ANGRU_CSVWRITER_H_

#include <iostream>

namespace angru{
namespace wrapper{

class CsvWriter
{
	std::string fileName;
	std::string delimeter;
	int linesCount;

public:
	CsvWriter(std::string filename, std::string delm = ",") :
			fileName(filename), delimeter(delm), linesCount(0)
	{}
	template<typename T>
	void AddDataRow(T first, T last);

  template<typename T>
	void AddData(T data);
};

} // wrapper
} // angru

#endif // ANGRU_CSVWRITER_H_
