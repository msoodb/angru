// This is start of the header guard.  CSVREADER_H can be any unique name.  By convention, we use the name of the header file.
#ifndef CSVREADER_H
#define CSVREADER_H
 
// This is the content of the .h file, which is where the declarations go
class CSVReader
{
	std::string fileName;
	std::string delimeter;
 
public:
	CSVReader(std::string filename, std::string delm = ",") :
			fileName(filename), delimeter(delm)
	{ }
 
	// Function to fetch data from a CSV File
	std::vector<std::vector<std::string> > getData();
};
 
// This is the end of the header guard
#endif