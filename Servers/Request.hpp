#ifndef Request_hpp
#define Request_hpp

#include "Response.hpp"
#include <filesystem>
#include <functional>
#include <sstream>
#include <unordered_map>

namespace lucy {
class RouteTrie;
class Request;
typedef std::function<void(const Request &, Response &)> Handler;

class Request {
private:
  void parse();
  std::string raw_request;

public:
  Request();
  Request(std::string raw_request, RouteTrie &trie);
  std::string method;
  std::filesystem::path path;
  std::string httpVersion;
  std::unordered_map<std::string, std::string> headers;
  std::string body;
  Handler *handler;
};
} // namespace lucy

#endif /* Request_hpp */
