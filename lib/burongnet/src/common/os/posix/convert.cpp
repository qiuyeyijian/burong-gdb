
#include "burongnet.h"
#if BURONGNET_API_POSIX
#include "common/os/convert.h"

#include <cstring>
#include <ctime>

namespace burongnet {

void Localtime(const uint64_t* time, void* out_tm) {
  ::localtime_r((time_t*)time, (tm*)out_tm);
}

char* ErrnoInfo(uint32_t err) { return strerror(err); }

}  // namespace burongnet
#endif