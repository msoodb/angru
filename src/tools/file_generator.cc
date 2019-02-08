#include "tools/file_generator.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <experimental/filesystem>

#include <boost/algorithm/string.hpp>

namespace angru{
namespace tools{
namespace generator{

void modelGenerator(std::string table_name_single, std::string entity_name,
    std::vector<std::pair<std::string, std::string>> fields)
{
  std::string table_name = table_name_single;
  std::string file_name = table_name_single + "_model";
  std::string class_name = entity_name + "Model";
  std::string guard = "ANGRU_" + file_name + "_H_"; boost::to_upper(guard);
  int field_added=0;
  std::vector<std::pair<std::string, std::string>>::iterator itr;
  std::string path_h= "/home/masoud/Projects/angru/generated/model_h/" + file_name + ".h";
  std::ofstream out_h(path_h);
  //-----------------------------    .h     -------------------------------
  out_h << "#ifndef " << guard << '\n';
  out_h << "#define " << guard << '\n';
  out_h << '\n';
  out_h << "#include <iostream>" << '\n';
  out_h << "#include <vector>" << '\n';
  out_h << "#include <pqxx/pqxx>" << '\n';
  out_h << '\n';
  out_h << "#include <boost/property_tree/ptree.hpp>" << '\n';
  out_h << "#include <boost/property_tree/json_parser.hpp>" << '\n';
  out_h << '\n';
  out_h << "namespace angru{" << '\n';
  out_h << "namespace mvc{" << '\n';
  out_h << "namespace model{" << '\n';
  out_h << '\n';
  out_h << "class " << class_name << '\n';
  out_h << "{" << '\n';
  out_h << "public:" << '\n';
  out_h << "	" << class_name << "();" << '\n';
  out_h << "	~" << class_name << "();" << '\n';
  out_h << "	static pqxx::result Get" << entity_name << "s(int page=1, std::string query=\"\");" << '\n';
  out_h << "	static int Get" << entity_name << "sCount(std::string query=\"\");" << '\n';
  out_h << "	static boost::property_tree::ptree Get" << entity_name << "sJson(int page=1, std::string query=\"\");" << '\n';
  out_h << "  static pqxx::result Get" << entity_name << "(int);" << '\n';
  out_h << "	static boost::property_tree::ptree Get" << entity_name << "Json(int);" << '\n';
  out_h << "	static std::string Add" << entity_name << "(" << '\n';
  field_added=0;
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "id"){
      continue;
    }
    else if(itr->second == "created_at"){
      continue;
    }
    else if(itr->second == "deleted_at"){
      continue;
    }
    else if(itr->second == "updated_at"){
      continue;
    }
    if(field_added > 0){
      out_h << "," << '\n';
    }
    out_h << "													" << itr->first << '\t' <<itr->second;
    field_added++;
  }
  out_h << ");" << '\n';
  out_h << "	static void Update" << entity_name << "(" << '\n';
  field_added=0;
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "created_at"){
      continue;
    }
    else if(itr->second == "deleted_at"){
      continue;
    }
    else if(itr->second == "updated_at"){
      continue;
    }
    if(field_added > 0){
      out_h << "," << '\n';
    }
    out_h << "													" << itr->first << '\t' <<itr->second;
    field_added++;
  }
  out_h << ");" << '\n';
  out_h << "	static void Delete" << entity_name << "(int);" << '\n';
  out_h << "};" << '\n';
  out_h << '\n';
  out_h << "} // model" << '\n';
  out_h << "} // mvc" << '\n';
  out_h << "} // angru" << '\n';
  out_h << '\n';
  out_h << "#endif // " << guard << '\n';
  //----------------------------------------------------------------------------
  out_h.close();

  std::string path_cc= "/home/masoud/Projects/angru/generated/model_cc/" + file_name + ".cc";
  std::ofstream out_cc(path_cc);
  //-----------------------------    .cc     -------------------------------
  out_cc << "#include \"models/" << file_name << ".h\"" << '\n';
  out_cc << '\n';
  out_cc << "#include <iostream>" << '\n';
  out_cc << "#include <string>" << '\n';
  out_cc << '\n';
  out_cc << "#include <pqxx/pqxx>" << '\n';
  out_cc << "#include <boost/property_tree/ptree.hpp>" << '\n';
  out_cc << "#include <boost/property_tree/json_parser.hpp>" << '\n';
  out_cc << "#include \"tools/system.h\"" << '\n';
  out_cc << "#include \"tools/log.h\"" << '\n';
  out_cc << "#include \"wrappers/postgresql.h\"" << '\n';
  out_cc << "#include \"wrappers/csv_writer.h\"" << '\n';
  out_cc << '\n';
  out_cc << "namespace angru{" << '\n';
  out_cc << "namespace mvc{" << '\n';
  out_cc << "namespace model{" << '\n';
  out_cc << '\n';
  out_cc << class_name << "::" << class_name << "(){}" << '\n';
  out_cc << class_name << "::~"<< class_name << "(){}" << '\n';
  out_cc << '\n';
  out_cc << "pqxx::result " << class_name << "::Get" << entity_name << "s(int page, std::string query){" << '\n';
  out_cc << "	pqxx::connection C(angru::wrapper::Postgresql::connection_string());" << '\n';
  out_cc << "	try {" << '\n';
  out_cc << "		if (C.is_open()) {" << '\n';
  out_cc << "			 LOG_INFO << \"Opened database successfully: \" << C.dbname();" << '\n';
  out_cc << "		} else {" << '\n';
  out_cc << "			 LOG_ERROR << \"Can't open database: \" << C.dbname();" << '\n';
  out_cc << "		}" << '\n';
  out_cc << "		C.disconnect ();" << '\n';
  out_cc << "	} catch (const angru::system::exception::error &e) {" << '\n';
  out_cc << "			LOG_ERROR << e.what();" << '\n';
  out_cc << "	}" << '\n';
  out_cc << "	LOG_INFO << \"Connected to database: \" << C.dbname();" << '\n';
  out_cc << "	pqxx::work W(C);" << '\n';
  out_cc << "	std::string complete_query = \"SELECT \\" << '\n';
  field_added=0;
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "deleted_at"){
      continue;
    }
    if(field_added > 0){
      out_cc << ", \\" << '\n';
    }
    out_cc << "									      				" << itr->second << " ";
    field_added++;
  }
  out_cc << " FROM " << table_name << "s where deleted_at is NULL \";" << '\n';
  out_cc << "	if(!query.empty())" << '\n';
  out_cc << "	{" << '\n';
  out_cc << "		complete_query += \" AND \";" << '\n';
  out_cc << "		complete_query +=  query;" << '\n';
  out_cc << "	}" << '\n';
  out_cc << "	complete_query += \" order by id \";" << '\n';
  out_cc << "	complete_query += \" limit 20 offset \";" << '\n';
  out_cc << "	int offset = (page-1)* OFFSET_COUNT ;" << '\n';
  out_cc << "	complete_query += std::to_string(offset);" << '\n';
  out_cc << "  C.prepare(\"find\", complete_query);" << '\n';
  out_cc << "  pqxx::result R = W.prepared(\"find\").exec();" << '\n';
  out_cc << "  W.commit();" << '\n';
  out_cc << "	return R;" << '\n';
  out_cc << "}" << '\n';
  out_cc << '\n';
  out_cc << "int " << class_name << "::Get" << entity_name << "sCount(std::string query){" << '\n';
  out_cc << "	pqxx::connection C(angru::wrapper::Postgresql::connection_string());" << '\n';
  out_cc << "	try {" << '\n';
  out_cc << "		if (C.is_open()) {" << '\n';
  out_cc << "			 LOG_INFO << \"Opened database successfully: \" << C.dbname();" << '\n';
  out_cc << "		} else {" << '\n';
  out_cc << "			 LOG_ERROR << \"Can't open database: \" << C.dbname();" << '\n';
  out_cc << "		}" << '\n';
  out_cc << "		C.disconnect ();" << '\n';
  out_cc << "	} catch (const angru::system::exception::error &e) {" << '\n';
  out_cc << "			LOG_ERROR << e.what();" << '\n';
  out_cc << "	}" << '\n';
  out_cc << "	LOG_INFO << \"Connected to database: \" << C.dbname();" << '\n';
  out_cc << "	pqxx::work W(C);" << '\n';
  out_cc << "	std::string complete_query = \"SELECT count(id) FROM " << table_name << "s where deleted_at is NULL \";" << '\n';
  out_cc << "	if(!query.empty())" << '\n';
  out_cc << "	{" << '\n';
  out_cc << "		complete_query += \" AND \";" << '\n';
  out_cc << "		complete_query +=  query;" << '\n';
  out_cc << "	}" << '\n';
  out_cc << "  C.prepare(\"find\", complete_query);" << '\n';
  out_cc << "  pqxx::result R = W.prepared(\"find\").exec();" << '\n';
  out_cc << "  W.commit();" << '\n';
  out_cc << "	return (R[0][0]).as<int>();" << '\n';
  out_cc << "}" << '\n';
  out_cc << '\n';
  out_cc << "boost::property_tree::ptree " << class_name << "::Get" << entity_name << "sJson(int page, std::string query){" << '\n';
  out_cc << "	pqxx::result R = Get" << entity_name << "s(page, query);" << '\n';
  out_cc << "	int result_count = Get" << entity_name << "sCount(query);" << '\n';
  out_cc << "	int pageCount = (result_count / OFFSET_COUNT) + 1;" << '\n';
  out_cc << '\n';
  out_cc << "	boost::property_tree::ptree result_node;" << '\n';
  out_cc << "	boost::property_tree::ptree info_node;" << '\n';
  out_cc << "	boost::property_tree::ptree " << table_name << "_node;" << '\n';
  out_cc << "	boost::property_tree::ptree " << table_name << "s_node;" << '\n';
  out_cc << '\n';
  out_cc << "	for (size_t i = 0; i < R.size(); i++) {" << '\n';
  int i=0;
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "deleted_at"){
      continue;
    }
    out_cc << "		" << table_name << "_node.put(\"" << itr->second << "\", R[i][" << i << "]);" << '\n';
    i++;
  }
  out_cc << "		" << table_name << "s_node.push_back(std::make_pair(\"\", " << table_name << "_node));" << '\n';
  out_cc << "	}" << '\n';
  out_cc << "	info_node.put<int>(\"page\", page);" << '\n';
  out_cc << "	info_node.put<int>(\"offset\", OFFSET_COUNT);" << '\n';
  out_cc << "	info_node.put<int>(\"page_count\", pageCount);" << '\n';
  out_cc << "	info_node.put<int>(\"result_count\", result_count);" << '\n';
  out_cc << '\n';
  out_cc << "	result_node.add_child(\"info\", info_node);" << '\n';
  out_cc << "	result_node.add_child(\"" << table_name << "s\", " << table_name << "s_node);" << '\n';
  out_cc << "	return result_node;" << '\n';
  out_cc << "}" << '\n';
  out_cc << '\n';
  out_cc << "pqxx::result " << class_name << "::Get" << entity_name << "(int id){" << '\n';
  out_cc << "	pqxx::connection C(angru::wrapper::Postgresql::connection_string());" << '\n';
  out_cc << "	try {" << '\n';
  out_cc << "		if (C.is_open()) {" << '\n';
  out_cc << "			 LOG_INFO << \"Opened database successfully: \" << C.dbname();" << '\n';
  out_cc << "		} else {" << '\n';
  out_cc << "			 LOG_ERROR << \"Can't open database: \" << C.dbname();" << '\n';
  out_cc << "		}" << '\n';
  out_cc << "		C.disconnect ();" << '\n';
  out_cc << "	} catch (const angru::system::exception::error &e) {" << '\n';
  out_cc << "			LOG_ERROR << e.what();" << '\n';
  out_cc << "	}" << '\n';
  out_cc << "	LOG_INFO << \"Connected to database: \" << C.dbname();" << '\n';
  out_cc << "	pqxx::work W(C);" << '\n';
  out_cc << "  C.prepare(\"find\", \"SELECT \\" << '\n';
  field_added=0;
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "deleted_at"){
      continue;
    }
    if(field_added > 0){
      out_cc << ", \\" << '\n';
    }
    out_cc << "									      				" << itr->second << " ";
    field_added++;
  }
  out_cc << " FROM " << table_name << "s where id = $1 and deleted_at is NULL \");" << '\n';
  out_cc << "  pqxx::result R = W.prepared(\"find\")(id).exec();" << '\n';
  out_cc << "	W.commit();" << '\n';
  out_cc << "	return R;" << '\n';
  out_cc << "}" << '\n';
  out_cc << '\n';
  out_cc << "boost::property_tree::ptree " << class_name << "::Get" << entity_name << "Json(int id){" << '\n';
  out_cc << "	pqxx::result R = Get" << entity_name << "(id);" << '\n';
  out_cc << "	boost::property_tree::ptree " << table_name << "_node;" << '\n';
  out_cc << '\n';
  out_cc << "	if(R.size() == 1){" << '\n';
  i=0;
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "deleted_at"){
      continue;
    }
    out_cc << "		" << table_name << "_node.put(\"" << itr->second << "\", R[0][" << i << "]);" << '\n';
    i++;
  }
  out_cc << "	}" << '\n';
  out_cc << "	return " << table_name << "_node;" << '\n';
  out_cc << "}" << '\n';
  out_cc << '\n';
  out_cc << "std::string " << class_name << "::Add" << entity_name << "(" << '\n';
  field_added=0;
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "id"){
      continue;
    }
    else if(itr->second == "created_at"){
      continue;
    }
    else if(itr->second == "deleted_at"){
      continue;
    }
    else if(itr->second == "updated_at"){
      continue;
    }
    if(field_added > 0){
      out_cc << ", " << '\n';
    }
    out_cc << "													" << itr->first << '\t' <<itr->second;
    field_added++;
  }
  out_cc << "){" << '\n';
  out_cc << "	pqxx::connection C(angru::wrapper::Postgresql::connection_string());" << '\n';
  out_cc << "	try {" << '\n';
  out_cc << "		if (C.is_open()) {" << '\n';
  out_cc << "			 LOG_INFO << \"Opened database successfully: \" << C.dbname();" << '\n';
  out_cc << "		} else {" << '\n';
  out_cc << "			 LOG_ERROR << \"Can't open database: \" << C.dbname();" << '\n';
  out_cc << "		}" << '\n';
  out_cc << "		C.disconnect ();" << '\n';
  out_cc << "	} catch (const angru::system::exception::error &e) {" << '\n';
  out_cc << "			LOG_ERROR << e.what();" << '\n';
  out_cc << "	}" << '\n';
  out_cc << "	LOG_INFO << \"Connected to database: \" << C.dbname();" << '\n';
  out_cc << "	pqxx::work W(C);" << '\n';
  out_cc << "	C.prepare(\"insert\", \"INSERT INTO " << table_name << "s( \\" << '\n';
  field_added=0;
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(field_added > 0){
      out_cc << ", \\" << '\n';
    }
    out_cc << "													" << itr->second;
    field_added++;
  }
  out_cc << "	) VALUES (\\" << '\n';
  i=1;
  field_added=0;
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(field_added > 0){
      out_cc << ", \\" << '\n';
    }
    if(itr->second == "id"){
      out_cc << "												   DEFAULT";
    }
    else if(itr->second == "created_at"){
      out_cc << "												   now()";
    }
    else if(itr->second == "deleted_at"){
      out_cc << "												   NULL";
    }
    else if(itr->second == "updated_at"){
      out_cc << "												   NULL";
    }
    else{
      out_cc << "												   $" << i;
      i++;
    }
    field_added++;
  }
  out_cc << " ) RETURNING id\");" << '\n';
  out_cc << '\n';
  out_cc << "  pqxx::result R = W.prepared(\"insert\")" << '\n';
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "id"){
      continue;
    }
    else if(itr->second == "created_at"){
      continue;
    }
    else if(itr->second == "deleted_at"){
      continue;
    }
    else if(itr->second == "updated_at"){
      continue;
    }
    else{
      out_cc << "                 ("<< itr->second <<")"<< '\n';
    }
  }
  out_cc << "         .exec();" << '\n';
  out_cc << "  W.commit();" << '\n';
  out_cc << "	std::string id=\"\";" << '\n';
  out_cc << "	if(R.size() == 1){" << '\n';
  out_cc << "		id = R[0][0].as<std::string>();" << '\n';
  out_cc << "	}" << '\n';
  out_cc << "	return id;" << '\n';
  out_cc << "}" << '\n';
  out_cc << '\n';
  out_cc << "void " << class_name << "::Update" << entity_name << "( " << '\n';
  field_added=0;
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "created_at"){
      continue;
    }
    else if(itr->second == "deleted_at"){
      continue;
    }
    else if(itr->second == "updated_at"){
      continue;
    }
    if(field_added > 0){
      out_cc << "," << '\n';
    }
    out_cc << "													" << itr->first << '\t' <<itr->second;
    field_added++;
  }
  out_cc << " ){" << '\n';
  out_cc << "	pqxx::connection C(angru::wrapper::Postgresql::connection_string());" << '\n';
  out_cc << "	try {" << '\n';
  out_cc << "		if (C.is_open()) {" << '\n';
  out_cc << "			 LOG_INFO << \"Opened database successfully: \" << C.dbname();" << '\n';
  out_cc << "		} else {" << '\n';
  out_cc << "			 LOG_ERROR << \"Can't open database: \" << C.dbname();" << '\n';
  out_cc << "		}" << '\n';
  out_cc << "		C.disconnect ();" << '\n';
  out_cc << "	} catch (const angru::system::exception::error &e) {" << '\n';
  out_cc << "			LOG_ERROR << e.what();" << '\n';
  out_cc << "	}" << '\n';
  out_cc << "	LOG_INFO << \"Connected to database: \" << C.dbname();" << '\n';
  out_cc << "	pqxx::work W(C);" << '\n';
  out_cc << "	C.prepare(\"update\", \"UPDATE " << table_name << "s SET \\" << '\n';
  i=2;
  field_added=0;
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "id"){
      continue;
    }
    if(itr->second == "created_at"){
      continue;
    }
    else if(itr->second == "deleted_at"){
      continue;
    }
    else if(itr->second == "updated_at"){
      if(field_added > 0){
        out_cc << ", \\" << '\n';
      }
      out_cc << "													" << itr->second << " = now()";
      field_added++;
      continue;
    }
    else{
      if(field_added > 0){
        out_cc << ", \\" << '\n';
      }
      out_cc << "													" << itr->second << " = $" << i;
    }
    field_added++;
    i++;
  }
  out_cc << "	WHERE id = $1\");" << '\n';
  out_cc << "	W.prepared(\"update\")" << '\n';
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "created_at"){
      continue;
    }
    else if(itr->second == "deleted_at"){
      continue;
    }
    else if(itr->second == "updated_at"){
      continue;
    }
    else{
      out_cc << "                 ("<< itr->second <<")"<< '\n';
    }
  }
  out_cc << "         .exec();" << '\n';
  out_cc << "	W.commit();" << '\n';
  out_cc << "}" << '\n';
  out_cc << '\n';
  out_cc << "void " << class_name << "::Delete" << entity_name << "(int id){" << '\n';
  out_cc << "	pqxx::connection C(angru::wrapper::Postgresql::connection_string());" << '\n';
  out_cc << "	try {" << '\n';
  out_cc << "		if (C.is_open()) {" << '\n';
  out_cc << "			 LOG_INFO << \"Opened database successfully: \" << C.dbname();" << '\n';
  out_cc << "		} else {" << '\n';
  out_cc << "			 LOG_ERROR << \"Can't open database: \" << C.dbname();" << '\n';
  out_cc << "		}" << '\n';
  out_cc << "		C.disconnect ();" << '\n';
  out_cc << "	 } catch (const angru::system::exception::error &e) {" << '\n';
  out_cc << "			LOG_ERROR << e.what();" << '\n';
  out_cc << "	 }" << '\n';
  out_cc << "	 LOG_INFO << \"Connected to database: \" << C.dbname();" << '\n';
  out_cc << "	 pqxx::work W(C);" << '\n';
  out_cc << "	 C.prepare(\"update\", \"UPDATE " << table_name << "s SET \\" << '\n';
  out_cc << "												deleted_at = now()  \\" << '\n';
  out_cc << "												WHERE id = $1\");" << '\n';
  out_cc << "   W.prepared(\"update\")(id).exec();" << '\n';
  out_cc << "   W.commit();" << '\n';
  out_cc << "  }" << '\n';
  out_cc << '\n';
  out_cc << "} // model" << '\n';
  out_cc << "} // mvc" << '\n';
  out_cc << "} // angru" << '\n';
  //----------------------------------------------------------------------------
  out_cc.close();

  return;
}

