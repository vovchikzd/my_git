module;

#include <filesystem>
namespace fs = std::filesystem;

export module mgt;

  export auto get_repo_root() -> fs::path {
    fs::path current_path = fs::current_path();

    for (int begin = 0,
             end   = std::distance(current_path.begin(), current_path.end());
         begin < end; ++begin, current_path = current_path.parent_path())
      if (const fs::path tmp = current_path / ".git";
          fs::exists(tmp) and fs::is_directory(tmp))
        return current_path;
    return "";
  }

export struct repository {
private:
  const fs::path root_;

public:
  repository(const repository&) = delete;
  repository& operator=(const repository&) = delete;

  repository(): root_(tools::get_repo_root()) {}

  auto isExist() const -> bool { return !root_.empty(); }

  auto root() const -> fs::path { return root_; }
};
