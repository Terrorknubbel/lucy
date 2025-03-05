#include "ListeningSocket.hpp"

lucy::ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int backlog) :
BindingSocket(domain, service, protocol, port, interface) {
  int listening = listen(get_sock(), backlog);
  test_connection(listening);
};
