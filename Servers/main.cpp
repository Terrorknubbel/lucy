#include <stdio.h>
#include <iostream>
#include <functional>

#include "Server.hpp"

int main() {
  lucy::Server server;

  server.Get("/test/:id/abc", [](std::string &response) {
    response = "Abc";
  });

  server.launch();

  return 0;
}
