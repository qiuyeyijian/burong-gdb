

#include "socket/connect_socket.h"

#include <errno.h>

#include <string>

#include "common/alloter/pool_alloter.h"
#include "common/log/log.h"
#include "common/network/address.h"
#include "common/network/io_handle.h"
#include "common/network/socket.h"
#include "common/os/convert.h"
#include "cppnet_base.h"
#include "cppnet_config.h"
#include "event/action_interface.h"
#include "event/event_interface.h"
#include "socket/rw_socket.h"

#define WSAEWOULDBLOCK 10035  // windows error

namespace burongnet {

ConnectSocket::ConnectSocket() : _accept_event(nullptr) {}

ConnectSocket::~ConnectSocket() {}

bool ConnectSocket::Bind(const std::string& ip, uint16_t port) {
  if (_sock == 0) {
    auto ret = OsHandle::TcpSocket(Address::IsIpv4(ip));
    if (ret._return_value < 0) {
      LOG_ERROR("create socket failed. errno:%d, info:%s", ret._errno,
                ErrnoInfo(ret._errno));
      return false;
    }
    _sock = ret._return_value;
  }
  _addr.SetType(Address::IsIpv4(ip) ? AT_IPV4 : AT_IPV6);
  _addr.SetIp(ip);
  _addr.SetAddrPort(port);

  auto ret = OsHandle::Bind(_sock, _addr);

#ifndef __win__  // WEPOLL don't support reuse_port
  if (ret._return_value < 0 && __reuse_port) {
    LOG_FATAL("bind socket filed! error:%d, info:%s", ret._errno,
              ErrnoInfo(ret._errno));
    OsHandle::Close(_sock);
    return false;
  }
#endif

  return true;
}

bool ConnectSocket::Listen() {
  auto ret = OsHandle::Listen(_sock);
#ifndef __win__  // WEPOLL don't support reuse_port
  if (ret._return_value < 0 && __reuse_port) {
    LOG_FATAL("listen socket filed! error:%d, info:%s", ret._errno,
              ErrnoInfo(ret._errno));
    OsHandle::Close(_sock);
    return false;
  }
#endif

  // set the socket noblocking
  SocketNoblocking(_sock);

  Accept();

  return true;
}

void ConnectSocket::Accept() {
  if (!_accept_event) {
    _accept_event = new Event();
    _accept_event->SetSocket(shared_from_this());
  }
  __all_socket_map[_sock] = shared_from_this();
  auto actions = GetEventActions();
  if (actions) {
    actions->AddAcceptEvent(_accept_event);
  }
}

void ConnectSocket::Close() {
  // TODO
}

void ConnectSocket::OnAccept() {
  while (true) {
    std::shared_ptr<AlloterWrap> alloter =
        std::make_shared<AlloterWrap>(MakePoolAlloterPtr());
    Address address;
    // may get more than one connections
    auto ret = OsHandle::Accept(_sock, address);
    if (ret._return_value < 0) {
      if (ret._errno == EAGAIN || ret._errno == WSAEWOULDBLOCK) {
        break;
      }
      LOG_ERROR("accept socket filed! errno:%d, info:%s", ret._errno,
                ErrnoInfo(ret._errno));
      break;
    }

    auto cppnet_base = _cppnet_base.lock();
    if (!cppnet_base) {
      return;
    }

    // set the socket noblocking
    SocketNoblocking(ret._return_value);

    // create a new socket.
    auto sock = MakeRWSocket(ret._return_value, alloter);

    sock->SetListenPort(_addr.GetAddrPort());
    sock->SetBuRongNetBase(cppnet_base);
    sock->SetEventActions(_event_actions);
    sock->SetAddress(std::move(address));
    sock->SetDispatcher(GetDispatcher());

    __all_socket_map[ret._return_value] = sock;

    // call accept call back function
    cppnet_base->OnAccept(sock);

    // start read
    sock->Read();
  }
}

std::shared_ptr<ConnectSocket> MakeConnectSocket() {
  return std::make_shared<ConnectSocket>();
}

}  // namespace burongnet