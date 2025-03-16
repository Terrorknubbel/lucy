#ifndef MiddlewareHandler_hpp
#define MiddlewareHandler_hpp

#include "Request.hpp"
#include <functional>

namespace lucy {
class Request;
typedef std::function<void(const Request &, Response &, std::function<void()> Next)> Middleware;
class MiddlewareHandler {
private:
  std::vector<Middleware> middlewares;

public:
  MiddlewareHandler();
  void add(Middleware middleware);
  void call(const Request &request, Response &response) const;
};
} // namespace lucy

#endif /* MiddlewareHandler_hpp */
