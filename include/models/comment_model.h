#ifndef ANGRU_COMMENT_MODEL_H_
#define ANGRU_COMMENT_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "wrappers/postgresql.h"

namespace angru{
namespace mvc{
namespace model{

class CommentModel
{
public:
	CommentModel();
	~CommentModel();
	static pqxx::result GetComments(int page=1, int limit=LIMIT_COUNT, std::string query="");
	static int GetCommentsCount(std::string query="");
	static boost::property_tree::ptree GetCommentsJson(int page=1, int limit=LIMIT_COUNT, std::string query="");
  static pqxx::result GetComment(std::string id);
	static boost::property_tree::ptree GetCommentJson(std::string id);
	static std::string AddComment(
													std::string	member,
													std::string	content,
													std::string	comment,
													std::string	reply_to,
													std::string	created_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void UpdateComment(
													std::string	id,
													std::string	member,
													std::string	content,
													std::string	comment,
													std::string	reply_to,
													std::string	updated_by,
													std::string	details,
													int	status,
													int	situation,
													std::string	description);
	static void DeleteComment(std::string id);
};

} // model
} // mvc
} // angru

#endif // ANGRU_COMMENT_MODEL_H_
