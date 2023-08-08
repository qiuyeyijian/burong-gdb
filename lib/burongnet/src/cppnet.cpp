

#include "cppnet.h"

#include "common/log/file_logger.h"
#include "common/log/log.h"
#include "common/log/stdout_logger.h"
#include "cppnet_base.h"
#include "cppnet_config.h"

namespace burongnet {

BuRongNet::BuRongNet() {}

BuRongNet::~BuRongNet() {
  if (_cppnet_base) {
    _cppnet_base->Dealloc();
  }
}

void BuRongNet::Init(int32_t thread_num) {
  if (!_cppnet_base) {
    _cppnet_base = std::make_shared<BuRongNetBase>();

  } else {
    return;
  }

  _cppnet_base->Init(thread_num);
  if (__print_log) {
    std::shared_ptr<Logger> file_log =
        std::make_shared<FileLogger>(__log_file_name);
    std::shared_ptr<Logger> std_log = std::make_shared<StdoutLogger>();
    file_log->SetLogger(std_log);
    LOG_SET(file_log);
    LOG_SET_LEVEL((LogLevel)__log_level);
  } else {
    LOG_SET_LEVEL(LL_NULL);
  }
}

void BuRongNet::Destory() { _cppnet_base->Dealloc(); }

void BuRongNet::Join() { _cppnet_base->Join(); }

void BuRongNet::SetReadCallback(const read_call_back& cb) {
  _cppnet_base->SetReadCallback(cb);
}

void BuRongNet::SetWriteCallback(const write_call_back& cb) {
  _cppnet_base->SetWriteCallback(cb);
}

void BuRongNet::SetDisconnectionCallback(const connect_call_back& cb) {
  _cppnet_base->SetDisconnectionCallback(cb);
}

void BuRongNet::SetTimerCallback(const timer_call_back& cb) {
  _cppnet_base->SetTimerCallback(cb);
}

uint64_t BuRongNet::AddTimer(int32_t interval, const user_timer_call_back& cb,
                          void* param, bool always) {
  return _cppnet_base->AddTimer(interval, cb, param, always);
}

void BuRongNet::RemoveTimer(uint64_t timer_id) {
  _cppnet_base->RemoveTimer(timer_id);
}

void BuRongNet::SetAcceptCallback(const connect_call_back& cb) {
  _cppnet_base->SetAcceptCallback(cb);
}

bool BuRongNet::ListenAndAccept(const std::string& ip, uint16_t port) {
  return _cppnet_base->ListenAndAccept(ip, port);
}

void BuRongNet::SetConnectionCallback(const connect_call_back& cb) {
  _cppnet_base->SetConnectionCallback(cb);
}

bool BuRongNet::Connection(const std::string& ip, uint16_t port) {
  return _cppnet_base->Connection(ip, port);
}

}  // namespace burongnet