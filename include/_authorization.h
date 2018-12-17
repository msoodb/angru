// This is start of the header guard.  INC_Authorization_H can be any unique name.  By convention, we use the name of the header file.
#ifndef INC_Authorization_H
#define INC_Authorization_H

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/description.h>
#include <pistache/router.h>
#include <pistache/serializer/rapidjson.h>

// This is the content of the .h file, which is where the declarations go
class _Authorization
{
public:
	static void AuthorizationCheck(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter&);
	static void ContentTypeJSONCheck(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter&);
};
// This is the end of the header guard
#endif
