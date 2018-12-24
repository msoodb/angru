#ifndef ANGRU_TEST_CLASS_H_
#define ANGRU_TEST_CLASS_H_

#include <iostream>

class A
{
private:
	double myValue_;
public:
	A(const double& myValue): myValue_(myValue){
		std::cout<<"Constructor of A with value: "<<myValue_<<std::endl;
	}
	~A()
	{
		std::cout<<"Destructor A with value: "<<myValue_<<std::endl;
	}
	double getValue() const {return myValue_;}

};

#endif // ANGRU_TEST_CLASS_H_
