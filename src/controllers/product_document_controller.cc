#include "controllers/product_document_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/product_document_model.h"
#include "models/privilege_model.h"


namespace angru{
namespace mvc{
namespace controller{

ProductDocumentController::ProductDocumentController(){}
ProductDocumentController::~ProductDocumentController(){}

void ProductDocumentController::doGetProductDocuments(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthenticationCheck(request,response);
    int page = 1;
    auto query = request.query();
    if(query.has("page")) {
      auto value = query.get("page").get();
      page = std::stoi(value);
    }
    boost::property_tree::ptree product_documents = angru::mvc::model::ProductDocumentModel::GetProductDocumentsJson(page);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, product_documents);

    std::string inifile_text = oss.str();
    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "ProductDocuments not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void ProductDocumentController::doGetProductDocument(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthenticationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    boost::property_tree::ptree product_document = angru::mvc::model::ProductDocumentModel::GetProductDocumentJson(id);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, product_document);

    std::string inifile_text = oss.str();

    if (inifile_text.empty()) {
      response.send(Pistache::Http::Code::Not_Found, "ProductDocuments not found.");
    } else {
      response.send(Pistache::Http::Code::Ok, inifile_text);
    }
}

void ProductDocumentController::doDeleteProductDocument(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthenticationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    angru::mvc::model::ProductDocumentModel::DeleteProductDocument(id);
    response.send(Pistache::Http::Code::Ok, "ProductDocument deleted.");
}

void ProductDocumentController::doAddProductDocument(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthenticationCheck(request,response);
    auto body = request.body();
    int	product_id;
    std::string	name;
    std::string	title;
    std::string	path;
    float	size;
    std::string	tags;
    std::string	details;
    int	status;
    std::string	description;
    try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      product_id = pt.get<int>("product_id");
      name = pt.get<std::string>("name");
      title = pt.get<std::string>("title");
      path = pt.get<std::string>("path");
      size = pt.get<float>("size");
      tags = pt.get<std::string>("tags");
      details = pt.get<std::string>("details");
      status = pt.get<int>("status");
      description = pt.get<std::string>("description");

      std::string id = angru::mvc::model::ProductDocumentModel::AddProductDocument(
                                                  product_id,
                                                  name,
                                                  title,
                                                  path,
                                                  size,
                                                  tags,
                                                  details,
                                                  status,
                                                  description );
      std::string message = "{\"message\":\"ProductDocument Added.\", \"id\":\"" + id + "\"}";
      response.send(Pistache::Http::Code::Ok, message);
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "ProductDocuments not found.");
    }
}

void ProductDocumentController::doUpdateProductDocument(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    angru::security::authorization::CORS(request,response);
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthenticationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
      id = value.as<int>();
    }
    if(id == -1){
      response.send(Pistache::Http::Code::Not_Found, "ProductDocuments not found.");
    }
    auto body = request.body();
    int	product_id;
    std::string	name;
    std::string	title;
    std::string	path;
    float	size;
    std::string	tags;
    std::string	details;
    int	status;
    std::string	description;
   try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      product_id = pt.get<int>("product_id");
      name = pt.get<std::string>("name");
      title = pt.get<std::string>("title");
      path = pt.get<std::string>("path");
      size = pt.get<float>("size");
      tags = pt.get<std::string>("tags");
      details = pt.get<std::string>("details");
      status = pt.get<int>("status");
      description = pt.get<std::string>("description");
      angru::mvc::model::ProductDocumentModel::UpdateProductDocument(
                                                  id,
                                                  product_id,
                                                  name,
                                                  title,
                                                  path,
                                                  size,
                                                  tags,
                                                  details,
                                                  status,
                                                  description );
      response.send(Pistache::Http::Code::Ok, "ProductDocuments updated.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "ProductDocuments not found.");
    }
 }

} // model
} // mvc
} // angru
