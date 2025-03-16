#include "Static.hpp"

namespace fs = std::filesystem;

lucy::Static::Static() {}

std::string lucy::Static::get_mime_type(const std::string &path) {
  std::string ext = fs::path(path).extension();

  const auto mimeTypeIter = mime_types.find(ext);
  if (mimeTypeIter != mime_types.end()) {
    return mimeTypeIter->second;
  }

  return "application/octet-stream";
}

std::string lucy::Static::read_file(const std::string &path) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    return "";
  }
  std::ostringstream ss;
  ss << file.rdbuf();
  return ss.str();
}

lucy::Middleware lucy::Static::serve(const std::string &path, const StaticOptions &options) {
  return [path, options](const Request &request, Response &response, std::function<void()> next) {
    if (request.method != "GET" && request.method != "HEAD") {
      next();
      return;
    }

    fs::path base_path = fs::current_path();
    fs::path req_path = request.path.relative_path();

    if (request.path.extension().empty()) {
      req_path /= options.defaultFile;
    }

    fs::path file_path = base_path / path / req_path;
    if (fs::exists(file_path) && fs::is_regular_file(file_path)) {
      std::string content = ""; // Wir gehen erstmal davon aus, dass `request.method` HEAD ist.

      if (request.method == "GET") {
        content = read_file(file_path);
      }

      std::string mime_type = get_mime_type(file_path);

      response.status(200).set("Content-Type", mime_type).send(content);

      return;
    }

    next();
  };
}
