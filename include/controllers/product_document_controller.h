#ifndef ANGRU_PRODUCT_DOCUMENT_CONTROLLER_H_
#define ANGRU_PRODUCT_DOCUMENT_CONTROLLER_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/description.h>
#include <pistache/router.h>
#include <pistache/serializer/rapidjson.h>

namespace angru{
namespace mvc{
namespace controller{

class ProductDocumentController
{
public:
	ProductDocumentController();
	~ProductDocumentController();
	static void doGetProductDocuments(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void doGetProductDocument(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void doDeleteProductDocument(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void doAddProductDocument(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void doUpdateProductDocument(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // controller
} // mvc
} // angru

#endif // ANGRU_PRODUCT_DOCUMENT_CONTROLLER_H_
