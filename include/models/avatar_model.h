#ifndef ANGRU_AVATAR_MODEL_H_
#define ANGRU_AVATAR_MODEL_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace angru{
namespace mvc{
namespace model{

class AvatarModel
{
public:
	AvatarModel();
	~AvatarModel();
  static std::string GetAvatar(std::string & filename);
	static std::string AddAvatar(
																const std::string & filename,
																const std::string & data,
																size_t offset,
																size_t length);
	static bool DeleteAvatar(const std::string & path);
};

} // model
} // mvc
} // angru

#endif // ANGRU_AVATAR_MODEL_H_
