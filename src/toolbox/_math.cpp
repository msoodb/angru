#include "_math.h"

#include <iostream>
#include <chrono>
#include <cmath>
#include <future>

int _math::add1(int x, int y)
{
  int count = 12;
  for (size_t i = 0; i < count; i++) {
    //std::cout << "add1...";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //std::cout << '\n';
  }
  //std::cout << '\n';
  return x + y;
}
int _math::add2(int x, int y)
{
  int count = 7;
  for (size_t i = 0; i < count; i++) {
    //std::cout << "add2...";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //std::cout << '\n';
  }
  //std::cout << '\n';
  return x + y;
}
int _math::add3(int x, int y)
{
  int count = 5;
  for (size_t i = 0; i < count; i++) {
    //std::cout << "add3...";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //std::cout << '\n';
  }
  //std::cout << '\n';
  return x + y;
}

bool _math::checkPrimeNumber(int n)
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
void _math::goldbachConjecture(int n)
{
	for (int i = 1; i < n/2; ++i)
	{
		if(checkPrimeNumber(i))
			if(checkPrimeNumber(n-i))
				std::cout<<n<< " = "<<i<<" + "<<n-i<<"\n";
	}
}
int _math::sumN(int n)  //Recursion
{
	if (n==0)	{
		return 0;
	}
	return n+sumN(n-1);
}
int _math::convertBinaryToDecimal(long long n)
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
long _math::fibonacci(unsigned n)
{
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}
long long  _math::factoriel(int n)
{
    if (n < 2) return n;
    return n * factoriel(n-1);
}
template <typename T>
T _math::minimum (T a, T b)
{
	return a<b ? a : b;
}
template int _math::minimum(int,int);
template double _math::minimum(double,double);
