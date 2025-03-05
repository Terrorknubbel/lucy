#ifndef BindingSocket_hpp
#define BindingSocket_hpp

#include <stdio.h>
#include "SimpleSocket.hpp"

namespace lucy
{
class BindingSocket : public SimpleSocket
{
public:
  BindingSocket(int domain, int service, int protocol, int port, u_long interface);
};
}

#endif /* BindingSocket_hpp */
