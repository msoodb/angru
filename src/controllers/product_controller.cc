#include "controllers/product_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/product_model.h"

namespace angru{
namespace mvc{
namespace controller{

ProductController::ProductController(){}
ProductController::~ProductController(){}

void ProductController::doGetProducts(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    int page = 1;
    auto query = request.query();
    if(query.has("page")) {
      auto value = query.get("page").get();
      page = std::stoi(value);
    }
    boost::property_tree::ptree products = angru::mvc::model::ProductModel::GetProductsJson(page);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, products);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "Products not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void ProductController::doGetProduct(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    boost::property_tree::ptree product = angru::mvc::model::ProductModel::GetProductJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, product);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "Products not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void ProductController::doDeleteProduct(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    angru::mvc::model::ProductModel::DeleteProduct(id);
    response.send(Pistache::Http::Code::Ok, "Product deleted.");
}

void ProductController::doAddProduct(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    auto body = request.body();
    std::string	title;
    float	price;
    std::string	tags;
    bool	expirable;
    std::string	details;
    std::string	name;
    std::string	code;
    bool	active;
    bool	taxable;
    std::string	description;
    try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      title = pt.get<std::string>("title");
      price = pt.get<float>("price");
      tags = pt.get<std::string>("tags");
      expirable = pt.get<bool>("expirable");
      details = pt.get<std::string>("details");
      name = pt.get<std::string>("name");
      code = pt.get<std::string>("code");
      active = pt.get<bool>("active");
      taxable = pt.get<bool>("taxable");
      description = pt.get<std::string>("description");

      angru::mvc::model::ProductModel::AddProduct(
                                                  title,
                                                  price,
                                                  tags,
                                                  expirable,
                                                  details,
                                                  name,
                                                  code,
                                                  active,
                                                  taxable,
                                                  description );
      response.send(Pistache::Http::Code::Ok, "Product added.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Products not found.");
    }
}

void ProductController::doUpdateProduct(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
      id = value.as<int>();
    }
    if(id == -1){
      response.send(Pistache::Http::Code::Not_Found, "Products not found.");
    }
    auto body = request.body();
    std::string	title;
    float	price;
    std::string	tags;
    bool	expirable;
    std::string	details;
    std::string	name;
    std::string	code;
    bool	active;
    bool	taxable;
    std::string	description;
   try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      title = pt.get<std::string>("title");
      price = pt.get<float>("price");
      tags = pt.get<std::string>("tags");
      expirable = pt.get<bool>("expirable");
      details = pt.get<std::string>("details");
      name = pt.get<std::string>("name");
      code = pt.get<std::string>("code");
      active = pt.get<bool>("active");
      taxable = pt.get<bool>("taxable");
      description = pt.get<std::string>("description");
      angru::mvc::model::ProductModel::UpdateProduct(
                                                  id,
                                                  title,
                                                  price,
                                                  tags,
                                                  expirable,
                                                  details,
                                                  name,
                                                  code,
                                                  active,
                                                  taxable,
                                                  description );
      response.send(Pistache::Http::Code::Ok, "Products updated.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "Products not found.");
    }
 }

} // model
} // mvc
} // angru
