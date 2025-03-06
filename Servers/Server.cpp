#include "Server.hpp"
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <unordered_map>
#include <functional>

lucy::Server::Server(){
  lucy::RouteTrie trie;
}

lucy::Server::~Server()
{
  close(client_fd);
}

void lucy::Server::acceptor()
{
  struct sockaddr_in address = listening_socket->get_address();
  int address_length = sizeof(address);
  client_fd = accept(listening_socket->get_server_fd(), (struct sockaddr *)&address, (socklen_t *)&address_length);
  read(client_fd, buffer, sizeof(buffer));
  request = std::string(buffer);
}

void lucy::Server::get(const std::string& path, Handler handler)
{
  trie.insert("GET", path, handler);
}

void lucy::Server::handler()
{
  std::cout << buffer << std::endl;
  std::string request(buffer);
  std::istringstream requestStream(request);
  std::string method, path, httpVersion;

  requestStream >> method >> path >> httpVersion;

  response_content = "404 Not Found";
  std::unordered_map<std::string, std::string> params;
  Handler *handler = trie.find(method, path);
  if(handler) {
    (*handler)(response_content);
  }
}

void lucy::Server::responder()
{
  std::string httpResponse =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: " + std::to_string(response_content.size()) + "\r\n"
    "\r\n" +
    response_content;

  std::cout << response_content << std::endl;
  write(client_fd, httpResponse.c_str(), httpResponse.size());
  close(client_fd);
}

void lucy::Server::listen(const int port, std::function<void()> callback)
{
  listening_socket = new ListeningSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, port, INADDR_ANY, 10);
  callback();

  while (true) {
    acceptor();
    handler();
    responder();
  }
}
