module;

#include <expected>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <new>
#include <print>
#include <vector>

namespace fs = std::filesystem;
using std::println;

export module tools;

import repository;

using citer = const std::vector<std::string>::const_iterator;

namespace tools {

  export auto init(const Repository& repo, citer begin, citer end) -> int {
    if (repo.isExist()) {
      println(stderr, "Initialized repository already exist, root: {}",
              repo.root());
      return EXIT_FAILURE;
    }

    try {
      const fs::path root =
          fs::current_path() / (std::distance(begin, end) ? *begin : "");

      fs::create_directory(root / ".git");
      fs::create_directory(root / ".git/objects");
      fs::create_directory(root / ".git/refs");

      std::ofstream head(root / ".git/HEAD");
      if (!head.is_open()) {
        println(stderr, "Failed to create HEAD file");
        fs::remove_all(root / ".git");
        return EXIT_FAILURE;
      }

      head << "ref: refs/heads/main\n";

      println(stdout, "Initialized git repository");
    } catch (const fs::filesystem_error& err) {
      println(stderr, "FILESYSTEM ERROR: {}", err.what());
      return EXIT_FAILURE;
    } catch (const std::bad_alloc& err) {
      println(stderr, "Cannot allocate memory: {}", err.what());
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }

  export auto get_repo_root()
      -> std::expected<fs::path, /*Errors::filesystem_error*/ int> {
    fs::path current_path = fs::current_path();

    for (int begin = 0,
             end   = std::distance(current_path.begin(), current_path.end());
         begin < end; ++begin, current_path = current_path.parent_path())
      if (const fs::path tmp = current_path / ".git";
          fs::exists(tmp) and fs::is_directory(tmp))
        return current_path;
  }

}  // namespace tools
