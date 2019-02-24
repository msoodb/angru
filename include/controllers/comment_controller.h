#ifndef ANGRU_COMMENT_CONTROLLER_H_
#define ANGRU_COMMENT_CONTROLLER_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/description.h>
#include <pistache/router.h>
#include <pistache/serializer/rapidjson.h>

namespace angru{
namespace mvc{
namespace controller{

class CommentController
{
public:
	CommentController();
	~CommentController();
	static void	doGetComments(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetComment(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteComment(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddComment(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateComment(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_COMMENT_CONTROLLER_H_
