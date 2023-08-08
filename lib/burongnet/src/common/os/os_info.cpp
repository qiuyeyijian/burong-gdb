

#include "common/os/os_info.h"

#include <thread>

uint32_t burongnet::GetCpuNum() { return std::thread::hardware_concurrency(); }