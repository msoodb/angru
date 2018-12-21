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
#include "productModel.h"
#include "_authorization.h"


ProductController::ProductController(){}
ProductController::~ProductController(){}
void ProductController::doGetProducts(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    _Authorization::AuthorizationCheck(request,response);
    int page = 1;
    auto query = request.query();
    if(query.has("page")) {
      auto value = query.get("page").get();
      page = std::stoi(value);
    }
    boost::property_tree::ptree product_ = ProductModel::getProducts_json(page);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, product_);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
        response.send(Pistache::Http::Code::Not_Found, "Products does not exist");
    } else {
        response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}
void ProductController::doGetProduct(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    _Authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    boost::property_tree::ptree product_ = ProductModel::getProduct_json(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, product_);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
        response.send(Pistache::Http::Code::Not_Found, "Product does not exist");
    } else {
        response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}
void ProductController::doDeleteProduct(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    _Authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    ProductModel::deleteProduct(id);
    response.send(Pistache::Http::Code::Ok, "Product delet.");
}
void ProductController::doAddProduct(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    _Authorization::AuthorizationCheck(request,response);
    _Authorization::ContentTypeJSONCheck(request,response);
    auto body = request.body();
    std::string title;
    float price;
    std::string created_at;
    std::string tags = "{gun}";
    try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      title = pt.get<std::string>("title");
      price = pt.get<float>("price");
      created_at = pt.get<std::string>("created_at");
      tags = pt.get<std::string>("tags");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Product not found");
    }
    ProductModel::addProduct(title,price,created_at,tags);
    response.send(Pistache::Http::Code::Ok, "Product added.");
}
