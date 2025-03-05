#include <stdio.h>
#include <iostream>
#include <functional>

#include "Server.hpp"

int main() {
  lucy::Server server;
  const int port = 80;

  server.get("/test/:id/abc", [](std::string &response) {
    response = "Abc";
  });

  server.listen(port, []() {
    std::cout << "Listening on port " << port << std::endl;
  });

  return 0;
}
