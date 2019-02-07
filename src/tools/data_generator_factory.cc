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
    std::cout << random_string << '\n';
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
    std::cout << random_string << '\n';
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
    std::cout << random_string << '\n';
    return random_string;
}

void GenerateAggrigator(){
  int count = 1000;
  std::string	name;
  std::string	title;
  std::string	code;
  std::string	phone;
  std::string	email;
  std::string	details;
  int	status;
  std::string	description;

  for (int i = 0; i < count; i++) {
    name = GenerateRandomAlpha(10, 20);
    title = GenerateRandomAlpha(10, 20);
    code = GenerateRandomNum(5, 10);
    phone = GenerateRandomNum(12, 12);
    email = "info@" + name + ".com";
    details = "{}";
    status = rand()%2;
    description = GenerateRandomAlpha(10, 50);

    //std::cout << name << '\n';
    angru::mvc::model::AggrigatorModel::AddAggrigator(
                            													name,
                            													title,
                            													code,
                            													phone,
                            													email,
                            													details,
                            													status,
                            													description);
  }
 }

} // namespace factory
} // namespace tools
} // namespace angru
