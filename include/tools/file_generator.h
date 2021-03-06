#ifndef ANGRU_FILE_GENERATOR_H_
#define ANGRU_FILE_GENERATOR_H_

namespace angru{
namespace tools{
namespace generator{

void modelGenerator(std::string table_name_singl, std::string entity_name, std::vector<std::pair<std::string, std::string>> fields);
void controllerGenerator(std::string table_name_singl, std::string entity_name, std::vector<std::pair<std::string, std::string>> fields);
void routerGenerator(std::string table_name_singl, std::string entity_name);

} // namespace generator
} // namespace tools
} // namespace angru

#endif // ANGRU_FILE_GENERATOR_H_
