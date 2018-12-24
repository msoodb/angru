#ifndef ANGRU_PRODUCT_CONTROLLER_H_
#define ANGRU_PRODUCT_CONTROLLER_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/description.h>
#include <pistache/router.h>
#include <pistache/serializer/rapidjson.h>

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

#endif // ANGRU_PRODUCT_CONTROLLER_H_
