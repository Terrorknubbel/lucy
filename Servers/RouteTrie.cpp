#include "RouteTrie.hpp"
#include <sstream>
#include <iostream>

lucy::RouteTrie::RouteTrie() {
  root = new TrieNode();
}

lucy::RouteTrie::~RouteTrie() {
    std::function<void(TrieNode*)> deleteNodes = [&](TrieNode* node) {
        for (auto& [selector, child_node] : node->children) {
            deleteNodes(child_node);
        }
        delete node;
    };
    deleteNodes(root);
}

std::vector<std::string> lucy::RouteTrie::splitPath(const std::string& path) {
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

void lucy::RouteTrie::insert(const std::string& method, const std::string& path, Handler handler) {
  lucy::TrieNode* node = root;
  std::vector<std::string> parts = splitPath(path);

    for (const std::string& part : parts) {
        if (part[0] == ':') {
            if (!node->children.count("*")) {
                node->children["*"] = new TrieNode();
            }
            node = node->children["*"];
        } else {
            if (!node->children.count(part)) {
                node->children[part] = new TrieNode();
            }
            node = node->children[part];
        }
    }
    node->handlers[method] = handler;
}

Handler* lucy::RouteTrie::find(const std::string& method, const std::string& requestPath) {
    TrieNode* node = root;
    std::vector<std::string> parts = splitPath(requestPath);

    for (const std::string& part : parts) {
        node = node->children.contains(part) ? node->children[part] :
           node->children.contains("*") ? node->children["*"] :
           nullptr;

        if (!node) {
            return nullptr;
        }
    }

  return &node->handlers[method];
}
