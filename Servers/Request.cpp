#include "Request.hpp"
#include "RouteTrie.hpp"

lucy::Request::Request() {}

lucy::Request::Request(std::string &raw_request, RouteTrie &trie) {
  parse(raw_request);
  handler = trie.find(method, path);
}

void lucy::Request::parse(std::string &raw_request) {
  std::istringstream requestStream(raw_request);
  std::string line;

  std::string raw_path;

  if (std::getline(requestStream, line)) {
    std::istringstream lineStream(line);
    lineStream >> method >> raw_path >> httpVersion;
  }

  parsePath(raw_path);

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

void lucy::Request::parsePath(std::string &raw_path) {
  size_t query_start = raw_path.find('?');
  path = (query_start == std::string::npos) ? raw_path : raw_path.substr(0, query_start);

  if (query_start == std::string::npos) {
    return;
  }

  std::string query = raw_path.substr(query_start + 1);
  size_t start = 0;
  size_t amp_pos = 0;

  while (start < query.length()) {
    amp_pos = query.find("&", start);

    if (amp_pos == std::string::npos) {
      amp_pos = query.length();
    }

    std::string pair = query.substr(start, amp_pos - start);

    size_t eq_pos = pair.find("=");

    if (eq_pos != std::string::npos) {
      std::string key = pair.substr(0, eq_pos);
      std::string value = pair.substr(eq_pos + 1);
      params[key] = value;
    } else if (!pair.empty()) {
      params[pair] = "";
    }

    start = amp_pos + 1;
  }
}
