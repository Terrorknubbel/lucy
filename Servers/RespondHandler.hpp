#ifndef RespondHandler_hpp
#define RespondHandler_hpp

#include "Request.hpp"
#include "MiddlewareHandler.hpp"

namespace lucy
{
class Request;
typedef std::function<void(const Request&, Response&)> Handler;
class RespondHandler
{
private:
  Handler notFoundHandler = [](const lucy::Request& request, lucy::Response& response) {
    response.status(404).send("404 Not Found: " + request.path);
  };
public:
  RespondHandler();
  std::string call(const Request& request, const MiddlewareHandler& middlewareHandler);
};
}

#endif /* RespondHandler_hpp */
