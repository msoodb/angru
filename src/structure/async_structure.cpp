#include <iostream>
#include <vector>
#include <algorithm>
#include <pthread.h>
#include <future>
#include <chrono>
#include <thread>

#include "async_structure.h"

int Async_Structure::add1(int x, int y){
  int count = 12;
  for (size_t i = 0; i < count; i++) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return x + y;
}
int Async_Structure::add2(int x, int y){
  int count = 7;
  for (size_t i = 0; i < count; i++) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return x + y;
}
int Async_Structure::add3(int x, int y){
  int count = 5;
  for (size_t i = 0; i < count; i++) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return x + y;
}

void Async_Structure::test_async(){
		//------------ Sync programming
		//int s1 = _math::add1(8, 12);
		//std::cout << "s1 is : "<< s1 << '\n';

		//int s2 = _math::add2(18, 4);
		//std::cout << "s2 is : "<< s2 << '\n';
		//------------------------------------------------------------------

		//------------ Async programming
    std::future<int> fu1 = std::async(add1, 14, 16);
		std::cout << "Calculating sum 12,10 in add1 method...."<< '\n';

		int s2 = add2(8, 3);
		std::cout << "s2 is : "<< s2 << '\n';

		int s1 = fu1.get();
    std::cout << "roozbeh" << '\n';
    std::cout << "s1 is : "<< s1 << '\n';

    std::packaged_task<int(int,int)> pktask(add1);
    std::future<int> f = pktask.get_future();
    std::thread thr(std::move(pktask),12,10);
    thr.join();
    int msum = f.get();
    std::cout << "sum is:" << msum <<'\n';

		/*std::vector<std::future<int>> futures;
		int sum;
		for (size_t i = 0; i < 5; i++) {
			futures.push_back(std::async(add1, 13,12));
		}
		for(auto& f : futures){
			sum = f.get();
			std::cout << "sum is :" << sum << '\n';
		}*/
		//------------------------------------------------------------------
}
