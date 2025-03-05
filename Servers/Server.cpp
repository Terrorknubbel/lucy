#include "Server.hpp"
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <unordered_map>
#include <functional>

lucy::Server::Server(){
  socket = new ListeningSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 80, INADDR_ANY, 10);

  lucy::RouteTrie trie;
}

lucy::Server::~Server()
{
    close(new_socket);
}

void lucy::Server::acceptor()
{
    struct sockaddr_in address = socket->get_address();
    int address_length = sizeof(address);
    new_socket = accept(socket->get_sock(), (struct sockaddr *)&address, (socklen_t *)&address_length);
    read(new_socket, buffer, sizeof(buffer));
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
    if (method == "GET") {
      std::unordered_map<std::string, std::string> params;
      Handler *handler = trie.find(method, path);
      if(handler) {
        (*handler)(response_content);
      }
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
    write(new_socket, httpResponse.c_str(), httpResponse.size());
    close(new_socket);
}

void lucy::Server::listen()
{
    while (true) {
        std::cout << "Waiting for connection..." << std::endl;
        acceptor();
        handler();
        responder();
        std::cout << "Connection closed." << std::endl;
    }
}
