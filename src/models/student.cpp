#include <iostream>
#include <string>
#include <vector>
#include "student.h"

Student::Student(int student_id_,	int entry_year_, std::string first_name_,
	std::string middle_name_, std::string last_name_, double GPA_, char gender_) :
	student_id(student_id_), entry_year(entry_year_), first_name(first_name_),
			middle_name(middle_name_),	last_name (last_name_), GPA (GPA_), gender (gender_){
}
Student::Student() : Student(0,2000,"","","",15.0,'M'){
}
Student::Student(const Student &obj) : Student(obj.student_id, obj.entry_year,
	obj.first_name, obj.middle_name, obj.last_name, obj.GPA, obj.gender){
}
Student::~Student(){
}
void Student::setData(
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
void Student::print()
{
	std::cout<<" "<<student_id<<" "<<entry_year<<" "
		<<first_name<<" "<<middle_name<<" "<<last_name<<" "<<gender<<" "<<GPA<<"\n";
}
std::vector<std::string> Student::getStudent()
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

int Student::getId()
{
	return student_id;
}
int Student::getEntryYer()
{
	return entry_year;
}
std::string Student::getfirst_name()
{
	return first_name;
}
std::string Student::getmiddle_name()
{
	return middle_name;
}
std::string Student::getlast_name()
{
	return last_name;
}
std::string Student::getFullName()
{
	return first_name + " " + middle_name + " " + last_name;
}
double Student::getGPA()
{
	return GPA;
}
char Student::getGender()
{
	return gender;
}
int Student::add(int a, int b)
{
	return a+b;
}
//      Operator
Student& Student::operator ++()
{
	this->entry_year++;
	return *this;
}
