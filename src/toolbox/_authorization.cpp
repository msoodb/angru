#include <iostream>
#include <string>
#include <chrono>
#include <boost/uuid/sha1.hpp>
#include <jwt/jwt.hpp>
#include "_authorization.h"

void _Authorization::AuthorizationCheck(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter& response){
    auto headers = request.headers();
    try
    {
        /*auto content_type = headers.tryGet<Pistache::Http::Header::ContentType>();
        if (content_type != nullptr)
        {
            if (content_type->mime() == MIME(Application, Json))
                std::cout << " content_type is application/json" << '\n';
        }*/
        auto enc_str = headers.getRaw("Authorization");
        std::cout << enc_str.value() << '\n';
        auto dec_obj = jwt::decode(enc_str.value(), jwt::params::algorithms({"hs256"}),
                        jwt::params::secret("secret"), jwt::params::verify(true));
    }
    catch (std::exception const& e){
        //std::cerr << e.what() << std::endl;
        response.send(Pistache::Http::Code::Unauthorized, "Authorization denied...");
    }
}
void _Authorization::ContentTypeJSONCheck(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter& response){
    auto headers = request.headers();
    try
    {
      auto content_type = headers.tryGet<Pistache::Http::Header::ContentType>();
      if (content_type != nullptr){
          if (content_type->mime() != MIME(Application, Json))
            response.send(Pistache::Http::Code::Not_Acceptable, "Not Acceptable...");
      }
    }
    catch (std::exception const& e){
        response.send(Pistache::Http::Code::Not_Acceptable, "Not Acceptable...");
    }
  }
