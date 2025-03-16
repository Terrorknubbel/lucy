#include "Middlewares.hpp"

lucy::Middlewares::Middlewares() {}

lucy::Middleware lucy::Middlewares::serveStatic(const std::string path) { return lucy::Static::serve(path); }
