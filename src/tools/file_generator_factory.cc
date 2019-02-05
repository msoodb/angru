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
  std::string entity_name="";
  std::vector<std::pair<std::string, std::string>> fields;

  entity_name="Product";
  fields.clear();
  fields.push_back(std::pair<std::string, std::string>("int", "id"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "title"));
  fields.push_back(std::pair<std::string, std::string>("float", "price"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "created_at"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "deleted_at"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "tags"));
  fields.push_back(std::pair<std::string, std::string>("bool", "expirable"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "details"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "updated_at"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "name"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "code"));
  fields.push_back(std::pair<std::string, std::string>("bool", "active"));
  fields.push_back(std::pair<std::string, std::string>("bool", "taxable"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "description"));
  angru::tools::generator::modelGenerator(entity_name, fields);
  angru::tools::generator::controllerGenerator(entity_name, fields);
  angru::tools::generator::routerGenerator(entity_name);

  entity_name="User";
  fields.clear();
  fields.push_back(std::pair<std::string, std::string>("int", "id"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "email"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "password"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "details"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "created_at"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "deleted_at"));
  angru::tools::generator::modelGenerator(entity_name, fields);
  angru::tools::generator::controllerGenerator(entity_name, fields);
  angru::tools::generator::routerGenerator(entity_name);

  entity_name="Aggrigator";
  fields.clear();
  fields.push_back(std::pair<std::string, std::string>("int", "id"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "name"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "title"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "phone"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "email"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "created_at"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "deleted_at"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "updated_at"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "details"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "description"));
  angru::tools::generator::modelGenerator(entity_name, fields);
  angru::tools::generator::controllerGenerator(entity_name, fields);
  angru::tools::generator::routerGenerator(entity_name);


  return;
}

} // namespace factory
} // namespace tools
} // namespace angru
