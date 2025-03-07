#include "RequestHandler.hpp"

lucy::RequestHandler::RequestHandler(RouteTrie &trie) {
  this->trie = trie;
}

lucy::Request lucy::RequestHandler::call(std::string &raw_request)
{
  Request request(raw_request);
  request.handler = trie.find(request.method, request.path);
  return request;
}
