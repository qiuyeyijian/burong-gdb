

#ifndef INCLUDE_CPPNET
#define INCLUDE_CPPNET

#include <memory>
#include <string>

#include "cppnet_buffer.h"
#include "cppnet_socket.h"
#include "cppnet_type.h"

namespace burongnet {

class BuRongNetBase;
// cppnet instance
class BuRongNet {
 public:
  BuRongNet();
  ~BuRongNet();
  // common
  // init cppnet library.
  // thread_num : the number of running threads.
  void Init(int32_t thread_num = 0);
  void Destory();

  // thread join
  void Join();

  // must set callback before listen
  void SetReadCallback(const read_call_back& cb);
  void SetWriteCallback(const write_call_back& cb);
  void SetDisconnectionCallback(const connect_call_back& cb);

  // if use socket timer, set it
  void SetTimerCallback(const timer_call_back& cb);

  // return timer id
  uint64_t AddTimer(int32_t interval, const user_timer_call_back& cb,
                    void* param = nullptr, bool always = false);
  void RemoveTimer(uint64_t timer_id);

  // server
  void SetAcceptCallback(const connect_call_back& cb);
  bool ListenAndAccept(const std::string& ip, uint16_t port);

  // client
  void SetConnectionCallback(const connect_call_back& cb);
  bool Connection(const std::string& ip, uint16_t port);

 private:
  std::shared_ptr<BuRongNetBase> _cppnet_base;
};

}  // namespace burongnet

#endif