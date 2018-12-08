// This is start of the header guard. PRODUCT_H can be any unique name.  By convention, we use the name of the header file.
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <vector>
#include <pqxx/pqxx>
//#include <boost/date_time/gregorian/gregorian.hpp>



// This is the content of the .h file, which is where the declarations go
class Product
{
public:
	Product();
	~Product();
	void setData();
	void print();
	static pqxx::result getProducts();
  static pqxx::result getProduct(int id);
	static void addProduct(int, std::string, float, std::string, std::string, std::string);
};

// This is the end of the header guard
#endif
