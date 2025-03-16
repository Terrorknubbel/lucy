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

  // Bei der HEAD-Methode wird die Content-Length befüllt, auch wenn der Content leer ist. Die Content-Length berechnen
  // wir hier also nur dann, wenn sie nicht bereits gesetzt wurde.
  if (response.headers["Content-Length"] == "0") {
    response.headers["Content-Length"] = std::to_string(response.content.size());
  }

  std::string startLine = "HTTP/1.1 " + std::to_string(response.status_code) + " " + response.http_status_text + "\r\n";

  std::string headers = "";
  for (const auto& [key, value] : response.headers) {
    headers += key + ": " + value + "\r\n";
  }

  std::string httpResponse = startLine + headers + "\r\n" + response.content;

  return httpResponse;
}
