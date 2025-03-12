#include "RespondHandler.hpp"

lucy::RespondHandler::RespondHandler() {}

std::string lucy::RespondHandler::call(const Request& request, const MiddlewareHandler& middlewareHandler) {
  Response response;

  middlewareHandler.call(request, response);

  if(!response.ready_to_send) {
    if(request.handler) {
      (*request.handler)(request, response);
    } else {
      notFoundHandler(request, response);
    }
  }

  std::string httpResponse =
    "HTTP/1.1 " + std::to_string(response.status_code) + " OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: " + std::to_string(response.content.size()) + "\r\n"
    "\r\n" +
    response.content;

  return httpResponse;
}
