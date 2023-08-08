

#ifndef CPPNET_EVENT_TIMER_EVENT
#define CPPNET_EVENT_TIMER_EVENT

#include <atomic>
#include <memory>

#include "common/timer/timer_slot.h"
#include "cppnet_type.h"
#include "event/event_interface.h"

namespace burongnet {

class TimerEvent : public Event, public TimerSlot {
 public:
  TimerEvent() : _timer_id(0) {}
  ~TimerEvent() {}

  void SetTimerCallBack(const user_timer_call_back& cb, void* param);

  void OnTimer();

 private:
  uint64_t _timer_id;
  user_timer_call_back _timer_cb;
};

}  // namespace burongnet

#endif