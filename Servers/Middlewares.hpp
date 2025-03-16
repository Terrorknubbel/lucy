#ifndef Middlewares_hpp
#define Middlewares_hpp

#include "../Middlewares/Static.hpp"

namespace lucy {
class Middlewares {
public:
  Middlewares();
  static Middleware serveStatic(const std::string path);
};
} // namespace lucy

#endif /* Middlewares_hpp */
