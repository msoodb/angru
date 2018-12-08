// This is start of the header guard. TEST_CLASS_H can be any unique name.  By convention, we use the name of the header file.
#ifndef TEST_CLASS_H
#define TEST_CLASS_H

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
#endif