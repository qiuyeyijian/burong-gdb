

#ifndef CPPNET_SOCKET_SOCKET_INTERFACE
#define CPPNET_SOCKET_SOCKET_INTERFACE

#include <cstdint>
#include <memory>
#include <unordered_map>

#include "common/network/address.h"

namespace burongnet {

class Address;
class BuRongNetBase;
class Dispatcher;
class EventActions;
class Socket {
 public:
  Socket() : _sock(0) {}
  Socket(uint64_t sock) : _sock(sock) {}
  virtual ~Socket() {}

  void SetSocket(const uint64_t& sock) { _sock = sock; }
  uint64_t GetSocket() { return _sock; }

  void SetAddress(const Address& addr) { _addr = addr; }
  const Address& GetAddress() const { return _addr; }

  void SetBuRongNetBase(std::shared_ptr<BuRongNetBase> base) { _cppnet_base = base; }
  const std::shared_ptr<BuRongNetBase> GetBuRongNetBase() const {
    return _cppnet_base.lock();
  }

  void SetEventActions(std::weak_ptr<EventActions> actions) {
    _event_actions = actions;
  }
  const std::shared_ptr<EventActions> GetEventActions() const {
    return _event_actions.lock();
  }

  void SetDispatcher(std::shared_ptr<Dispatcher> dis) { _dispatcher = dis; }
  std::shared_ptr<Dispatcher> GetDispatcher() { return _dispatcher.lock(); }

 protected:
  uint64_t _sock;
  Address _addr;

  std::weak_ptr<BuRongNetBase> _cppnet_base;
  std::weak_ptr<EventActions> _event_actions;
  std::weak_ptr<Dispatcher> _dispatcher;

  static thread_local std::unordered_map<uint64_t, std::shared_ptr<Socket>>
      __all_socket_map;
};

}  // namespace burongnet

#endif