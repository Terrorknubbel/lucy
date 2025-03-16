#ifndef ListeningSocket_hpp
#define ListeningSocket_hpp

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace lucy {
class ListeningSocket {
private:
  struct sockaddr_in address;
  int server_fd;
  int client_fd;

public:
  ListeningSocket();
  ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int backlog);
  struct sockaddr_in get_address();
  int get_server_fd();
};
} // namespace lucy

#endif /* ListeningSocket_hpp */
