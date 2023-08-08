

#ifndef COMMON_TIMER_TIMER
#define COMMON_TIMER_TIMER

#include <memory>

#include "common/timer/timer_interface.h"

namespace burongnet {

std::shared_ptr<Timer> MakeTimer1Sec();

std::shared_ptr<Timer> MakeTimer1Min();

std::shared_ptr<Timer> MakeTimer1Hour();

}  // namespace burongnet

#endif