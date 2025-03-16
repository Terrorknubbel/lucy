#include "Response.hpp"

lucy::Response::Response() {}

void lucy::Response::send(const std::string &content) {
  this->content = content;
  ready_to_send = true;
}

lucy::Response &lucy::Response::set(const std::string &key, const std::string &value) {
  this->headers[key] = value;
  return *this;
}

lucy::Response &lucy::Response::status(int status_code) {
  this->status_code = status_code;
  this->http_status_text = HTTP_STATUS_TEXT.at(status_code);
  return *this;
}
