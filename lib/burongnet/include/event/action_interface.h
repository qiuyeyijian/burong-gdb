

#ifndef CPPNET_EVENT_ACTION_INTERFACE
#define CPPNET_EVENT_ACTION_INTERFACE

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace burongnet {

class Timer;
class Event;
class Address;
class TimeSolt;

// net IO event interface
class EventActions {
 public:
  EventActions() {}
  virtual ~EventActions() {}

  virtual bool Init(uint32_t thread_num = 0) = 0;
  virtual bool Dealloc() = 0;

  // net IO event
  virtual bool AddSendEvent(Event* event) = 0;
  virtual bool AddRecvEvent(Event* event) = 0;
  virtual bool AddAcceptEvent(Event* event) = 0;
  virtual bool AddConnection(Event* event, Address& addr) = 0;
  virtual bool AddDisconnection(Event* event) = 0;

  virtual bool DelEvent(Event* event) = 0;
  // IO thread process
  virtual void ProcessEvent(int32_t wait_ms) = 0;
  // weak up net IO thread
  virtual void Wakeup() = 0;
};

std::shared_ptr<EventActions> MakeEventActions();

}  // namespace burongnet

#endif