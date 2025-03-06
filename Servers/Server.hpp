#ifndef Server_hpp
#define Server_hpp

#include <stdio.h>

#include "../Sockets/ListeningSocket.hpp"
#include "RouteTrie.hpp"
#include <cstring>
#include <sstream>
#include <functional>

typedef std::function<void(std::string&)> Handler;

namespace lucy
{
class Server
{
private:
  ListeningSocket *listening_socket;
  char buffer[65536] = {0};
  int client_fd;
  void acceptor();
  void handler();
  void responder();
  std::string response_content;
  RouteTrie trie;
public:
  Server();
  ~Server();
  void listen(const int port, std::function<void()> callback);
  void get(const std::string& path, Handler handler);
};
}

#endif /* Server_hpp */
