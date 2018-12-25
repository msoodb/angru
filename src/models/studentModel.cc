#include "models/studentModel.h"

#include <iostream>
#include <string>
#include <vector>

StudentModel::StudentModel(int student_id_,	int entry_year_, std::string first_name_,
	std::string middle_name_, std::string last_name_, double GPA_, char gender_) :
	student_id(student_id_), entry_year(entry_year_), first_name(first_name_),
			middle_name(middle_name_),	last_name (last_name_), GPA (GPA_), gender (gender_){
}
StudentModel::StudentModel() : StudentModel(0,2000,"","","",15.0,'M'){
}
StudentModel::StudentModel(const StudentModel &obj) : StudentModel(obj.student_id, obj.entry_year,
	obj.first_name, obj.middle_name, obj.last_name, obj.GPA, obj.gender){
}
StudentModel::~StudentModel(){
}
void StudentModel::setData(
		int student_id_,
		int entry_year_,
		std::string first_name_,
		std::string middle_name_,
		std::string last_name_,
		double GPA_,
		char gender_)
{
	student_id = student_id_;
	entry_year = entry_year_;
	first_name = first_name_;
	middle_name = middle_name_;
	last_name = last_name_;
	GPA = GPA_;
	gender = gender_;
}
void StudentModel::print()
{
	std::cout<<" "<<student_id<<" "<<entry_year<<" "
		<<first_name<<" "<<middle_name<<" "<<last_name<<" "<<gender<<" "<<GPA<<"\n";
}
std::vector<std::string> StudentModel::getStudent()
{
	std::vector<std::string> v;
	v.push_back(std::to_string(this->student_id));
	v.push_back(std::to_string(this->entry_year));
	v.push_back(this->first_name);
	v.push_back(this->middle_name);
	v.push_back(this->last_name);
	v.push_back(std::to_string(this->GPA));
	v.push_back(std::string(1, this->gender));
	return v;
}

int StudentModel::getId()
{
	return student_id;
}
int StudentModel::getEntryYer()
{
	return entry_year;
}
std::string StudentModel::getfirst_name()
{
	return first_name;
}
std::string StudentModel::getmiddle_name()
{
	return middle_name;
}
std::string StudentModel::getlast_name()
{
	return last_name;
}
std::string StudentModel::getFullName()
{
	return first_name + " " + middle_name + " " + last_name;
}
double StudentModel::getGPA()
{
	return GPA;
}
char StudentModel::getGender()
{
	return gender;
}
int StudentModel::add(int a, int b)
{
	return a+b;
}
//      Operator
StudentModel& StudentModel::operator ++()
{
	this->entry_year++;
	return *this;
}
