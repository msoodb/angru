#include <iostream>
#include <vector>
#include <algorithm>
#include <pthread.h>
#include <future>
#include <chrono>
#include <thread>


int add1(int x, int y){
  int count = 12;
  for (size_t i = 0; i < count; i++) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return x + y;
}
int add2(int x, int y){
  int count = 7;
  for (size_t i = 0; i < count; i++) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return x + y;
}
int add3(int x, int y){
  int count = 5;
  for (size_t i = 0; i < count; i++) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return x + y;
}

void test_async(){
		//------------ Sync programming
		//int s1 = _math::add1(8, 12);
		//std::cout << "s1 is : "<< s1 << '\n';

		//int s2 = _math::add2(18, 4);
		//std::cout << "s2 is : "<< s2 << '\n';
		//------------------------------------------------------------------

		//------------ Async programming
		//std::future<int> fu1 = std::async(_math::add1, 12, 10);
		//std::cout << "Calculating sum 12,10 in add1 method...."<< '\n';

		//int s2 = _math::add2(8, 3);
		//std::cout << "s2 is : "<< s2 << '\n';

		//int s1 = fu1.get();
		//std::cout << "s1 is : "<< s1 << '\n';

		std::vector<std::future<int>> futures;
		int sum;
		for (size_t i = 0; i < 5; i++) {
			//sum = _math::add1(13,12);
			futures.push_back(std::async(add1, 13,12));
			//std::cout << "sum is: " << sum <<'\n';
		}
		for(auto& f : futures){
			sum = f.get();
			std::cout << "sum is :" << sum << '\n';
		}
		//------------------------------------------------------------------
}
