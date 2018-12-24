#ifndef ANGRU_BOOST_STRUCTURE_H_
#define ANGRU_BOOST_STRUCTURE_H_

class Boost_Structure
{
public:
	Boost_Structure();  //Simple Constructor

	//----------------------------------  Useful Macros
	static void testMacroA();
	static void testMacroB();
	static void testMacroC();
	static void testMacroD();
	//----------------------------------

	//---------------------------------- Boost Shared Pointer
	static void testRawPointer();
	static void testSharedPointer();
	//----------------------------------


	//---------------------------------- Distribution Functions
	static void distributionFunc1();
	static void distributionFunc2();
	//----------------------------------

	//---------------------------------- Random Numbers
	static void randomFunc1();
	static void randomFunc2();
	static void randomFunc3();
	static void randomFunc4();
	//----------------------------------

	//---------------------------------- Function
	//----------------------------------

	//---------------------------------- Bind
	//----------------------------------

	//---------------------------------- The Any Class
	//----------------------------------

	//---------------------------------- Optional
	//----------------------------------

	//---------------------------------- Serialization
	//----------------------------------

	//---------------------------------- Filesystem
	//----------------------------------

	//----------------------------------  Matrix operations with uBLAS
	//----------------------------------

};

#endif // ANGRU_BOOST_STRUCTURE_H_
