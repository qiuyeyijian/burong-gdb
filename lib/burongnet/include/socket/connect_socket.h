

#ifndef CPPNET_SOCKET_CONNECT_SOCKET
#define CPPNET_SOCKET_CONNECT_SOCKET

#include <memory>

#include "socket/socket_interface.h"

namespace burongnet {

class Event;
class ConnectSocket : public Socket,
                      public std::enable_shared_from_this<ConnectSocket> {
 public:
  ConnectSocket();
  virtual ~ConnectSocket();

  virtual bool Bind(const std::string& ip, uint16_t port);
  virtual bool Listen();
  virtual void Accept();
  virtual void Close();

  virtual void OnAccept();

 private:
  Event* _accept_event;
};

std::shared_ptr<ConnectSocket> MakeConnectSocket();

}  // namespace burongnet

#endif