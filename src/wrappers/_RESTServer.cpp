#include "wrappers/_RESTServer.h"

#include <iostream>
#include <string>

#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include "tools/_error.h"
#include "controllers/productController.h"
#include "controllers/userController.h"

void REST_Server::setup(int port_number, int thread_count){
  Pistache::Port port(port_number);
  Pistache::Address addr(Pistache::Ipv4::any(), port);
  std::cout << "Using " <<  std::thread::hardware_concurrency() << " Cores" << std::endl;
  std::cout << "Using " << port_number << " port number" << std::endl;
  std::cout << "Using " << thread_count << " threads" << std::endl;
  REST_Server rest_server(addr);
  rest_server.init(thread_count);
  rest_server.start();
  rest_server.shutdown();
}

REST_Server::REST_Server(Pistache::Address addr) : httpEndpoint(std::make_shared<Pistache::Http::Endpoint>(addr))
  , desc("angru RESTful API", "0.1"){
}

void REST_Server::setupRoutes() {
    Pistache::Rest::Routes::Post(router, "/login", Pistache::Rest::Routes::bind(&UserController::doLogin));
    //-----------------------------------------------------------------------------------------------------------
    Pistache::Rest::Routes::Get(router, "/products", Pistache::Rest::Routes::bind(&ProductController::doGetProducts));
    Pistache::Rest::Routes::Get(router, "/products/:id", Pistache::Rest::Routes::bind(&ProductController::doGetProduct));
    Pistache::Rest::Routes::Delete(router, "/products/:id", Pistache::Rest::Routes::bind(&ProductController::doDeleteProduct));
    Pistache::Rest::Routes::Post(router, "/products", Pistache::Rest::Routes::bind(&ProductController::doAddProduct));
    Pistache::Rest::Routes::Put(router, "/products/:id", Pistache::Rest::Routes::bind(&ProductController::doUpdateProduct));
    //-----------------------------------------------------------------------------------------------------------
    Pistache::Rest::Routes::Get(router, "/users", Pistache::Rest::Routes::bind(&UserController::doGetUsers));
    Pistache::Rest::Routes::Get(router, "/users/:id", Pistache::Rest::Routes::bind(&UserController::doGetUser));
    Pistache::Rest::Routes::Delete(router, "/users/:id", Pistache::Rest::Routes::bind(&UserController::doDeleteUser));
    Pistache::Rest::Routes::Post(router, "/users", Pistache::Rest::Routes::bind(&UserController::doAddUser));
    Pistache::Rest::Routes::Put(router, "/users/:id", Pistache::Rest::Routes::bind(&UserController::doUpdateUser));
}

void REST_Server::printCookies(const Pistache::Http::Request& req) {
    auto cookies = req.cookies();
    std::cout << "Cookies: [" << std::endl;
    const std::string indent(4, ' ');
    for (const auto& c: cookies) {
        std::cout << indent << c.name << " = " << c.value << std::endl;
    }
    std::cout << "]" << std::endl;
}

void REST_Server::handleReady(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter response) {
    response.send(Pistache::Http::Code::Ok, "1");
}

void REST_Server::init(size_t thr) {
    auto opts = Pistache::Http::Endpoint::options()
        .threads(thr)
        .flags(Pistache::Tcp::Options::InstallSignalHandler);
    httpEndpoint->init(opts);
    setupRoutes();
}

void REST_Server::start() {
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
}

void REST_Server::shutdown() {
    httpEndpoint->shutdown();
}
