#include "BindingSocket.hpp"

lucy::BindingSocket::BindingSocket(int domain, int service, int protocol, int port, u_long interface) :
SimpleSocket(domain, service, protocol, port, interface) {
  sockaddr_in address = get_address();
  int bound = bind(get_sock(), (struct sockaddr *)&address, sizeof(address));
  test_connection(bound);
};
