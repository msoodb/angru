// This is start of the header guard.  CSVWRITER_H can be any unique name.  By convention, we use the name of the header file.
#ifndef CSVWRITER_H
#define CSVWRITER_H


// This is the content of the .h file, which is where the declarations go
class CSVWriter
{
	std::string fileName;
	std::string delimeter;
	int linesCount;

public:
	CSVWriter(std::string filename, std::string delm = ",") :
			fileName(filename), delimeter(delm), linesCount(0)
	{}
	/*
	 * Member function to store a range as comma seperated value
	 */
	template<typename T>
	void addDatainRow(T first, T last);

  template<typename T>
	void addData(T data);
};


// This is the end of the header guard
#endif
