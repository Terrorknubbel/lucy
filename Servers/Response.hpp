#ifndef Response_hpp
#define Response_hpp

#include <string>
#include <unordered_map>

namespace lucy {
class Response {
  const std::unordered_map<int, std::string> HTTP_STATUS_TEXT = {
    {200, "OK"},
    {201, "Created"},
    {204, "No Content"},
    {301, "Moved Permanently"},
    {302, "Found"},
    {304, "Not Modified"},
    {400, "Bad Request"},
    {401, "Unauthorized"},
    {403, "Forbidden"},
    {404, "Not Found"},
    {500, "Internal Server Error"},
    {501, "Not Implemented"},
    {502, "Bad Gateway"},
    {503, "Service Unavailable"}};

private:
  friend class RespondHandler;
  friend class MiddlewareHandler;

  int status_code = 200;
  std::string http_status_text = HTTP_STATUS_TEXT.at(status_code);
  std::unordered_map<std::string, std::string> headers = {{"Content-Type", "text/plain"}, {"Content-Length", "0"}};
  std::string content;
  bool ready_to_send = false;

public:
  Response();
  void send(const std::string &content);
  Response &set(const std::string &key, const std::string &value);
  Response &status(int status_code);
};
} // namespace lucy

#endif /* Response_hpp */
