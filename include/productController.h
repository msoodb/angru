// This is start of the header guard. PRODUCT_CONTROLLER_H can be any unique name.  By convention, we use the name of the header file.
#ifndef PRODUCT_CONTROLLER_H
#define PRODUCT_CONTROLLER_H

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/description.h>
#include <pistache/router.h>
#include <pistache/serializer/rapidjson.h>

// This is the content of the .h file, which is where the declarations go
class ProductController
{
public:
	ProductController();
	~ProductController();
	static void doGetProducts(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void doGetProduct(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void doDeleteProduct(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void doAddProduct(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void doUpdateProduct(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

// This is the end of the header guard
#endif
