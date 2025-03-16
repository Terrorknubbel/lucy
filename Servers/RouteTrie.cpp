#include "RouteTrie.hpp"
#include "Request.hpp"

lucy::RouteTrie::RouteTrie() { root = std::make_unique<TrieNode>(); }

std::vector<std::string> lucy::RouteTrie::splitPath(const std::string &path) {
  std::vector<std::string> parts;
  std::stringstream ss(path);
  std::string item;
  while (std::getline(ss, item, '/')) {
    if (!item.empty()) {
      parts.push_back(item);
    }
  }
  return parts;
}

void lucy::RouteTrie::insert(const std::string &method, const std::string &path, Handler handler) {
  TrieNode *node = root.get();
  std::vector<std::string> parts = splitPath(path);

  for (const std::string &part : parts) {
    if (part[0] == ':') {
      if (!node->children.count("*")) {
        node->children["*"] = std::make_unique<TrieNode>();
      }
      node = node->children["*"].get();
    } else {
      if (!node->children.count(part)) {
        node->children[part] = std::make_unique<TrieNode>();
      }
      node = node->children[part].get();
    }
  }
  node->handlers[method] = handler;
}

lucy::Handler *lucy::RouteTrie::find(const std::string &method, const std::string &requestPath) {
  TrieNode *node = root.get();
  std::vector<std::string> parts = splitPath(requestPath);
  for (const std::string &part : parts) {
    node = node->children.contains(part)  ? node->children[part].get()
           : node->children.contains("*") ? node->children["*"].get()
                                          : nullptr;

    // No route found
    if (!node) {
      return nullptr;
    }
  }

  // Route exists but for another method
  if (!node->handlers.count(method)) {
    return nullptr;
  }

  return &node->handlers[method];
}
