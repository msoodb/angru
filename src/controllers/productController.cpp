#include <iostream>
#include <string>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>


#include "_error.h"
#include "_log.h"
#include "_PostgreSQL.h"

#include "productController.h"
#include "product.h"


ProductController::ProductController(){}
ProductController::~ProductController(){}
void ProductController::doGetProduct(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }

    boost::property_tree::ptree product_ = Product::getProduct_json(id);
    std::ostringstream oss;
    boost::property_tree::ini_parser::write_ini(oss, product_);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
        response.send(Pistache::Http::Code::Not_Found, "Product does not exist");
    } else {
        response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}
