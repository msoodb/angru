#include <iostream>
#include <vector>
#include <algorithm>

#include "_error.h"
#include "_log.h"

int main(int argc, char const *argv[])
{
	std::cout<<"Angru version .010. Check Logfile."<<std::endl;

	//int n[10000001];
	/*for (size_t i = 0; i < 10000001; i++) {
		std::cout << i<< " : hello" << '\n';
	}*/
	//return 0;
	std::cout << argc << '\n';
	int count = argv.size();
	for (size_t i = 0; i < count; i++) {
		std::cout << argv[i] << '\n';
	}
	/*try
	{
    int count = 10;
    int r;
    srand(unsigned(time(0)));
    std::vector<int> v;
    for (size_t i = 0; i < count; i++) {
      r = rand()%10;
      v.push_back(r);
    }
    std::vector<int>::iterator itr;
    itr = v.begin();
    std::cout << '\n';
    std::cout << "----------------------------------------" << '\n';
    while (itr != v.end()) {
      std::cout << *itr << '\t';
      itr++;
    }
    std::cout << '\n';
    std::cout << "----------------------------------------" << '\n';
    std::sort(v.begin(), v.end());
    itr = v.begin();
    while (itr != v.end()) {
      std::cout << *itr << '\t';
      itr++;
    }
    std::cout << '\n';
    std::cout << "------------------------------------------" << '\n';
    itr = v.begin();
    v.pop_back();
    v.pop_back();
    while (itr != v.end()) {
      std::cout << *itr << '\t';
      itr++;
    }
    //std::cout << RAND_MAX << '\n';
    std::cout << std::endl;
	}
	catch(const _error& e)
	{
    LOG_ERROR << e.what();
		return 1;
	}
	catch(...)
	{
    LOG_ERROR << "Error: unknown exception";
		return 2;
	}*/
	return 0;
}
