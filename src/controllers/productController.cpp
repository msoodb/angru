#include "productController.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "_error.h"
#include "_log.h"
#include "_PostgreSQL.h"
#include "_authorization.h"
#include "productModel.h"


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
        response.send(Pistache::Http::Code::Not_Found, "Products not found.");
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
        response.send(Pistache::Http::Code::Not_Found, "Products not found.");
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
    std::string tags;
    try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      title = pt.get<std::string>("title");
      price = pt.get<float>("price");
      tags = pt.get<std::string>("tags");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Products not found.");
    }
    ProductModel::addProduct(title,price,tags);
    response.send(Pistache::Http::Code::Ok, "Product added.");
}
void ProductController::doUpdateProduct(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    _Authorization::AuthorizationCheck(request,response);
    _Authorization::ContentTypeJSONCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    if(id==-1){
        response.send(Pistache::Http::Code::Not_Found, "Products not found.");
    }
    auto body = request.body();
    std::string title;
    float price;
    std::string tags;
    try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      title = pt.get<std::string>("title");
      price = pt.get<float>("price");
      tags = pt.get<std::string>("tags");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Products not found.");
    }
    ProductModel::updateProduct(id,title,price,tags);
    response.send(Pistache::Http::Code::Ok, "Products updated.");
}
