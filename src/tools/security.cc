#include "tools/security.h"

#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/uuid/sha1.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/remove_whitespace.hpp>
#include <jwt/jwt.hpp>




namespace angru{
namespace security{
namespace cryptography{

std::string get_base64(const std::string& p_arg){
  return "";
}
std::string decode_base64(std::string input){
  using namespace boost::archive::iterators;
  typedef transform_width<binary_from_base64<remove_whitespace
      <std::string::const_iterator> >, 8, 6> ItBinaryT;
  try
  {
    // If the input isn't a multiple of 4, pad with =
    size_t num_pad_chars((4 - input.size() % 4) % 4);
    input.append(num_pad_chars, '=');

    size_t pad_chars(std::count(input.begin(), input.end(), '='));
    std::replace(input.begin(), input.end(), '=', 'A');
    std::string output(ItBinaryT(input.begin()), ItBinaryT(input.end()));
    output.erase(output.end() - pad_chars, output.end());
    return output;
  }
  catch (std::exception const&)
  {
    return std::string("");
  }
}
std::string get_md5(const std::string& p_arg){
  return "";
}
std::string get_sha1(const std::string& p_arg){
  boost::uuids::detail::sha1 sha1;
    sha1.process_bytes(p_arg.data(), p_arg.size());
    unsigned hash[5] = {0};
    sha1.get_digest(hash);

    char buf[41] = {0};

    for (int i = 0; i < 5; i++)
    {
        std::sprintf(buf + (i << 3), "%08x", hash[i]);
    }
    return std::string(buf);
}
std::string get_sha256(const std::string& p_arg){
  return "";
}
std::string get_jwt(const std::string& user_id, const std::string&email){
  using namespace jwt::params;
  auto key = "secret";
  jwt::jwt_object obj{algorithm("HS256"), payload({{"user", "admin"}}), secret(key)};
  obj.add_claim("iss", email)
       .add_claim("sub", "test")
       .add_claim("id", user_id)
       .add_claim("iat", 1513862371)
       .add_claim("exp", std::chrono::system_clock::now() + std::chrono::seconds{259200});
  auto enc_str = obj.signature();
  return enc_str;
  }
} // namespace cryptography

namespace authorization{

std::string AuthenticationCheck(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter& response){
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    auto headers = request.headers();
    auto enc_str = headers.getRaw("Authorization");
    try
    {
        auto dec_obj = jwt::decode(enc_str.value(), jwt::params::algorithms({"hs256"}),
                        jwt::params::secret("secret"), jwt::params::verify(true));
        std::stringstream ss;
        ss << dec_obj.payload();
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);
        std::string user_id = pt.get<std::string>("id");
        return user_id;
    }
    catch (std::exception const& e){
      response.send(Pistache::Http::Code::Unauthorized, "{\"message\":\"Authorization denied.\"}");
    }
    catch(...)
    {
      response.send(Pistache::Http::Code::Unauthorized, "{\"message\":\"Authorization denied.\"}");
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
void CORS(const Pistache::Rest::Request& request,
  Pistache::Http::ResponseWriter& response){
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.headers().add<Pistache::Http::Header::AccessControlAllowMethods>("OPTIONS, GET, POST, DELETE, PUT");
    response.headers().add<Pistache::Http::Header::AccessControlAllowHeaders>("DNT,X-CustomHeader,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,dataType,Content-Type,api_type,Authorization,boundary") ;
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
}
void doGetOptions(const Pistache::Rest::Request& req,
    Pistache::Http::ResponseWriter response) {
      response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
      response.headers().add<Pistache::Http::Header::AccessControlAllowMethods>("OPTIONS, GET, POST, DELETE, PUT");
      response.headers().add<Pistache::Http::Header::AccessControlAllowHeaders>("DNT,X-CustomHeader,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,dataType,Content-Type,api_type,Authorization,boundary") ;
      response.send(Pistache::Http::Code::Ok, "{\"message\":\"success\"}");
}

} // namespace authorization
} // namespace tools
} // namespace angru
