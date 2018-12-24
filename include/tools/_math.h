#ifndef ANGRU_MATH_H_
#define ANGRU_MATH_H_

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
	template<typename T>
	T minimum (T a, T b);
};

#endif // ANGRU_MATH_H_
