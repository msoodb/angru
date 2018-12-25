//-------------------------  Class, Object  ----------------------------------//
int new_studentId;
int new_entryYear;
std::string new_firstName;
std::string new_middleName;
std::string new_lastName;
double new_GPA; //Grade Point Average
char new_gender;

std::vector<Student> vecStudents;
char choise = 'y';
while(choise == 'y' || choise == 'Y')
{
  Student st;
  std::cout<<"Enter studentId: ";
  std::cin>>new_studentId;
  std::cout<<"Enter entryYear: ";
  std::cin>>new_entryYear;
  std::cout<<"Enter firstName: ";
  std::cin>>new_firstName;
  std::cout<<"Enter middleName: ";
  std::cin>>new_middleName;
  std::cout<<"Enter lastName: ";
  std::cin>>new_lastName;
  std::cout<<"Enter GPA: ";
  std::cin>>new_GPA;
  std::cout<<"Enter gender: ";
  std::cin>>new_gender;

  st.setData(
    new_studentId,
    new_entryYear,
    new_firstName,
    new_middleName,
    new_lastName,
    new_GPA, //Grade Point Average
    new_gender);
  vecStudents.push_back(st);
  std::cout<<"Continue? (y/n)";
  std::cin>>choise;
}
for(Student student : vecStudents)
{
  student.print();
}
//std::sort(vecStudents.begin(), vecStudents.end());
for(Student student : vecStudents)
{
  student.print();
}
std::cout<<std::endl;

CSVWriter writer("StudentW.csv");
for (Student s : vecStudents)
{
  std::vector<std::string> v = s.getStudent();
  writer.AddDataRow(v.begin(), v.end());
}
//-----------------------------------------------------------------------//
