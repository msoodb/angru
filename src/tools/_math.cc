#include "tools/_math.h"

#include <iostream>
#include <chrono>
#include <cmath>
#include <future>

namespace angru{
namespace tools{
namespace math{

int add1(int x, int y)
{
  int count = 12;
  for (size_t i = 0; i < count; i++) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return x + y;
}
int add2(int x, int y)
{
  int count = 7;
  for (size_t i = 0; i < count; i++) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return x + y;
}
int add3(int x, int y)
{
  int count = 5;
  for (size_t i = 0; i < count; i++) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return x + y;
}

bool checkPrimeNumber(int n)
{
	bool flag = true;
	for (int i = 2; i <= n/2; ++i){
		if(n%i == 0){
			flag = false;
			break;
		}
	}
	return flag;
}
void goldbachConjecture(int n)
{
	for (int i = 1; i < n/2; ++i)
	{
		if(checkPrimeNumber(i))
			if(checkPrimeNumber(n-i))
				std::cout<<n<< " = "<<i<<" + "<<n-i<<"\n";
	}
}
int sumN(int n)  //Recursion
{
	if (n==0)	{
		return 0;
	}
	return n+sumN(n-1);
}
int convertBinaryToDecimal(long long n)
{
	int decimalNumber=0;
	int reminder=0;
	int i=0;
	while (n!=0)
	{
		reminder = n%10;
		n /= 10;
		decimalNumber += reminder * pow(2, i);
		++i;
	}
	return decimalNumber;
}
long fibonacci(unsigned n)
{
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}
long long  factoriel(int n)
{
    if (n < 2) return n;
    return n * factoriel(n-1);
}
template <typename T>
T minimum (T a, T b)
{
	return a<b ? a : b;
}
template int minimum(int,int);
template double minimum(double,double);

} // namespace authorization
} // namespace tools
} // namespace angru