void controllerGenerator(std::string table_name_single, std::string entity_name,
  std::vector<std::pair<std::string, std::string>> fields)
{
  std::string table_name = table_name_single;
  std::string file_name = table_name_single + "_controller";
  std::string file_model_name = table_name_single + "_model";
  std::string class_name = entity_name + "Controller";
  std::string guard = "ANGRU_" + file_name + "_H_"; boost::to_upper(guard);
  int field_added=0;
  std::vector<std::pair<std::string, std::string>>::iterator itr;
  std::string path_h= "/home/masoud/Projects/angru/generated/controller_h/" + file_name + ".h";

  std::ofstream out_h(path_h);
  //-----------------------------    .h     -------------------------------
  out_h << "#ifndef " << guard << '\n';
  out_h << "#define " << guard << '\n';
  out_h << '\n';
  out_h << "#include <iostream>" << '\n';
  out_h << "#include <vector>" << '\n';
  out_h << "#include <pqxx/pqxx>" << '\n';
  out_h << '\n';
  out_h << "#include <pistache/http.h>" << '\n';
  out_h << "#include <pistache/endpoint.h>" << '\n';
  out_h << "#include <pistache/description.h>" << '\n';
  out_h << "#include <pistache/router.h>" << '\n';
  out_h << "#include <pistache/serializer/rapidjson.h>" << '\n';
  out_h << '\n';
  out_h << "namespace angru{" << '\n';
  out_h << "namespace mvc{" << '\n';
  out_h << "namespace controller{" << '\n';
  out_h << '\n';
  out_h << "class " << class_name << '\n';
  out_h << "{" << '\n';
  out_h << "public:" << '\n';
  out_h << "	" << class_name << "();" << '\n';
  out_h << "	~" << class_name << "();" << '\n';
  out_h << "	static void	doGet" << entity_name << "s(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);" << '\n';
  out_h << "	static void	doGet" << entity_name << "(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);" << '\n';
  out_h << "  static void	doDelete" << entity_name << "(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);" << '\n';
  out_h << "	static void	doAdd" << entity_name << "(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);" << '\n';
  out_h << "	static void	doUpdate" << entity_name << "(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);" << '\n';
  out_h << "};" << '\n';
  out_h << '\n';
  out_h << "} // model" << '\n';
  out_h << "} // mvc" << '\n';
  out_h << "} // angru" << '\n';
  out_h << '\n';
  out_h << "#endif // " << guard << '\n';
  //----------------------------------------------------------------------------
  out_h.close();

  std::string path_cc= "/home/masoud/Projects/angru/generated/controller_cc/" + file_name + ".cc";
  std::ofstream out_cc(path_cc);
  //-----------------------------    .cc     -------------------------------
  out_cc << "#include \"controllers/" << file_name << ".h\"" << '\n';
  out_cc << '\n';
  out_cc << "#include <iostream>" << '\n';
  out_cc << "#include <string>" << '\n';
  out_cc << '\n';
  out_cc << "#include <pqxx/pqxx>" << '\n';
  out_cc << "#include <boost/property_tree/ptree.hpp>" << '\n';
  out_cc << "#include <boost/property_tree/json_parser.hpp>" << '\n';
  out_cc << "#include \"tools/system.h\"" << '\n';
  out_cc << "#include \"tools/log.h\"" << '\n';
  out_cc << "#include \"wrappers/postgresql.h\"" << '\n';
  out_cc << "#include \"tools/security.h\"" << '\n';
  out_cc << "#include \"models/" << file_model_name << ".h\"" << '\n';
  out_cc << '\n';
  out_cc << "namespace angru{" << '\n';
  out_cc << "namespace mvc{" << '\n';
  out_cc << "namespace controller{" << '\n';
  out_cc << '\n';
  out_cc << class_name << "::" << class_name << "(){}" << '\n';
  out_cc << class_name << "::~"<< class_name << "(){}" << '\n';
  out_cc << '\n';
  out_cc << "void " << class_name << "::doGet" << entity_name << "s(const Pistache::Rest::Request& request," << '\n';
  out_cc << "  Pistache::Http::ResponseWriter response) {" << '\n';
  out_cc << "    angru::security::authorization::CORS(request,response);" << '\n';
  out_cc << "    angru::security::authorization::ContentTypeJSONCheck(request,response);" << '\n';
  out_cc << "    angru::security::authorization::AuthorizationCheck(request,response);" << '\n';
  out_cc << "    int page = 1;" << '\n';
  out_cc << "    std::string filter;" << '\n';
  out_cc << "    auto query = request.query();" << '\n';
  out_cc << "    if(query.has(\"page\")) {" << '\n';
  out_cc << "      auto value = query.get(\"page\").get();" << '\n';
  out_cc << "      page = std::stoi(value);" << '\n';
  out_cc << "    }" << '\n';
  out_cc << "    if(query.has(\"filter\")) {" << '\n';
  out_cc << "      auto value = query.get(\"filter\").get();" << '\n';
  out_cc << "      filter = angru::security::cryptography::decode_base64(value);" << '\n';
  out_cc << "    }" << '\n';
  out_cc << "    boost::property_tree::ptree " << table_name << "s = angru::mvc::model::" << entity_name << "Model::Get" << entity_name << "sJson(page, filter);" << '\n';
  out_cc << "    std::ostringstream oss;" << '\n';
  out_cc << "    boost::property_tree::write_json(oss, " << table_name << "s);" << '\n';
  out_cc << '\n';
  out_cc << "    std::string inifile_text = oss.str();" << '\n';
  out_cc << "    if (inifile_text.empty()) {" << '\n';
  out_cc << "      response.send(Pistache::Http::Code::Not_Found, \"" << entity_name << "s not found.\");" << '\n';
  out_cc << "    } else {" << '\n';
  out_cc << "      response.send(Pistache::Http::Code::Ok, inifile_text);" << '\n';
  out_cc << "    }" << '\n';
  out_cc << "}" << '\n';
  out_cc << '\n';
  out_cc << "void " << class_name << "::doGet" << entity_name << "(const Pistache::Rest::Request& request," << '\n';
  out_cc << "  Pistache::Http::ResponseWriter response) {" << '\n';
  out_cc << "    angru::security::authorization::CORS(request,response);" << '\n';
  out_cc << "    angru::security::authorization::ContentTypeJSONCheck(request,response);" << '\n';
  out_cc << "    angru::security::authorization::AuthorizationCheck(request,response);" << '\n';
  out_cc << "    int id = -1;" << '\n';
  out_cc << "    if (request.hasParam(\":id\")) {" << '\n';
  out_cc << "        auto value = request.param(\":id\");" << '\n';
  out_cc << "        id = value.as<int>();" << '\n';
  out_cc << "    }" << '\n';
  out_cc << "    boost::property_tree::ptree " << table_name << " = angru::mvc::model::" << entity_name << "Model::Get" << entity_name << "Json(id);" << '\n';
  out_cc << "    std::ostringstream oss;" << '\n';
  out_cc << "    boost::property_tree::write_json(oss, " << table_name << ");" << '\n';
  out_cc << '\n';
  out_cc << "    std::string inifile_text = oss.str();" << '\n';
  out_cc << '\n';
  out_cc << "    if (inifile_text.empty()) {" << '\n';
  out_cc << "      response.send(Pistache::Http::Code::Not_Found, \"" << entity_name << "s not found.\");" << '\n';
  out_cc << "    } else {" << '\n';
  out_cc << "      response.send(Pistache::Http::Code::Ok, inifile_text);" << '\n';
  out_cc << "    }" << '\n';
  out_cc << "}" << '\n';
  out_cc << '\n';
  out_cc << "void " << class_name << "::doDelete" << entity_name << "(const Pistache::Rest::Request& request," << '\n';
  out_cc << "  Pistache::Http::ResponseWriter response) {" << '\n';
  out_cc << "    angru::security::authorization::CORS(request,response);" << '\n';
  out_cc << "    angru::security::authorization::ContentTypeJSONCheck(request,response);" << '\n';
  out_cc << "    angru::security::authorization::AuthorizationCheck(request,response);" << '\n';
  out_cc << "    int id = -1;" << '\n';
  out_cc << "    if (request.hasParam(\":id\")) {" << '\n';
  out_cc << "        auto value = request.param(\":id\");" << '\n';
  out_cc << "        id = value.as<int>();" << '\n';
  out_cc << "    }" << '\n';
  out_cc << "    angru::mvc::model::" << entity_name << "Model::Delete" << entity_name << "(id);" << '\n';
  out_cc << "    response.send(Pistache::Http::Code::Ok, \"" << entity_name << " deleted.\");" << '\n';
  out_cc << "}" << '\n';
  out_cc << '\n';
  out_cc << "void " << class_name << "::doAdd" << entity_name << "(const Pistache::Rest::Request& request," << '\n';
  out_cc << "  Pistache::Http::ResponseWriter response) {" << '\n';
  out_cc << "    angru::security::authorization::CORS(request,response);" << '\n';
  out_cc << "    angru::security::authorization::ContentTypeJSONCheck(request,response);" << '\n';
  out_cc << "    angru::security::authorization::AuthorizationCheck(request,response);" << '\n';
  out_cc << "    auto body = request.body();" << '\n';
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "id"){
      continue;
    }
    else if(itr->second == "created_at"){
      continue;
    }
    else if(itr->second == "deleted_at"){
      continue;
    }
    else if(itr->second == "updated_at"){
      continue;
    }
    out_cc << "    " << itr->first << '\t' << itr->second << ";" << '\n';
  }
  out_cc << "    try" << '\n';
  out_cc << "    {" << '\n';
  out_cc << "      std::stringstream ss;" << '\n';
  out_cc << "      ss << body;" << '\n';
  out_cc << "      boost::property_tree::ptree pt;" << '\n';
  out_cc << "      boost::property_tree::read_json(ss, pt);" << '\n';
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "id"){
      continue;
    }
    else if(itr->second == "created_at"){
      continue;
    }
    else if(itr->second == "deleted_at"){
      continue;
    }
    else if(itr->second == "updated_at"){
      continue;
    }
    out_cc << "      " << itr->second << " = pt.get<" << itr->first << ">(\"" << itr->second << "\");" << '\n';
  }
  out_cc << '\n';
  out_cc << "      angru::mvc::model::" << entity_name << "Model::Add" << entity_name << "(" << '\n';
  field_added =0;
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "id"){
      continue;
    }
    else if(itr->second == "created_at"){
      continue;
    }
    else if(itr->second == "deleted_at"){
      continue;
    }
    else if(itr->second == "updated_at"){
      continue;
    }
    if(field_added > 0){
      out_cc << ", " << '\n';
    }
    out_cc << "                                                  " << itr->second;
    field_added++;
  }
  out_cc << " );" << '\n';
  out_cc << "      response.send(Pistache::Http::Code::Ok, \"" << entity_name << " added.\");" << '\n';
  out_cc << "    }" << '\n';
  out_cc << "    catch (std::exception const& e){" << '\n';
  out_cc << "      response.send(Pistache::Http::Code::Not_Found, \"" << entity_name << "s not found.\");" << '\n';
  out_cc << "    }" << '\n';
  out_cc << "}" << '\n';
  out_cc << '\n';
  out_cc << "void " << class_name << "::doUpdate" << entity_name << "(const Pistache::Rest::Request& request," << '\n';
  out_cc << "  Pistache::Http::ResponseWriter response) {" << '\n';
  out_cc << "    angru::security::authorization::CORS(request,response);" << '\n';
  out_cc << "    angru::security::authorization::ContentTypeJSONCheck(request,response);" << '\n';
  out_cc << "    angru::security::authorization::AuthorizationCheck(request,response);" << '\n';
  out_cc << "    int id = -1;" << '\n';
  out_cc << "    if (request.hasParam(\":id\")) {" << '\n';
  out_cc << "        auto value = request.param(\":id\");" << '\n';
  out_cc << "      id = value.as<int>();" << '\n';
  out_cc << "    }" << '\n';
  out_cc << "    if(id == -1){" << '\n';
  out_cc << "      response.send(Pistache::Http::Code::Not_Found, \"" << entity_name << "s not found.\");" << '\n';
  out_cc << "    }" << '\n';
  out_cc << "    auto body = request.body();" << '\n';
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "id"){
      continue;
    }
    else if(itr->second == "created_at"){
      continue;
    }
    else if(itr->second == "deleted_at"){
      continue;
    }
    else if(itr->second == "updated_at"){
      continue;
    }
    out_cc << "    " << itr->first << '\t' << itr->second << ";" << '\n';
  }
  out_cc << "   try" << '\n';
  out_cc << "    {" << '\n';
  out_cc << "      std::stringstream ss;" << '\n';
  out_cc << "      ss << body;" << '\n';
  out_cc << "      boost::property_tree::ptree pt;" << '\n';
  out_cc << "      boost::property_tree::read_json(ss, pt);" << '\n';
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "id"){
      continue;
    }
    else if(itr->second == "created_at"){
      continue;
    }
    else if(itr->second == "deleted_at"){
      continue;
    }
    else if(itr->second == "updated_at"){
      continue;
    }
    out_cc << "      " << itr->second << " = pt.get<" << itr->first << ">(\"" << itr->second << "\");" << '\n';
  }
  out_cc << "      angru::mvc::model::" << entity_name << "Model::Update" << entity_name << "(" << '\n';
  field_added =0;
  for (itr = fields.begin(); itr != fields.end(); ++itr) {
    if(itr->second == "created_at"){
      continue;
    }
    else if(itr->second == "deleted_at"){
      continue;
    }
    else if(itr->second == "updated_at"){
      continue;
    }
    if(field_added > 0){
      out_cc << ", " << '\n';
    }
    out_cc << "                                                  " << itr->second;
    field_added++;
  }
  out_cc << " );" << '\n';
  out_cc << "      response.send(Pistache::Http::Code::Ok, \"" << entity_name << "s updated.\");" << '\n';
  out_cc << "    }" << '\n';
  out_cc << "    catch (std::exception const& e){" << '\n';
  out_cc << "      response.send(Pistache::Http::Code::Not_Found, \"" << entity_name << "s not found.\");" << '\n';
  out_cc << "    }" << '\n';
  out_cc << " }" << '\n';
  out_cc << '\n';
  out_cc << "} // model" << '\n';
  out_cc << "} // mvc" << '\n';
  out_cc << "} // angru" << '\n';
  //----------------------------------------------------------------------------
  out_cc.close();

  return;
}

