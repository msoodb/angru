// This is start of the header guard. USER_CONTROLLER_H can be any unique name.  By convention, we use the name of the header file.
#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/description.h>
#include <pistache/router.h>
#include <pistache/serializer/rapidjson.h>

// This is the content of the .h file, which is where the declarations go
class UserController
{
public:
	UserController();
	~UserController();
	static void doGetUsers(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void doGetUser(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void doDeleteUser(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

// This is the end of the header guard
#endif
