#include "structures/boost_structure.h"

#include <iostream>
#include <vector>

#include <boost/current_function.hpp>
#include <boost/static_assert.hpp>
#include <boost/foreach.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/math/distributions.hpp>
#include <boost/random.hpp>
#include <boost/function.hpp>

//---------------------------------------------------------------------------------------------//
Boost_Structure::Boost_Structure()
{
}

void Boost_Structure::testMacroA()
{
	std::cout<<"You have called "<<BOOST_CURRENT_FUNCTION<<std::endl;
}
void Boost_Structure::testMacroB()
{
	BOOST_STATIC_ASSERT(2==2);
}
void Boost_Structure::testMacroC()
{
	std::vector<double> myVec(10);
	BOOST_FOREACH(double& d, myVec)
	{
		d = 10.0;
	}
	BOOST_FOREACH(double d, myVec)
	{
		std::cout<<"d: "<<d<<std::endl;
	}
}
void Boost_Structure::testMacroD()
{
	BOOST_ERROR ("failure to launch");
	double x = 0.0;
	BOOST_TEST(x=0);
}
//---------------------------------------------------------------------------------------------//
void Boost_Structure::testRawPointer()
{
	/*A* ptr_myA = new A(1.0);
	throw "Error Ocurred in Class A.";
	delete ptr_myA;   //ptr_myA wont be deleted.!!!*/
}
void Boost_Structure::testSharedPointer()
{
	//boost::shared_ptr<A> bptr_myA(new A(1.0));
	//std::cout<<bptr_myA->getValue()<<std::endl;
	//------------------------------------------------
	/*A* ptr_myA = new A(2.0);
	boost::shared_ptr<A> bptr_myA(ptr_myA);
	//std::cout<<bptr_myA->getValue()<<std::endl;
	bptr_myA.reset(new A(3.0));*/
}
//---------------------------------------------------------------------------------------------//
void Boost_Structure::distributionFunc1()
{

}
void Boost_Structure::distributionFunc2()
{

}
//---------------------------------------------------------------------------------------------//
void Boost_Structure::randomFunc1()
{

}
void Boost_Structure::randomFunc2()
{

}
void Boost_Structure::randomFunc3()
{

}
void Boost_Structure::randomFunc4()
{

}

//---------------------------------------------------------------------------------------------//
