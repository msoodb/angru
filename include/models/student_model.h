#ifndef ANGRU_STUDENT_MODEL_H_
#define ANGRU_STUDENT_MODEL_H_

#include <iostream>
#include <vector>

namespace angru{
namespace mvc{
namespace model{

class StudentModel
{
public:
	StudentModel();
	StudentModel(
		int student_id,
		int entry_year,
		std::string first_name,
		std::string middle_name,
		std::string last_name,
		double grade_point_avarage,
		char gender);
	StudentModel (const StudentModel&);
	~StudentModel();
	void SetData(
		int student_id,
		int entry_year,
		std::string first_name,
		std::string middle_name,
		std::string last_name,
		double grade_point_avarage,
		char gender);
	static int add(int, int);
	void Print();
	int getId();
	int getEntryYer();
	std::vector<std::string> GetStudent();
	std::string getfirst_name();
	std::string getmiddle_name();
	std::string getlast_name();
	std::string getFullName();
	double getGPA();
	char getGender();
	StudentModel& operator ++();
protected:
private:
	int student_id_;
	int entry_year_;
	std::string first_name_;
	std::string middle_name_;
	std::string last_name_;
	double grade_point_avarage_;
	char gender_;
};

} // model
} // mvc
} // angru

#endif // ANGRU_STUDENT_MODEL_H_
