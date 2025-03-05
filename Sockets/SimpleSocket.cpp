#include "SimpleSocket.hpp"

lucy::SimpleSocket::SimpleSocket(int domain, int service, int protocol, int port, u_long interface)
{
  address.sin_family = domain;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = htonl(interface);

  sock = socket(domain, service, protocol);
  test_connection(sock);
}

void lucy::SimpleSocket::test_connection(int item_to_test)
{
  if (item_to_test < 0) {
    perror("Connection failed");
    exit(EXIT_FAILURE);
  }
}

struct sockaddr_in lucy::SimpleSocket::get_address()
{
  return address;
}

int lucy::SimpleSocket::get_sock()
{
  return sock;
}
