

#ifndef COMMON_UTIL_RANDOM
#define COMMON_UTIL_RANDOM

#include <cstdint>
#include <random>

namespace burongnet {

class RangeRandom {
 public:
  RangeRandom(int32_t min, int32_t max);
  ~RangeRandom();

  int32_t Random();

 private:
  static std::random_device _random;
  static std::mt19937 _engine;
  std::uniform_int_distribution<int32_t> _uniform;
};

}  // namespace burongnet

#endif