#include "structures/STL_structure.h"

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

int vectorSample()
{
	std::cout<<"STLstructure vectorSample method"<<std::endl;
	std::vector <int> vec;
	int i=0;
	std::cout<<"vec size is: "<<vec.size()<<std::endl;
	for (i = 0; i < 5; ++i)
	{
		vec.push_back(i+2);
	}
	vec.push_back(25);
	std::cout<<"vec size is: "<<vec.size()<<std::endl;

	for (int i = 0; i < vec.size(); ++i)
	{
		std::cout<<" vec["<<i<<"] is: "<<vec[i]<<"\n";
	}

	std::vector<int>::iterator v = vec.begin();
	while(v!=vec.end())
	{
		std::cout<<"Value of vec is: "<< *v<<std::endl;
		v++;
	}
	vec.resize(2);
	v = vec.begin();
	while(v!=vec.end())
	{
		std::cout<<"Value of vec is: "<< *v<<std::endl;
		v++;
	}
	vec.resize(12, 4);
	v = vec.begin();
	while(v!=vec.end())
	{
		std::cout<<"Value of vec is: "<< *v<<std::endl;
		v++;
	}

	return 0;
}
int dequeSample()
{
	std::cout<<"STLstructure dequeSample method"<<std::endl;
	std::deque<int> deq;
	deq = {5, 1, 7, 13};
	deq.push_back(9);
	deq.push_front(3);
	for (int i : deq)
	{
		std::cout<<i<<std::endl;
	}
	std::sort(deq.begin(), deq.end(), std::greater<int>());
	for(int i : deq)
	{
		std::cout<<i<< " ";
	}
	std::cout<<std::endl;

	std::deque<std::string> strdeq;
	std::string strtemp;
	char choise = 'y';
	while(choise == 'y' || choise == 'Y')
	{
		std::cout<<"Enter string: ";
		std::cin>>strtemp;
		strdeq.push_back(strtemp);
		std::cout<<"Continue? (y/n)";
		std::cin>>choise;
	}
	std::sort(strdeq.begin(), strdeq.end());
	for(std::string &s : strdeq)
	{
		std::cout<<s<<" ";
	}
	std::cout<<std::endl;
	return 0;
}
