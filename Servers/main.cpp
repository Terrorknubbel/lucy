#include <stdio.h>
#include <iostream>
#include <functional>

#include "Server.hpp"

int main() {
  lucy::Server server;

  server.get("/test/:id/abc", [](std::string &response) {
    response = "Abc";
  });

  server.listen();

  return 0;
}
