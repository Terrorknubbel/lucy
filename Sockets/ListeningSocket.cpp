#include "ListeningSocket.hpp"
#include <unistd.h>

lucy::ListeningSocket::ListeningSocket() {}

lucy::ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int backlog)
{
  address.sin_family = domain;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = htonl(interface);

  server_fd = socket(domain, service, protocol);
  if (server_fd < 0) {
    perror("Failed to create socket");
    exit(EXIT_FAILURE);
  }

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("Failed to bind socket");
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, backlog) < 0) {
    perror("Failed to listen on socket");
    exit(EXIT_FAILURE);
  }
}

struct sockaddr_in lucy::ListeningSocket::get_address()
{
  return address;
}

int lucy::ListeningSocket::get_server_fd()
{
  return server_fd;
}
