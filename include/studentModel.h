#ifndef ANGRU_STUDENT_MODEL_H_
#define ANGRU_STUDENT_MODEL_H_

#include <iostream>
#include <vector>

class StudentModel
{
	int student_id;
	int entry_year;
	std::string first_name;
	std::string middle_name;
	std::string last_name;
	double GPA; //Grade Point Average
	char gender;
public:
	static int zx;
	StudentModel();  //Simple Constructor
	StudentModel(
		int student_id_,
		int entry_year_,
		std::string first_name_,
		std::string middle_name_,
		std::string last_name_,
		double GPA_, //Grade Point Average
		char gender_);
	StudentModel (const StudentModel&); //Copy Constructor
	~StudentModel();   //Destructor
	void setData(
		int student_id_,
		int entry_year_,
		std::string first_name_,
		std::string middle_name_,
		std::string last_name_,
		double GPA_, //Grade Point Average
		char gender_);
	static int add(int, int);
	void print();
	int getId();
	int getEntryYer();
	std::vector<std::string> getStudent();
	std::string getfirst_name();
	std::string getmiddle_name();
	std::string getlast_name();
	std::string getFullName();
	double getGPA();
	char getGender();
	//   operator
	StudentModel& operator ++();
};

#endif
