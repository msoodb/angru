#include <iostream>
#include <string>
#include <vector>
#include "student.h"

Student::Student()
{
	studentId = 0;
	entryYear = 2000;
	firstName = "";
	middleName = "";
	lastName = "";
	GPA = 0.0; //Grade Point Average
	gender = 'M';
}
Student::~Student()
{

}
Student::Student(
		int new_studentId,
		int new_entryYear,
		std::string new_firstName,
		std::string new_middleName,
		std::string new_lastName,
		double new_GPA, //Grade Point Average
		char new_gender)
{
	studentId = new_studentId;
	entryYear = new_entryYear;
	firstName = new_firstName;
	middleName = new_middleName;
	lastName = new_lastName;
	GPA = new_GPA; //Grade Point Average
	gender = new_gender;
}
Student::Student(const Student &obj)
{
	studentId = obj.studentId;
	entryYear = obj.entryYear;
	firstName = obj.firstName;
	middleName = obj.middleName;
	lastName = obj.lastName;
	GPA = obj.GPA; //Grade Point Average
	gender = obj.gender;
}
void Student::setData(
		int new_studentId,
		int new_entryYear,
		std::string new_firstName,
		std::string new_middleName,
		std::string new_lastName,
		double new_GPA, //Grade Point Average
		char new_gender)
{
	studentId = new_studentId;
	entryYear = new_entryYear;
	firstName = new_firstName;
	middleName = new_middleName;
	lastName = new_lastName;
	GPA = new_GPA; //Grade Point Average
	gender = new_gender;
}
void Student::print()
{
	std::cout<<" "<<studentId<<" "<<entryYear<<" "
		<<firstName<<" "<<middleName<<" "<<lastName<<" "<<gender<<" "<<GPA<<"\n"; //Grade Point Average
}
std::vector<std::string> Student::getStudent()
{
	std::vector<std::string> v;
	v.push_back(std::to_string(this->studentId));
	v.push_back(std::to_string(this->entryYear));
	v.push_back(this->firstName);
	v.push_back(this->middleName);
	v.push_back(this->lastName);
	v.push_back(std::to_string(this->GPA));
	v.push_back(std::string(1, this->gender));
	return v;
}

int Student::getId()
{
	return studentId;
}
int Student::getEntryYer()
{
	return entryYear;
}
std::string Student::getFirstName()
{
	return firstName;
}
std::string Student::getMiddleName()
{
	return middleName;
}
std::string Student::getLastName()
{
	return lastName;
}
std::string Student::getFullName()
{
	return firstName + " " + middleName + " " + lastName;
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
	this->entryYear++;
	return *this;
}
