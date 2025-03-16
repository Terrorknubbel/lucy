#include "MiddlewareHandler.hpp"

lucy::MiddlewareHandler::MiddlewareHandler() {}

void lucy::MiddlewareHandler::add(Middleware middleware) { middlewares.push_back(middleware); }

void lucy::MiddlewareHandler::call(const Request &request, Response &response) const {
  if (middlewares.size() == 0) {
    return;
  }

  int index = 0;
  std::function<void()> next = [&]() {
    if (index < middlewares.size() && !response.ready_to_send) {
      Middleware current_middleware = middlewares[index++];
      current_middleware(request, response, next);
    }
  };
  next();
}
