#include "tools/file_generator_factory.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <experimental/filesystem>

#include "tools/file_generator.h"

namespace angru{
namespace tools{
namespace factory{

void generate()
{
  std::string file_name= "product_model";
  std::string entity_name="Product";
  std::string class_name="ProductModel";
  // empty map container
  //std::multimap<std::string, std::string> fields;
  std::vector<std::pair<std::string, std::string>> fields;

  // insert elements in random order
  fields.push_back(std::pair<std::string, std::string>("int", "id"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "title"));
  fields.push_back(std::pair<std::string, std::string>("float", "price"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "tags"));
  fields.push_back(std::pair<std::string, std::string>("bool", "expirable"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "details"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "name"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "code"));
  fields.push_back(std::pair<std::string, std::string>("bool", "active"));
  fields.push_back(std::pair<std::string, std::string>("bool", "taxable"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "description"));

  angru::tools::generator::modelGenerator(file_name, entity_name, class_name, fields);
  return;
}

} // namespace factory
} // namespace tools
} // namespace angru
