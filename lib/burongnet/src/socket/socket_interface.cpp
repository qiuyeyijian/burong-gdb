

#include "socket/socket_interface.h"

namespace burongnet {

thread_local std::unordered_map<uint64_t, std::shared_ptr<Socket>>
    Socket::__all_socket_map;

}