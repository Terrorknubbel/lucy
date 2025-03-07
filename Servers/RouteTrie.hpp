#ifndef RouteTrie_hpp
#define RouteTrie_hpp

#include "Request.hpp"
#include <unordered_map>
#include <string>
#include <functional>
#include <vector>

namespace lucy
{
class Request;
typedef std::function<void(const Request&, std::string&)> Handler;

class TrieNode {
public:
    std::unordered_map<std::string, TrieNode*> children;
    std::unordered_map<std::string, Handler> handlers;


    TrieNode() : handlers(std::unordered_map<std::string, Handler>()) {}
};

class RouteTrie {
private:
    TrieNode* root;

    std::vector<std::string> splitPath(const std::string& path);

public:
    RouteTrie();
    ~RouteTrie();

    void insert(const std::string& method, const std::string& path, Handler handler);
    Handler* find(const std::string& method, const std::string& requestPath);
};
}

#endif // RouteTrie_hpp
