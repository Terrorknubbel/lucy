#ifndef ListeningSocket_hpp
#define ListeningSocket_hpp

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

namespace lucy
{
class ListeningSocket
{
private:
  struct sockaddr_in address;
  int server_fd;
  int client_fd;
public:
  ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int backlog);
  int await_connection();
  struct sockaddr_in get_address();
  int get_server_fd();
};
}

#endif /* ListeningSocket_hpp */
