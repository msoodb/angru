#ifndef ANGRU_DATA_GENERATOR_FACTORY_H_
#define ANGRU_DATA_GENERATOR_FACTORY_H_

namespace angru{
namespace tools{
namespace factory{

void GenerateFakeData();
std::string GenerateRandomAlphaNum(const int minlen, const int maxlen);
std::string GenerateRandomAlpha(const int minlen, const int maxlen);
std::string GenerateRandomNum(const int minlen, const int maxlen);
void GenerateAggregator();

} // namespace factory
} // namespace tools
} // namespace angru

#endif // ANGRU_DATA_GENERATOR_FACTORY_H_
