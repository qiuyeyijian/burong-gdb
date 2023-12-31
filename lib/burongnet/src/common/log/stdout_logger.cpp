

#include "common/log/stdout_logger.h"

#include <iostream>

namespace burongnet {

StdoutLogger::StdoutLogger() {}

StdoutLogger::~StdoutLogger() {}

void StdoutLogger::Debug(std::shared_ptr<Log>& log) {
  {
    std::unique_lock<std::mutex> lock(_mutex);
    std::cout << log->_log << std::endl;
  }
  Logger::Debug(log);
}

void StdoutLogger::Info(std::shared_ptr<Log>& log) {
  {
    std::unique_lock<std::mutex> lock(_mutex);
    std::cout << log->_log << std::endl;
  }
  Logger::Info(log);
}

void StdoutLogger::Warn(std::shared_ptr<Log>& log) {
  {
    std::unique_lock<std::mutex> lock(_mutex);
    std::cout << log->_log << std::endl;
  }
  Logger::Warn(log);
}

void StdoutLogger::Error(std::shared_ptr<Log>& log) {
  {
    std::unique_lock<std::mutex> lock(_mutex);
    std::cerr << log->_log << std::endl;
  }
  Logger::Error(log);
}

void StdoutLogger::Fatal(std::shared_ptr<Log>& log) {
  {
    std::unique_lock<std::mutex> lock(_mutex);
    std::cerr << log->_log << std::endl;
  }
  Logger::Fatal(log);
}

}  // namespace burongnet