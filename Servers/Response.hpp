#ifndef Response_hpp
#define Response_hpp

#include <string>

namespace lucy
{
class Response
{
private:
  friend class RespondHandler;
  friend class MiddlewareHandler;

  int status_code = 200;
  std::string content;
  bool ready_to_send = false;
public:
  Response();
  void send(const std::string& content);
  Response& status(int status_code);
};
}

#endif /* Response_hpp */
