#ifndef RequestHandler_hpp
#define RequestHandler_hpp

#include "../Sockets/ListeningSocket.hpp"
#include "Request.hpp"
#include "RouteTrie.hpp"

namespace lucy
{
class RequestHandler
{
private:
  ListeningSocket *listening_socket;
  RouteTrie trie;
public:
  RequestHandler(RouteTrie &trie);
  Request call(std::string &raw_request);
};
}

#endif /* RequestHandler_hpp */
