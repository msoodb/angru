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


ProductController::ProductController(){}
ProductController::~ProductController(){}
void ProductController::doGetProducts(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
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
    auto query = request.query();
    int id;
    std::string title;
    float price;
    std::string created_at;
    std::string deleted_at;
    std::string tags = "{gun, handgun, pistol}";
    if(query.has("id")) {
      auto value = query.get("id").get();
      id = std::stoi(value);
    }
    if(query.has("title")) {
      auto value = query.get("title").get();
      title = value;
    }
    if(query.has("price")) {
      auto value = query.get("price").get();
      price = std::stof(value);
    }
    if(query.has("created_at")) {
      auto value = query.get("created_at").get();
      created_at = value;
    }
    if(query.has("deleted_at")) {
      auto value = query.get("deleted_at").get();
      deleted_at = value;
    }
    if(query.has("tags")) {
      auto value = query.get("tags").get();
      tags = value;
    }
    ProductModel::addProduct(id,title,price,created_at,deleted_at,tags);
    response.send(Pistache::Http::Code::Ok, "Product added.");
}
