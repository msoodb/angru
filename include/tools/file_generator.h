#ifndef ANGRU_FILE_GENERATOR_H_
#define ANGRU_FILE_GENERATOR_H_

namespace angru{
namespace tools{
namespace generator{

void modelGenerator(std::string file_name, std::string entity_name,
  std::string class_name, std::vector<std::pair<std::string, std::string>> fields);

} // namespace generator
} // namespace tools
} // namespace angru

#endif // ANGRU_FILE_GENERATOR_H_
