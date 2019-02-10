#include "wrappers/rest_server.h"

#include <iostream>
#include <string>

#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include "tools/system.h"
#include "tools/security.h"
#include "controllers/aggrigator_controller.h"
#include "controllers/content_provider_controller.h"
#include "controllers/file_controller.h"
#include "controllers/avatar_controller.h"
#include "controllers/product_controller.h"
#include "controllers/product_document_controller.h"
#include "controllers/user_controller.h"

namespace angru{
namespace wrapper{

void RestServer::Setup(int port_number, int thread_count){
  Pistache::Port port(port_number);
  Pistache::Address addr(Pistache::Ipv4::any(), port);
  std::cout << "Using " <<  std::thread::hardware_concurrency() <<
    " Cores" << std::endl;
  std::cout << "Using " << port_number << " port number" << std::endl;
  std::cout << "Using " << thread_count << " threads" << std::endl;
  RestServer rest_server(addr);
  rest_server.Init(thread_count);
  rest_server.Start();
  rest_server.Shutdown();
}


RestServer::RestServer(Pistache::Address addr) :
  httpEndpoint(std::make_shared<Pistache::Http::Endpoint>(addr)){
}

void RestServer::SetupRoutes() {
  using namespace angru::mvc::controller;
  using namespace Pistache::Rest::Routes;
  Options(router, "/*", bind(&angru::security::authorization::doGetOptions));
  Options(router, "/*/*", bind(&angru::security::authorization::doGetOptions));
  Options(router, "/:", bind(&angru::security::authorization::doGetOptions));
  Options(router, "/*/:", bind(&angru::security::authorization::doGetOptions));
  Options(router, "/*/:*", bind(&angru::security::authorization::doGetOptions));
  Options(router, "/*/:*/*", bind(&angru::security::authorization::doGetOptions));
  Options(router, "/*/:*/*/:*", bind(&angru::security::authorization::doGetOptions));

  Post(router, "/login", bind(&UserController::doLogin));

  Get(router, "/files/:id", bind(&FileController::doGetFile));
  Post(router, "/files", bind(&FileController::doAddFile));

  Get(router, "/aggrigators", bind(&AggrigatorController::doGetAggrigators));
  Get(router, "/aggrigators/:id", bind(&AggrigatorController::doGetAggrigator));
  Delete(router, "/aggrigators/:id", bind(&AggrigatorController::doDeleteAggrigator));
  Post(router, "/aggrigators", bind(&AggrigatorController::doAddAggrigator));
  Put(router, "/aggrigators/:id", bind(&AggrigatorController::doUpdateAggrigator));

  Get(router, "/content_providers", bind(&ContentProviderController::doGetContentProviders));
	Get(router, "/content_providers/:id", bind(&ContentProviderController::doGetContentProvider));
	Delete(router, "/content_providers/:id", bind(&ContentProviderController::doDeleteContentProvider));
  Post(router, "/content_providers", bind(&ContentProviderController::doAddContentProvider));
	Put(router, "/content_providers/:id", bind(&ContentProviderController::doUpdateContentProvider));

  Get(router, "/products", bind(&ProductController::doGetProducts));
  Get(router, "/products/:id", bind(&ProductController::doGetProduct));
  Delete(router, "/products/:id", bind(&ProductController::doDeleteProduct));
  Post(router, "/products", bind(&ProductController::doAddProduct));
  Put(router, "/products/:id", bind(&ProductController::doUpdateProduct));

  Get(router, "/products/:product_id/documents", bind(&ProductDocumentController::doGetProductDocuments));
  Get(router, "/products/:product_id/documents/:id", bind(&ProductDocumentController::doGetProductDocument));
  Delete(router, "/products/:product_id/documents/:id", bind(&ProductDocumentController::doDeleteProductDocument));
  Post(router, "/products/:product_id/documents", bind(&ProductDocumentController::doAddProductDocument));
  Put(router, "/products/:product_id/documents/:id", bind(&ProductDocumentController::doUpdateProductDocument));

  Get(router, "/users", bind(&UserController::doGetUsers));
  Get(router, "/users/:id", bind(&UserController::doGetUser));
  Delete(router, "/users/:id", bind(&UserController::doDeleteUser));
  Post(router, "/users", bind(&UserController::doAddUser));
  Put(router, "/users/:id", bind(&UserController::doUpdateUser));
  Put(router, "/users/:id/password", bind(&UserController::doChangePassword));
  Post(router, "/users/:id/avatars", bind(&AvatarController::doAddAvatar));

}

void RestServer::PrintCookies(const Pistache::Http::Request& req) {
    auto cookies = req.cookies();
    std::cout << "Cookies: [" << std::endl;
    const std::string indent(4, ' ');
    for (const auto& c: cookies) {
        std::cout << indent << c.name << " = " << c.value << std::endl;
    }
    std::cout << "]" << std::endl;
}

void RestServer::HandleReady(const Pistache::Rest::Request&,
  Pistache::Http::ResponseWriter response) {
    response.send(Pistache::Http::Code::Ok, "1");
}

void RestServer::Init(size_t thr) {
    auto opts = Pistache::Http::Endpoint::options()
        .threads(thr)
        .flags(Pistache::Tcp::Options::InstallSignalHandler);
    httpEndpoint->init(opts);
    SetupRoutes();
}

void RestServer::Start() {
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
}

void RestServer::Shutdown() {
    httpEndpoint->shutdown();
}

} // wrapper
} // angru
