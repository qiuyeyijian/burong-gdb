

#include "common/timer/timer.h"

#include "common/timer/timer_container.h"

namespace burongnet {

std::shared_ptr<Timer> MakeTimer1Sec() {
  return std::make_shared<TimerContainer>(nullptr, TU_MILLISECOND, TU_SECOND);
}

std::shared_ptr<Timer> MakeTimer1Min() {
  auto sec_sub =
      std::make_shared<TimerContainer>(nullptr, TU_MILLISECOND, TU_SECOND);
  auto timer = std::make_shared<TimerContainer>(sec_sub, TU_SECOND, TU_MINUTE);
  sec_sub->SetRootTimer(timer);
  return timer;
}

std::shared_ptr<Timer> MakeTimer1Hour() {
  auto sec_sub =
      std::make_shared<TimerContainer>(nullptr, TU_MILLISECOND, TU_SECOND);
  auto min_sub =
      std::make_shared<TimerContainer>(sec_sub, TU_SECOND, TU_MINUTE);
  auto timer = std::make_shared<TimerContainer>(min_sub, TU_MINUTE, TU_HOUR);
  sec_sub->SetRootTimer(timer);
  min_sub->SetRootTimer(timer);

  return timer;
}

}  // namespace burongnet