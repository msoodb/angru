#include <iostream>
#include <vector>
// This is start of the header guard. STUDENT_H can be any unique name.  By convention, we use the name of the header file.
#ifndef STUDENT_H
#define STUDENT_H
 
// This is the content of the .h file, which is where the declarations go
class Student
{	
	int studentId;
	int entryYear;
	std::string firstName;
	std::string middleName;
	std::string lastName;
	double GPA; //Grade Point Average
	char gender;
public:
	static int zx;
	Student();  //Simple Constructor
	Student(
		int new_studentId,
		int new_entryYear,
		std::string new_firstName,
		std::string new_middleName,
		std::string new_lastName,
		double new_GPA, //Grade Point Average
		char new_gender);
	Student (const Student&); //Copy Constructor
	~Student();   //Destructor
	void setData(
		int new_studentId,
		int new_entryYear,
		std::string new_firstName,
		std::string new_middleName,
		std::string new_lastName,
		double new_GPA, //Grade Point Average
		char new_gender);
	static int add(int, int);
	void print();
	int getId();
	int getEntryYer();
	std::vector<std::string> getStudent();
	std::string getFirstName();
	std::string getMiddleName();
	std::string getLastName();
	std::string getFullName();
	double getGPA();	
	char getGender();
	//   operator
	Student& operator ++();
};
 
// This is the end of the header guard
#endif