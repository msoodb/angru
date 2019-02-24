#ifndef ANGRU_TAGS_CONTENT_CONTROLLER_H_
#define ANGRU_TAGS_CONTENT_CONTROLLER_H_

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

class TagsContentController
{
public:
	TagsContentController();
	~TagsContentController();
	static void	doGetTagsContents(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doGetTagsContent(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
  static void	doDeleteTagsContent(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doAddTagsContent(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
	static void	doUpdateTagsContent(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
};

} // model
} // mvc
} // angru

#endif // ANGRU_TAGS_CONTENT_CONTROLLER_H_
