#ifndef ListeningSocket_hpp
#define ListeningSocket_hpp

#include <stdio.h>
#include "BindingSocket.hpp"

namespace lucy
{
class ListeningSocket : public BindingSocket
{
public:
ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int backlog);
};
}

#endif /* ListeningSocket_hpp */
