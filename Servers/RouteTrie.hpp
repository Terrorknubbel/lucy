#ifndef RouteTrie_hpp
#define RouteTrie_hpp

#include <memory>
#include <unordered_map>
#include <functional>
#include <vector>

#include "Request.hpp"

namespace lucy
{
class Request;
typedef std::function<void(const Request&, Response&)> Handler;

class TrieNode {
public:
    std::unordered_map<std::string, std::unique_ptr<TrieNode>> children;
    std::unordered_map<std::string, Handler> handlers;

    TrieNode() : handlers(std::unordered_map<std::string, Handler>()) {}
};

class RouteTrie {
private:
    std::unique_ptr<TrieNode> root;
    std::vector<std::string> splitPath(const std::string& path);
public:
    RouteTrie();

    void insert(const std::string& method, const std::string& path, Handler handler);
    Handler* find(const std::string& method, const std::string& requestPath);
};
}

#endif // RouteTrie_hpp
