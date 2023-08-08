

#include "common/alloter/normal_alloter.h"

#include <cstdlib>
#include <cstring>  //for memset

namespace burongnet {

NormalAlloter::NormalAlloter() {}

NormalAlloter::~NormalAlloter() {}

void* NormalAlloter::Malloc(uint32_t size) {
  void* ret = malloc((size_t)size);
  if (!ret) {
    throw "not enough memory";
    return nullptr;
  }

  return ret;
}

void* NormalAlloter::MallocAlign(uint32_t size) { return Malloc(Align(size)); }

void* NormalAlloter::MallocZero(uint32_t size) {
  void* ret = Malloc(size);
  if (ret) {
    memset(ret, 0, size);
  }
  return ret;
}

void NormalAlloter::Free(void*& data, uint32_t len) {
  free(data);
  data = nullptr;
}

std::shared_ptr<NormalAlloter> MakeNormalAlloterPtr() {
  return std::make_shared<NormalAlloter>();
}

}  // namespace burongnet