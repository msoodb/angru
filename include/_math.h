// This is start of the header guard.  INC_MATH_H can be any unique name.  By convention, we use the name of the header file.
#ifndef INC_MATH_H
#define INC_MATH_H

// This is the content of the .h file, which is where the declarations go
class _math
{
public:
	static int add1(int, int); // function prototype for add.h -- don't forget the semicolon!
	static int add2(int, int); // function prototype for add.h -- don't forget the semicolon!
	static int add3(int, int); // function prototype for add.h -- don't forget the semicolon!
	static bool checkPrimeNumber(int);
	static void goldbachConjecture(int);
	static int sumN(int);
	static int convertBinaryToDecimal(long long);
  static long fibonacci(unsigned);
	static long long  factoriel(int);
};
// This is the end of the header guard
#endif
