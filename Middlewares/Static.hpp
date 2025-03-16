#ifndef Static_hpp
#define Static_hpp

#include "../Servers/MiddlewareHandler.hpp"
#include "../Servers/mime_types.hpp"
#include <unordered_map>
#include <fstream>

namespace lucy {
struct StaticOptions {
  std::string defaultFile = "index.html";
};

class Static {
private:
  static std::string get_mime_type(const std::string &path);
  static std::string read_file(const std::string &path);

public:
  Static();
  static Middleware serve(const std::string &path, const StaticOptions &options = StaticOptions());
};
} // namespace lucy

#endif /* Static_hpp */
