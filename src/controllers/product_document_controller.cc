#include "controllers/product_document_controller.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "tools/security.h"
#include "models/product_document_model.h"

namespace angru{
namespace mvc{
namespace controller{

ProductDocumentController::ProductDocumentController(){}
ProductDocumentController::~ProductDocumentController(){}
void ProductDocumentController::doGetProductDocuments(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*") ;
    response.headers().add<Pistache::Http::Header::AccessControlAllowHeaders>("DNT,X-CustomHeader,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,dataType,Content-Type,api_type,Authorization") ;
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    int product_id = -1;
    if (request.hasParam(":product_id")) {
        auto value = request.param(":product_id");
        product_id = value.as<int>();
    }
    try
    {
      boost::property_tree::ptree product_documents = angru::mvc::model::ProductDocumentModel::GetProductDocumentsJson(product_id);
      std::ostringstream oss;
      boost::property_tree::write_json(oss, product_documents);

      std::string inifile_text = oss.str();
      if (inifile_text.empty()) {
        response.send(Pistache::Http::Code::Not_Found, "ProductDocuments not found.");
      } else {
        response.send(Pistache::Http::Code::Ok, inifile_text);
      }
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "ProductDocuments not found.");
    }
}
void ProductDocumentController::doGetProductDocument(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*") ;
    response.headers().add<Pistache::Http::Header::AccessControlAllowHeaders>("DNT,X-CustomHeader,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,dataType,Content-Type,api_type,Authorization") ;
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    int product_id = -1;
    if (request.hasParam(":product_id")) {
        auto value = request.param(":product_id");
        product_id = value.as<int>();
    }
    try
    {
      boost::property_tree::ptree product_document = angru::mvc::model::ProductDocumentModel::GetProductDocumentJson(id, product_id);
      std::ostringstream oss;
      boost::property_tree::write_json(oss, product_document);

      std::string inifile_text = oss.str();

      if (inifile_text.empty()) {
        response.send(Pistache::Http::Code::Not_Found, "ProductDocuments not found.");
      }
      else {
        response.send(Pistache::Http::Code::Ok, inifile_text);
      }
    }
    catch (std::exception const& e){
      LOG_ERROR << e.what();
      response.send(Pistache::Http::Code::Not_Found, "ProductDocuments not found.");
    }
    catch(...)
  	{
      LOG_ERROR << "Error: unknown exception";
      response.send(Pistache::Http::Code::Not_Found, "ProductDocuments not found.");
  	}
}
void ProductDocumentController::doDeleteProductDocument(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.headers().add<Pistache::Http::Header::AccessControlAllowMethods>("OPTIONS, GET, POST, DELETE, PUT");
    response.headers().add<Pistache::Http::Header::AccessControlAllowHeaders>("DNT,X-CustomHeader,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,dataType,Content-Type,api_type,Authorization") ;
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    int product_id = -1;
    if (request.hasParam(":product_id")) {
        auto value = request.param(":product_id");
        product_id = value.as<int>();
    }
    angru::mvc::model::ProductDocumentModel::DeleteProductDocument(id, product_id);
    response.send(Pistache::Http::Code::Ok, "ProductDocument deleted.");
}
void ProductDocumentController::doAddProductDocument(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*") ;
    response.headers().add<Pistache::Http::Header::AccessControlAllowHeaders>("DNT,X-CustomHeader,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,dataType,Content-Type,api_type,Authorization") ;
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    auto body = request.body();
    int product_id;
		std::string name;
		std::string title;
		std::string path;
		std::string extention;
		float size;
		std::string tags;
		std::string details;
		bool active;
		std::string description;

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
      extention = pt.get<std::string>("extention");
      size = pt.get<float>("size");
      tags = pt.get<std::string>("tags");
      details = pt.get<std::string>("details");
      active = pt.get<bool>("active");
      description = pt.get<std::string>("description");

      angru::mvc::model::ProductDocumentModel::AddProductDocument(product_id,
      																			name,
      																			title,
      																			path,
      																			extention,
      																			size,
      																			tags,
      																			details,
      																			active,
      																			description);
      response.send(Pistache::Http::Code::Ok, "ProductDocument added.");
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Found, "ProductDocuments not found.");
    }
}
void ProductDocumentController::doUpdateProductDocument(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.headers().add<Pistache::Http::Header::AccessControlAllowMethods>("OPTIONS, GET, POST, DELETE, PUT");
    response.headers().add<Pistache::Http::Header::AccessControlAllowHeaders>("DNT,X-CustomHeader,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,dataType,Content-Type,api_type,Authorization") ;
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    angru::security::authorization::ContentTypeJSONCheck(request,response);
    angru::security::authorization::AuthorizationCheck(request,response);
    int id = -1;
    if (request.hasParam(":id")) {
        auto value = request.param(":id");
        id = value.as<int>();
    }
    int product_id = -1;
    if (request.hasParam(":product_id")) {
        auto value = request.param(":product_id");
        product_id = value.as<int>();
    }
    auto body = request.body();
		std::string name;
		std::string title;
		std::string path;
		std::string extention;
		float size;
		std::string tags;
		std::string details;
		bool active;
		std::string description;
    try
    {
      std::stringstream ss;
      ss << body;
      boost::property_tree::ptree pt;
      boost::property_tree::read_json(ss, pt);
      name = pt.get<std::string>("name");
      title = pt.get<std::string>("title");
      path = pt.get<std::string>("path");
      extention = pt.get<std::string>("extention");
      size = pt.get<float>("size");
      tags = pt.get<std::string>("tags");
      details = pt.get<std::string>("details");
      active = pt.get<bool>("active");
      description = pt.get<std::string>("description");
      angru::mvc::model::ProductDocumentModel::UpdateProductDocument(id,
                                                              product_id,
                                                              name,
                                                              title,
                                                              path,
                                                              extention,
                                                              size,
                                                              tags,
                                                              details,
                                                              active,
                                                              description);
      response.send(Pistache::Http::Code::Ok, "ProductDocuments updated.");
    }
    catch (std::exception const& e){
      std::cout << e.what() << '\n';
      response.send(Pistache::Http::Code::Not_Found, "ProductDocuments not found.");
    }
}

} // controller
} // mvc
} // angru
