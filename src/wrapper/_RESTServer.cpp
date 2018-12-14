#include <iostream>
#include <string>

#include "_RESTServer.h"
#include "_error.h"


REST_Server::REST_Server(Pistache::Address addr) : httpEndpoint(std::make_shared<Pistache::Http::Endpoint>(addr))
  , desc("angru RESTful API", "0.1"){
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

void REST_Server::setupRoutes() {
    Pistache::Rest::Routes::Post(router, "/record/:name/:value?", Pistache::Rest::Routes::bind(&REST_Server::doRecordMetric, this));
    Pistache::Rest::Routes::Get(router, "/value/:name", Pistache::Rest::Routes::bind(&REST_Server::doGetMetric, this));
    Pistache::Rest::Routes::Get(router, "/ready", Pistache::Rest::Routes::bind(&REST_Server::handleReady, this));
    Pistache::Rest::Routes::Get(router, "/auth", Pistache::Rest::Routes::bind(&REST_Server::doAuth, this));
}

void REST_Server::doRecordMetric(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    auto name = request.param(":name").as<std::string>();

    Guard guard(metricsLock);
    auto it = std::find_if(metrics.begin(), metrics.end(), [&](const Metric& metric) {
        return metric.name() == name;
    });

    int val = 1;
    if (request.hasParam(":value")) {
        auto value = request.param(":value");
        val = value.as<int>();
    }

    if (it == std::end(metrics)) {
        metrics.push_back(Metric(std::move(name), val));
        response.send(Pistache::Http::Code::Created, std::to_string(val));
    }
    else {
        auto &metric = *it;
        metric.incr(val);
        response.send(Pistache::Http::Code::Ok, std::to_string(metric.value()));
    }
}

void REST_Server::doGetMetric(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    auto name = request.param(":name").as<std::string>();

    Guard guard(metricsLock);
    auto it = std::find_if(metrics.begin(), metrics.end(), [&](const Metric& metric) {
        return metric.name() == name;
    });

    if (it == std::end(metrics)) {
        response.send(Pistache::Http::Code::Not_Found, "Metric does not exist");
    } else {
        const auto& metric = *it;
        response.send(Pistache::Http::Code::Ok, std::to_string(metric.value()));
    }
}

void REST_Server::doAuth(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    printCookies(request);
    response.cookies()
        .add(Pistache::Http::Cookie("lang", "en-US"));
    response.send(Pistache::Http::Code::Ok);
}
