module;

#include <filesystem>
#include <expected>
namespace fs = std::filesystem;

export module MRepository;

auto get_repo_root() -> std::expected<fs::path, /*Errors::filesystem_error*/int> {
  fs::path current_path = fs::current_path();

  for (int begin = 0,
           end   = std::distance(current_path.begin(), current_path.end());
       begin < end; ++begin, current_path = current_path.parent_path()) {
    if (fs::path tmp = current_path / ".git";
        fs::exists(tmp) and fs::is_directory(tmp))
      return current_path;
  }
  return "";
}

export struct Repository {
private:
  const fs::path root;

  template<std::convertible_to<fs::path> T>
  Repository(T&& path): root(std::forward<T>(path)) {}

public:
  Repository(const Repository&) = delete;
  static auto get_repo() -> std::expected<Repository, /*Errors::error*/int> {
    std::expected<Repository, int> result;
    return result;
  }
};
