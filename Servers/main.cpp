#include <functional>
#include <iostream>

#include "Middlewares.hpp"
#include "Server.hpp"

void loggingMiddleware(const lucy::Request &req, lucy::Response &res, std::function<void()> next) {
  std::cout << "Request: " << req.method << " " << req.path << std::endl;
  for (auto [key, value] : req.params) {
    std::cout << "Param: " << key << " " << value << std::endl;
  }
  next();
}

int main() {
  lucy::Server server;
  const int port = 80;

  server.use(loggingMiddleware);
  server.use(lucy::Middlewares::serveStatic("public"));

  server.get("/test/:id/abc", [](const lucy::Request &request, lucy::Response &response) {
    response.status(200).send("Hello World");
  });

  server.listen(port, []() { std::cout << "Listening on port " << port << std::endl; });

  return 0;
}
