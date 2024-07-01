module;

#include <filesystem>
#include <expected>
namespace fs = std::filesystem;

export module repository;

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
