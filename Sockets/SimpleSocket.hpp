#ifndef SimpleSocket_hpp
#define SimpleSocket_hpp

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

namespace lucy
{
class SimpleSocket
{
private:
  struct sockaddr_in address;
  int sock;
public:
  SimpleSocket(int domain, int service, int protocol, int port, u_long interface);
  void test_connection(int);
  struct sockaddr_in get_address();
  int get_sock();
};
}

#endif /* SimpleSocket_hpp */
