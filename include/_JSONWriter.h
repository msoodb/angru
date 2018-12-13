// This is start of the header guard. JSONWRITER_H can be any unique name.  By convention, we use the name of the header file.
#ifndef JSONWRITER_H
#define JSONWRITER_H


// This is the content of the .h file, which is where the declarations go
class JSONWriter
{
	std::string fileName;
	std::string delimeter;
	int linesCount;

public:
	JSONWriter(std::string filename, std::string delm = ",") :
			fileName(filename), delimeter(delm), linesCount(0)
	{}
	/*
	 * Member function to store a range as comma seperated value
	 */
	template<typename T>
	void addDatainRow(T first, T last);

	void addData(boost::property_tree::ptree);
};

// This is the end of the header guard
#endif
