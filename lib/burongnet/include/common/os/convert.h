

#ifndef COMMON_OS_CONVERT
#define COMMON_OS_CONVERT

#include <cstdint>

namespace burongnet {

void Localtime(const uint64_t* time, void* out_tm);

char* ErrnoInfo(uint32_t err);

}  // namespace burongnet

#endif