#include "tools/data_generator_factory.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <experimental/filesystem>

#include "models/aggrigator_model.h"

namespace angru{
namespace tools{
namespace factory{

void GenerateFakeData(){
  GenerateAggrigator();
  return;
}

std::string GenerateRandomAlphaNum(const int minlen, const int maxlen) {
    static const char alphanum[] =
        "123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string random_string;
    int len = rand()%((maxlen - minlen) + 1) + maxlen;
    char ch;
    for (int i = 0; i < len; ++i) {
        ch = alphanum[rand() % (sizeof(alphanum) - 1)];
        random_string = random_string + ch;
    }
    return random_string;
}
std::string GenerateRandomAlpha(const int minlen, const int maxlen) {
    static const char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string random_string;
    int len = rand()%((maxlen - minlen) + 1) + maxlen;
    char ch;
    for (int i = 0; i < len; ++i) {
        ch = alphanum[rand() % (sizeof(alphanum) - 1)];
        random_string = random_string + ch;
    }
    return random_string;
}
std::string GenerateRandomNum(const int minlen, const int maxlen) {
    static const char alphanum[] =  "0123456789";
    std::string random_string;
    int len = rand()%((maxlen - minlen) + 1) + maxlen;
    char ch;
    for (int i = 0; i < len; ++i) {
        ch = alphanum[rand() % (sizeof(alphanum) - 1)];
        random_string = random_string + ch;
    }
    return random_string;
}

void GenerateAggrigator(){
  int count = 300;
  std::string	name;
  std::string	title;
  std::string	code;
  std::string	phone;
  std::string	email;
  std::string created_by = "9979027d-1672-4108-95a4-eb5d346545a0"; //zeus
  std::string	details;
  int	status;
  int	situation;
  std::string	description;

  std::cout << "aggrigator ";
  for (int i = 0; i < count; i++) {
    name = GenerateRandomAlpha(10, 15);
    title = GenerateRandomAlpha(5, 10);
    code = GenerateRandomNum(5, 10);
    phone = GenerateRandomNum(12, 12);
    email = "info@" + name + ".com";
    details = "{}";
    status = rand()%2;
    situation = 0;
    description = GenerateRandomAlpha(10, 30);

    angru::mvc::model::AggrigatorModel::AddAggrigator(
                                                      name,
                                                      title,
                                                      code,
                                                      phone,
                                                      email,
                                                      created_by,
                                                      details,
                                                      status,
                                                      situation,
                                                      description );
    std::cout << ".";
  }
 }

} // namespace factory
} // namespace tools
} // namespace angru
