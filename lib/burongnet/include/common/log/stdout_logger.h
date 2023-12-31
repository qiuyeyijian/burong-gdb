

#ifndef QUIC_COMMON_LOG_STDOUT_LOGGER
#define QUIC_COMMON_LOG_STDOUT_LOGGER

#include <mutex>

#include "common/log/logger_interface.h"

namespace burongnet {

class StdoutLogger : public Logger {
 public:
  StdoutLogger();
  ~StdoutLogger();

  void Debug(std::shared_ptr<Log>& log);
  void Info(std::shared_ptr<Log>& log);
  void Warn(std::shared_ptr<Log>& log);
  void Error(std::shared_ptr<Log>& log);
  void Fatal(std::shared_ptr<Log>& log);

 private:
  std::mutex _mutex;
};

}  // namespace burongnet

#endif