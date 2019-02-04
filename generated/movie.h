#ifndef ANGRU_MOVIE_H_
#define ANGRU_MOVIE_H_

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace angru{
namespace mvc{
namespace model{

class CMovie
{
public:
	CMovie();
	~CMovie();
	static pqxx::result GetMovies(int page=1, std::string query="");
	static int GetMoviesCount(std::string query="");
	static boost::property_tree::ptree GetMoviesJson(int page=1, std::string query="");
  static pqxx::result GetMovie(int);
	static boost::property_tree::ptree GetMovieJson(int);
	static std::string AddMovie(
													std::string	title,
													std::string	tags,
													std::string	details,
													std::string	code,
													bool	active,
													std::string	description);
	static void UpdateMovie(
													int	id,
													std::string	title,
													std::string	tags,
													std::string	details,
													std::string	code,
													bool	active,
													std::string	description);
	static void DeleteMovie(int);
};

} // model
} // mvc
} // angru

#endif // ANGRU_MOVIE_H_
