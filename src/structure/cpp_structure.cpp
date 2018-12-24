#include <iostream>
#include <string>
#include <iomanip>
#include <future>
#include <chrono>

using namespace std;

const float PI = 3.14;
const int WEEK_DAYS_COUNT = 7;
const string WEEK[WEEK_DAYS_COUNT] = {
	"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
};
const int YEAR_MONTHS_COUNT = 12;
const string YEAR[YEAR_MONTHS_COUNT] = {
	"January", "February", "March",
	"April", "May", "June",
	"July", "August", "September",
	"October", "November", "December"
};
int n_variable = 12; //global n

std::string fetchDataFromCSV(std::string recvdData)
{
	std::this_thread::sleep_for(std::chrono::seconds(7));
	return "CSV_" + recvdData;
}

std::string fetchDataFromDB(std::string recvdData)
{
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return "DB_" + recvdData;
}

std::string fetchDataFromFile(std::string recvdData)
{
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return "File_" + recvdData;
}

int main_cpp(int argc, char const *argv[])
{

	system("@cls || clear");

	//--------------------------- Data Type---------------------------------//
	int n_variable = 3;  //local n
	cout<<"global n is: "<<::n_variable<<"\n";  //global n_variable
	cout<<"local n is: "<<n_variable<<endl; //local n_variable
	//-----------------------------------------------------------------------//


	//--------------------------- Data Type---------------------------------//
	char c1;
	char16_t c2;
	char32_t c3;
	wchar_t c4;

	short i1 = -12;  //signed short int
	int i2 = 14;	//signed int
	long i3 = 34567;     //signed long int
	long long i4 = 8887;   //signed long long int

	unsigned short b1; //unsigned short int
	unsigned b2; //unsigned int
	unsigned long b3; //unsigned long int
	unsigned long long b4; //unsigned long long int

	float f;
	double d;
	long double ld;

	bool B;
	decltype(nullptr) np;

	int foo = 100;
	//auto bar = foo;  //warning???
	decltype(foo) sds = 210;

	typedef long int *pint32;
	pint32 x, y, z;

	cout<<"size of char is: "<<sizeof(char)<<endl;
	cout<<"size of short is: "<<sizeof(short)<<endl;
	cout<<"size of int is: "<<sizeof(int)<<endl;
	cout<<"size of long is: "<<sizeof(long)<<endl;
	cout<<"size of long long is: "<<sizeof(long long)<<endl;
	cout<<"size of float is: "<<sizeof(float)<<endl;
	cout<<"size of dlouble is: "<<sizeof(double)<<endl;
	cout<<"size of long double is: "<<sizeof(long double)<<endl;

	char cha = 't';
	cout <<int(cha)<<endl;

	int ax;
  long int bx;
  char cx;
  float fx;
  double dx;
  std::cin>>ax>>bx>>cx>>fx>>dx;
  std::cout<<ax<<"\n";
  std::cout<<bx<<"\n";
  std::cout<<cx<<"\n";
  std::cout<<std::fixed<<std::setprecision(3)<<fx<<"\n";
  std::cout<<std::fixed<<std::setprecision(9)<<dx;
	//-----------------------------------------------------------------------//

	//-----------------------------  cin, cout ------------------------------//
	double myDouble = 4456754562.0;
	cout<<fixed<<setw(11)<<setprecision(6)<<setfill('0')<<myDouble<<"\n";
	//-----------------------------------------------------------------------//


	//-----------------------------  string ----------------------------------//
	char name[] = "hello";
	string str;
	str = "this is my string";
	cout<<str.size()<<" "<<str<<endl;
	str.pop_back();
	cout<<str.size()<<" "<<str<<endl;
	str.pop_back();
	cout<<str.size()<<" "<<str<<endl;
	str.clear();

	if(str.empty())
	{
		cout<<"str is empty"<<endl;
	}
	cout<<str.size()<<" "<<str<<endl;

	for (int i = 0; i < WEEK_DAYS_COUNT; ++i)
	{
		cout<<WEEK[i]<<"\n";
	}
	string line(134, '.');
	cout<<line<<endl;

	/* ---The string Class Input Methods
	The string class has two input methods: stream extraction operator (>>) and getline()*/

	//cin
	string strName;
	cin>>strName;   // only get string befor WHITESPACE
	cin.ignore();
	cout<<strName<<"\n";

	//string::getline()
	string strFullName;
	getline(cin, strFullName);
	cout<<strFullName<<endl;
	//-----------------------------------------------------------------------//

	//-------------------------  std::stoi  ----------------------------------//
	std::string strInt("123");
	int n1 = std::stoi(strInt);
	int n2 = 123;
	std::string strInt2 = std::to_string(n2);
	char ch = 'B';
	std::string s5 = std::string(1, ch);
	//-----------------------------------------------------------------------//

	//-------------------------   date/time  ----------------------------------//

	// current date/time based on current system
	time_t now = time(0);

	// convert now to string form
	char* dt = ctime(&now);

	// convert now to string form
	std::string strdt = ctime(&now);

	std::cout<< "(now)[time_t now = time(0);]: "<< now <<std::endl;
	std::cout<< "(dt)[char* dt = ctime(&now);]: "<< dt <<std::endl;
	std::cout<< "(strdt)[std::string strdt = ctime(&now);]: "<< strdt <<std::endl;
	//-----------------------------------------------------------------------//

	//-------------------------   typedef / enum -------------------------------//
	typedef int feet;
	feet a = 100;
	std::cout<<a<<"\n";

	enum colors {blue, red, green};
	colors c;
	c = red;
	std::cout<<c<<"\n";
	//-----------------------------------------------------------------------//

	//-------------------------   random numbers -------------------------------//
	/* generate 10  random numbers. */
	// set the seed
	srand( (unsigned)time( NULL ) );
	int i, j;
	for(i = 0; i < 10; i++ ) {
		// generate actual random number
		j = rand();
		std::cout <<" Random Number : " << j << std::endl;
	}
	//-------------------------------------------------------------------------//

	//-------------------------   Async Programming   --------------------------//
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	std::future<std::string> resultFromCSV = std::async(std::launch::async, fetchDataFromCSV, "Data");
	std::future<std::string> resultFromDB = std::async(std::launch::async, fetchDataFromDB, "Data");
	std::string fileData = fetchDataFromFile("Data");
	std::string dbData = resultFromDB.get();
	std::string csvData = resultFromCSV.get();
	auto end = std::chrono::system_clock::now();
	auto diff = std::chrono::duration_cast < std::chrono::seconds > (end - start).count();
	std::cout << "Total Time Taken = " << diff << " Seconds" << std::endl;
	std::string data = dbData + " :: " + fileData + " :: " + csvData;
	std::cout << "Data = " << data << std::endl;
	//-------------------------------------------------------------------------//


	return 0;
}
