#include "Response.hpp"

lucy::Response::Response() {}

void lucy::Response::send(const std::string& content) {
  this->content = content;
  ready_to_send = true;
}

lucy::Response& lucy::Response::status(int status_code) {
  this->status_code = status_code;
  return *this;
}
