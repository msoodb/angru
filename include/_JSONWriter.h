#ifndef ANGRU_JSONWRITER_H_
#define ANGRU_JSONWRITER_H_

class JSONWriter
{
	std::string fileName;
	std::string delimeter;
	int linesCount;

public:
	JSONWriter(std::string filename, std::string delm = ",") :
			fileName(filename), delimeter(delm), linesCount(0)
	{}
	template<typename T>
	void addDatainRow(T first, T last);

	void addData(boost::property_tree::ptree);
};

#endif
