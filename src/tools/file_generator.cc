#include "tools/file_generator.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <experimental/filesystem>

#include <boost/algorithm/string.hpp>

namespace angru{
namespace tools{
namespace generator{

void modelGenerator(std::string file_name, std::string entity_name,
  std::string class_name, std::vector<std::pair<std::string, std::string>> fields)
{
  std::string guard = "ANGRU_" + file_name + "_H_";
  boost::to_upper(guard);

  std::string path_h= "/home/masoud/Projects/angru/generated/" + file_name + ".h";
  std::ofstream out(path_h);
  //-----------------------------    .h     -------------------------------
  out << "#ifndef " << guard << '\n';
  out << "#define " << guard << '\n';
  out << '\n';
  out << "#include <iostream>" << '\n';
  out << "#include <vector>" << '\n';
  out << "#include <pqxx/pqxx>" << '\n';
  out << '\n';
  out << "#include <boost/property_tree/ptree.hpp>" << '\n';
  out << "#include <boost/property_tree/json_parser.hpp>" << '\n';
  out << '\n';
  out << "namespace angru{" << '\n';
  out << "namespace mvc{" << '\n';
  out << "namespace model{" << '\n';
  out << '\n';
  out << "class " << class_name << '\n';
  out << "{" << '\n';
  out << "public:" << '\n';
  out << "	" << class_name << "();" << '\n';
  out << "	~" << class_name << "();" << '\n';
  out << "	static pqxx::result Get" << entity_name << "s(int page=1, std::string query=\"\");" << '\n';
  out << "	static int Get" << entity_name << "sCount(std::string query=\"\");" << '\n';
  out << "	static boost::property_tree::ptree Get" << entity_name << "sJson(int page=1, std::string query=\"\");" << '\n';
  out << "  static pqxx::result Get" << entity_name << "(int);" << '\n';
  out << "	static boost::property_tree::ptree Get" << entity_name << "Json(int);" << '\n';
  out << "	static std::string Add" << entity_name << "(" << '\n';
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
      if(itr->second == "id"){
        continue;
      }
      out << "													" << itr->first << '\t' <<itr->second;
      if(itr != fields.end()-1){
        out << "," << '\n';
      }
  }
  out << ");" << '\n';
  out << "	static void Update" << entity_name << "(" << '\n';
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
      out << "													" << itr->first << '\t' <<itr->second;
      if(itr != fields.end()-1){
        out << "," << '\n';
      }
  }
  out << ");" << '\n';
  out << "	static void Delete" << entity_name << "(int);" << '\n';
  out << "};" << '\n';
  out << '\n';
  out << "} // model" << '\n';
  out << "} // mvc" << '\n';
  out << "} // angru" << '\n';
  out << '\n';
  out << "#endif // " << guard << '\n';
  //----------------------------------------------------------------------------
  out.close();

  std::string path_cc= "/home/masoud/Projects/angru/generated/" + file_name + ".cc";
  //std::ofstream out(path_cc);
  //-----------------------------    .h     -------------------------------
  return;
}

} // namespace generator
} // namespace tools
} // namespace angru
