#ifndef ANGRU_CSVWRITER_H_
#define ANGRU_CSVWRITER_H_

class CSVWriter
{
	std::string fileName;
	std::string delimeter;
	int linesCount;

public:
	CSVWriter(std::string filename, std::string delm = ",") :
			fileName(filename), delimeter(delm), linesCount(0)
	{}
	template<typename T>
	void addDatainRow(T first, T last);

  template<typename T>
	void addData(T data);
};

#endif
