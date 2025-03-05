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
  ListeningSocket *socket;
  char buffer[65536] = {0};
  int new_socket;
  void acceptor();
  void handler();
  void responder();
  std::string response_content;
  RouteTrie trie;
public:
  Server();
  ~Server();
  void launch();
  void Get(const std::string& path, Handler handler);
};
}

#endif /* Server_hpp */
