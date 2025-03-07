#ifndef Server_hpp
#define Server_hpp

#include "../Sockets/ListeningSocket.hpp"
#include "RouteTrie.hpp"
#include "RequestHandler.hpp"
#include <functional>

typedef std::function<void(const lucy::Request&, std::string&)> Handler;

namespace lucy
{
class Server
{
private:
  ListeningSocket *listening_socket;
  char buffer[65536] = {0};
  int client_fd;
  void acceptor();
  void responder();
  std::string raw_request;
  std::string response_content;
  RouteTrie trie;
  Request request;
public:
  Server();
  ~Server();
  void listen(const int port, std::function<void()> callback);
  void get(const std::string& path, Handler handler);
};
}

#endif /* Server_hpp */
