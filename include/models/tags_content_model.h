#ifndef ANGRU_TAGS_CONTENT_MODEL_H_
#define ANGRU_TAGS_CONTENT_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace angru{
namespace mvc{
namespace model{

class TagsContentModel
{
public:
	TagsContentModel();
	~TagsContentModel();
	static pqxx::result GetTagsContents(int page=1, std::string query="");
	static int GetTagsContentsCount(std::string query="");
	static boost::property_tree::ptree GetTagsContentsJson(int page=1, std::string query="");
  static pqxx::result GetTagsContent(std::string id);
	static boost::property_tree::ptree GetTagsContentJson(std::string id);
	static std::string AddTagsContent(
													std::string	tag,
													std::string	content,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateTagsContent(
													std::string	id,
													std::string	tag,
													std::string	content,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteTagsContent(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_TAGS_CONTENT_MODEL_H_
