module;

#include <filesystem>
namespace fs = std::filesystem;

export module GRepository;

export auto get_repo_root() -> fs::path {
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

public:
  Repository(): root(get_repo_root()) {}
};
