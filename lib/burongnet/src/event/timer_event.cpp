

#include "event/timer_event.h"

#include "common/log/log.h"
#include "socket/rw_socket.h"

namespace burongnet {

void TimerEvent::SetTimerCallBack(const user_timer_call_back& cb, void* param) {
  _timer_cb = cb;
  SetData(param);
}

void TimerEvent::OnTimer() {
  if (GetType() & ET_USER_TIMER) {
    _timer_cb(GetData());

  } else if (GetType() & ET_TIMER) {
    auto sock = GetSocket();
    auto rw_sock = std::dynamic_pointer_cast<RWSocket>(sock);
    rw_sock->OnTimer();

  } else {
    LOG_ERROR("invalid timer type. type:%d", GetType());
  }
}

}  // namespace burongnet