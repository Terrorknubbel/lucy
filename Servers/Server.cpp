#include "Server.hpp"
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <unordered_map>
#include <functional>

lucy::Server::Server(){}

lucy::Server::~Server()
{
  close(client_fd);
}

void lucy::Server::acceptor()
{
  struct sockaddr_in address = listening_socket.get_address();
  int address_length = sizeof(address);
  client_fd = accept(listening_socket.get_server_fd(), (struct sockaddr *)&address, (socklen_t *)&address_length);
  read(client_fd, buffer, sizeof(buffer));
  raw_request = std::string(buffer);
}

void lucy::Server::use(Middleware middleware)
{
  middlewareHandler.add(middleware);
}

void lucy::Server::get(const std::string& path, Handler handler)
{
  trie.insert("GET", path, handler);
}

void lucy::Server::responder()
{
  write(client_fd, http_response.c_str(), http_response.size());
  close(client_fd);
}

void lucy::Server::listen(const int port, std::function<void()> callback)
{
  listening_socket = ListeningSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, port, INADDR_ANY, 10);
  callback();

  while (true) {
    acceptor();
    request = Request(raw_request, trie);
    http_response = RespondHandler().call(request, middlewareHandler);
    responder();

  }
}
