#include <stdio.h>
#include <iostream>
#include <functional>

#include "Server.hpp"

int main() {
  lucy::Server server;
  const int port = 80;

  server.get("/test/:id/abc", [](const lucy::Request& request, std::string& response) {
    response = "Incoming request for " + request.path;
  });

  server.listen(port, []() {
    std::cout << "Listening on port " << port << std::endl;
  });

  return 0;
}
