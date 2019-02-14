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
  std::string table_name_single ="";
  std::string entity_name="";
  std::vector<std::pair<std::string, std::string>> fields;

  // table_name_single = "product";
  // entity_name="Product";
  // fields.clear();
  // fields.push_back(std::pair<std::string, std::string>("int", "id"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "name"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "title"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "code"));
  // fields.push_back(std::pair<std::string, std::string>("float", "price"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "created_at"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "deleted_at"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "updated_at"));
  // fields.push_back(std::pair<std::string, std::string>("bool", "expirable"));
  // fields.push_back(std::pair<std::string, std::string>("bool", "taxable"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "tags"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "details"));
  // fields.push_back(std::pair<std::string, std::string>("int", "status"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "description"));
  // angru::tools::generator::modelGenerator(table_name_single,entity_name, fields);
  // angru::tools::generator::controllerGenerator(table_name_single, entity_name, fields);
  // angru::tools::generator::routerGenerator(table_name_single, entity_name);
  //
  // table_name_single = "product_document";
  // entity_name="ProductDocument";
  // fields.clear();
  // fields.push_back(std::pair<std::string, std::string>("int", "id"));
  // fields.push_back(std::pair<std::string, std::string>("int", "product_id"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "name"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "title"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "path"));
  // fields.push_back(std::pair<std::string, std::string>("float", "size"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "created_at"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "deleted_at"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "updated_at"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "tags"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "details"));
  // fields.push_back(std::pair<std::string, std::string>("int", "status"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "description"));
  // angru::tools::generator::modelGenerator(table_name_single,entity_name, fields);
  // angru::tools::generator::controllerGenerator(table_name_single, entity_name, fields);
  // angru::tools::generator::routerGenerator(table_name_single, entity_name);

  // table_name_single = "user";
  // entity_name="User";
  // fields.clear();
  // fields.push_back(std::pair<std::string, std::string>("std::string", "id"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "first_name"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "middle_name"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "last_name"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "username"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "email"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "password"));
  // fields.push_back(std::pair<std::string, std::string>("int", "type"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "created_by"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "deleted_by"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "updated_by"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "created_at"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "deleted_at"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "updated_at"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "details"));
  // fields.push_back(std::pair<std::string, std::string>("int", "status"));
  // fields.push_back(std::pair<std::string, std::string>("int", "situation"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "description"));
  // angru::tools::generator::modelGenerator(table_name_single,entity_name, fields);
  // angru::tools::generator::controllerGenerator(table_name_single, entity_name, fields);
  // angru::tools::generator::routerGenerator(table_name_single, entity_name);
  //
  table_name_single = "mobile_operator";
  entity_name="MobileOperator";
  fields.clear();
  fields.push_back(std::pair<std::string, std::string>("std::string", "id"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "name"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "title"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "code"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "phone"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "email"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "created_by"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "deleted_by"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "updated_by"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "created_at"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "deleted_at"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "updated_at"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "details"));
  fields.push_back(std::pair<std::string, std::string>("int", "status"));
  fields.push_back(std::pair<std::string, std::string>("int", "situation"));
  fields.push_back(std::pair<std::string, std::string>("std::string", "description"));
  angru::tools::generator::modelGenerator(table_name_single,entity_name, fields);
  angru::tools::generator::controllerGenerator(table_name_single, entity_name, fields);
  angru::tools::generator::routerGenerator(table_name_single, entity_name);
  //
  // table_name_single = "aggrigator";
  // entity_name="Aggrigator";
  // fields.clear();
  // fields.push_back(std::pair<std::string, std::string>("std::string", "id"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "name"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "title"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "code"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "phone"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "email"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "created_by"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "deleted_by"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "updated_by"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "created_at"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "deleted_at"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "updated_at"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "details"));
  // fields.push_back(std::pair<std::string, std::string>("int", "status"));
  // fields.push_back(std::pair<std::string, std::string>("int", "situation"));
  // fields.push_back(std::pair<std::string, std::string>("std::string", "description"));
  // angru::tools::generator::modelGenerator(table_name_single,entity_name, fields);
  // angru::tools::generator::controllerGenerator(table_name_single, entity_name, fields);
  // angru::tools::generator::routerGenerator(table_name_single, entity_name);
  //


  return;
}

} // namespace factory
} // namespace tools
} // namespace angru
