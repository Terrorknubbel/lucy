#include "Request.hpp"
#include "RouteTrie.hpp"

lucy::Request::Request() {}

lucy::Request::Request(std::string raw_request, RouteTrie &trie) {
  this->raw_request = raw_request;
  parse();
  handler = trie.find(method, path);
}

void lucy::Request::parse() {
  std::istringstream requestStream(raw_request);
  std::string line;

  if (std::getline(requestStream, line)) {
    std::istringstream lineStream(line);
    lineStream >> method >> path >> httpVersion;
  }

  while (std::getline(requestStream, line) && line != "\r") {
    std::istringstream headerStream(line);
    std::string key, value;
    if (std::getline(headerStream, key, ':')) {
      std::getline(headerStream, value);
      if (!key.empty() && !value.empty()) {
        if (value[0] == ' ') {
          value.erase(0, 1);
        }
        headers[key] = value;
      }
    }
  }

  std::stringstream bodyStream;
  bodyStream << requestStream.rdbuf();
  body = bodyStream.str();
}
