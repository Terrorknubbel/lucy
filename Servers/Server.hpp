#ifndef Server_hpp
#define Server_hpp

#include "../Sockets/ListeningSocket.hpp"
#include "RouteTrie.hpp"
#include "RespondHandler.hpp"
#include "MiddlewareHandler.hpp"
#include <functional>

namespace lucy
{
typedef std::function<void(const Request&, Response&)> Handler;
class Server
{
private:
  ListeningSocket *listening_socket;
  char buffer[65536] = {0};
  int client_fd;
  void acceptor();
  void responder();
  std::string raw_request;
  std::string http_response;
  RouteTrie trie;
  Request request;
  MiddlewareHandler middlewareHandler;
public:
  Server();
  ~Server();
  void listen(const int port, std::function<void()> callback);
  void use(Middleware middleware);
  void get(const std::string& path, Handler handler);
};
}

#endif /* Server_hpp */