void routerGenerator(std::string table_name_single, std::string entity_name)
{
  std::string table_name = table_name_single;
  std::string file_name = table_name_single + "_router";
  std::string class_name = entity_name + "Controller";

  std::vector<std::pair<std::string, std::string>>::iterator itr;
  std::string path_h= "/home/masoud/Projects/angru/generated/router/" + file_name + ".r";
  std::ofstream out_r(path_h);
  //-----------------------------    .r     -------------------------------
  out_r << '\n';
  out_r << "	Get(router, \"/" << table_name << "s\", bind(&" << class_name << "::doGet" << entity_name << "s));" << '\n';
  out_r << "	Get(router, \"/" << table_name << "s/:id\", bind(&" << class_name << "::doGet" << entity_name << "));" << '\n';
  out_r << "	Delete(router, \"/" << table_name << "s/:id\", bind(&" << class_name << "::doDelete" << entity_name << "));" << '\n';
  out_r << "  Post(router, \"/" << table_name << "s\", bind(&" << class_name << "::doAdd" << entity_name << "));" << '\n';
  out_r << "	Put(router, \"/" << table_name << "s/:id\", bind(&" << class_name << "::doUpdate" << entity_name << "));" << '\n';
  out_r << '\n';
  //----------------------------------------------------------------------------
  out_r.close();
}
} // namespace generator
} // namespace tools
} // namespace angru
