#ifndef Response_hpp
#define Response_hpp

#include <string>

namespace lucy
{
class Response
{
private:
  friend class RespondHandler;

  int status_code = 200;
  std::string content;
public:
  Response();
  void send(const std::string& content);
  Response& status(int status_code);
};
}

#endif /* Response_hpp */
