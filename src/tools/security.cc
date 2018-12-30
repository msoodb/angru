#include "tools/security.h"

#include <iostream>
#include <string>
#include <chrono>

#include <boost/uuid/sha1.hpp>
#include <jwt/jwt.hpp>

namespace angru{
namespace security{
namespace cryptography{

std::string get_base64(const std::string& p_arg){

}
std::string get_md5(const std::string& p_arg){

}
std::string get_sha1(const std::string& p_arg){
  boost::uuids::detail::sha1 sha1;
      sha1.process_bytes(p_arg.data(), p_arg.size());
      unsigned hash[5] = {0};
      sha1.get_digest(hash);

      // Back to string
      char buf[41] = {0};

      for (int i = 0; i < 5; i++)
      {
          std::sprintf(buf + (i << 3), "%08x", hash[i]);
      }
      return std::string(buf);
}
std::string get_sha256(const std::string& p_arg){

}
std::string get_jwt(const std::string& id, const std::string&email){
  using namespace jwt::params;

  auto key = "secret"; //Secret to use for the algorithm
  //Create JWT object
  jwt::jwt_object obj{algorithm("HS256"), payload({{"user", "admin"}}), secret(key)};

  //Use add_claim API to add claim values which are
  // _not_ strings.
  // For eg: `iat` and `exp` claims below.
  // Other claims could have been added in the payload
  // function above as they are just stringy things.
  obj.add_claim("iss", email)
       .add_claim("sub", "test")
       .add_claim("id", id)
       .add_claim("iat", 1513862371)
       .add_claim("exp", std::chrono::system_clock::now() + std::chrono::seconds{259200});
  //Get the encoded string/assertion
  auto enc_str = obj.signature();
  //std::cout << enc_str << std::endl;

  //Decode
  //auto dec_obj = jwt::decode(enc_str, algorithms({"hs256"}), secret(key));
  //std::cout << dec_obj.header() << std::endl;
  //std::cout << dec_obj.payload() << std::endl;

  return enc_str;
  }
} // namespace cryptography

namespace authorization{

void AuthorizationCheck(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter& response){
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    auto headers = request.headers();
    try
    {
        auto enc_str = headers.getRaw("Authorization");
        auto dec_obj = jwt::decode(enc_str.value(), jwt::params::algorithms({"hs256"}),
                        jwt::params::secret("secret"), jwt::params::verify(true));
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Unauthorized, "Authorization denied...");
    }
}
void ContentTypeJSONCheck(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter& response){
    auto headers = request.headers();
    try
    {
      auto content_type = headers.tryGet<Pistache::Http::Header::ContentType>();
      if (content_type != nullptr){
          if (content_type->mime() != MIME(Application, Json)){
            response.send(Pistache::Http::Code::Not_Acceptable, "Not Acceptable...");
          }
      }
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Not_Acceptable, "Not Acceptable...");
    }
}
void doGetOptions(const Pistache::Http::Request& req,
    Pistache::Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, "{\"message\":\"success\"}");
}

} // namespace authorization
} // namespace tools
} // namespace angru
