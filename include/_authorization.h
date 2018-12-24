#ifndef ANGRU_AUTHORIZATION_H_
#define ANGRU_AUTHORIZATION_H_

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/description.h>
#include <pistache/router.h>
#include <pistache/serializer/rapidjson.h>

class _Authorization
{
public:
	static void AuthorizationCheck(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter&);
	static void ContentTypeJSONCheck(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter&);
};
#endif
