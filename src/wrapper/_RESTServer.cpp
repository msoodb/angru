#include <iostream>
#include <string>

#include "_RESTServer.h"
#include "_error.h"

#include "productController.h"


REST_Server::REST_Server(Pistache::Address addr) : httpEndpoint(std::make_shared<Pistache::Http::Endpoint>(addr))
  , desc("angru RESTful API", "0.1"){
}

void REST_Server::setupRoutes() {
    Pistache::Rest::Routes::Get(router, "/products", Pistache::Rest::Routes::bind(&ProductController::doGetProducts));
    Pistache::Rest::Routes::Get(router, "/products/:id", Pistache::Rest::Routes::bind(&ProductController::doGetProduct));
    Pistache::Rest::Routes::Delete(router, "/products/:id", Pistache::Rest::Routes::bind(&ProductController::doDeleteProduct));
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
