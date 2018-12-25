#include "models/student_model.h"

#include <iostream>
#include <string>
#include <vector>

namespace angru{
namespace mvc{
namespace model{

StudentModel::StudentModel(int student_id,	int entry_year, std::string first_name,
	std::string middle_name, std::string last_name, double grade_point_avarage, char gender) :
	student_id_(student_id), entry_year_(entry_year), first_name_(first_name),
			middle_name_(middle_name),	last_name_(last_name),
			grade_point_avarage_(grade_point_avarage), gender_(gender){
}
StudentModel::StudentModel() : StudentModel(0,2000,"","","",15.0,'M'){
}
StudentModel::StudentModel(const StudentModel &obj) : StudentModel(obj.student_id_, obj.entry_year_,
	obj.first_name_, obj.middle_name_, obj.last_name_, obj.grade_point_avarage_, obj.gender_){
}
StudentModel::~StudentModel(){
}
void StudentModel::SetData(
	int student_id,
	int entry_year,
	std::string first_name,
	std::string middle_name,
	std::string last_name,
	double grade_point_avarage,
	char gender)
{
	student_id_ = student_id;
	entry_year_ = entry_year;
	first_name_ = first_name;
	middle_name_ = middle_name;
	last_name_ = last_name;
	grade_point_avarage_ = grade_point_avarage;
	gender_ = gender;
}
void StudentModel::Print()
{
	std::cout<<" "<<student_id_<<" "<<entry_year_<<" "
		<<first_name_<<" "<<middle_name_<<" "<<last_name_<<" "<<gender_<<" "<<grade_point_avarage_<<"\n";
}
std::vector<std::string> StudentModel::GetStudent()
{
	std::vector<std::string> v;
	v.push_back(std::to_string(this->student_id_));
	v.push_back(std::to_string(this->entry_year_));
	v.push_back(this->first_name_);
	v.push_back(this->middle_name_);
	v.push_back(this->last_name_);
	v.push_back(std::to_string(this->grade_point_avarage_));
	v.push_back(std::string(1, this->gender_));
	return v;
}

int StudentModel::getId()
{
	return student_id_;
}
int StudentModel::getEntryYer()
{
	return entry_year_;
}
std::string StudentModel::getfirst_name()
{
	return first_name_;
}
std::string StudentModel::getmiddle_name()
{
	return middle_name_;
}
std::string StudentModel::getlast_name()
{
	return last_name_;
}
std::string StudentModel::getFullName()
{
	return first_name_ + " " + middle_name_ + " " + last_name_;
}
double StudentModel::getGPA()
{
	return grade_point_avarage_;
}
char StudentModel::getGender()
{
	return gender_;
}
int StudentModel::add(int a, int b)
{
	return a+b;
}
//      Operator
StudentModel& StudentModel::operator ++()
{
	this->entry_year_++;
	return *this;
}

} // model
} // mvc
} // angru
