#include "RespondHandler.hpp"

lucy::RespondHandler::RespondHandler(const Request* request) {
  this->request = request;
}

std::string lucy::RespondHandler::call() {
  Response response;

  if(request->handler) {
    (*request->handler)(*request, response);
  } else {
    notFoundHandler(*request, response);
  }

  std::string httpResponse =
    "HTTP/1.1 " + std::to_string(response.status_code) + " OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: " + std::to_string(response.content.size()) + "\r\n"
    "\r\n" +
    response.content;

  return httpResponse;
}
