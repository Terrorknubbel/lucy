#ifndef RespondHandler_hpp
#define RespondHandler_hpp

#include "Request.hpp"
#include <string>

namespace lucy
{
class Request;
typedef std::function<void(const Request&, Response&)> Handler;
class RespondHandler
{
private:
  const Request* request;
  Handler notFoundHandler = [](const lucy::Request& request, lucy::Response& response) {
    response.status(404).send("404 Not Found: " + request.path);
  };
public:
  RespondHandler(const Request* request);
  std::string call();
};
}

#endif /* RespondHandler_hpp */
