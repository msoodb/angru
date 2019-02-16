#ifndef ANGRU_SECURITY_H_
#define ANGRU_SECURITY_H_

#include <iostream>

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/description.h>
#include <pistache/router.h>
#include <pistache/serializer/rapidjson.h>

namespace angru{
namespace security{
namespace cryptography{

std::string get_base64(const std::string&);
std::string decode_base64(std::string input);
std::string get_md5(const std::string&);
std::string get_sha1(const std::string&);
std::string get_sha256(const std::string&);
std::string get_jwt(const std::string&, const std::string&);

} // namespace cryptography

namespace authorization{

std::string AuthenticationCheck(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter&);
void ContentTypeJSONCheck(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter&);
void CORS(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter&);
void doGetOptions(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);

} // namespace authorization
} // namespace tools
} // namespace angru

#endif // ANGRU_SECURITY_H_
