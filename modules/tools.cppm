module;

#include <expected>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <new>
#include <print>
#include <vector>

export module tools;

import repository;

namespace fs = std::filesystem;
using std::println;

using citer = const std::vector<std::string>::const_iterator;

namespace tools {

  export auto init(const Repository& repo, citer begin, citer end) -> int {
    if (repo.isExist()) {
      println(stderr, "Initialized repository already exist, root: {}",
              repo.root().string());
      return EXIT_FAILURE;
    }

    try {
      const fs::path root =
          fs::current_path() / (std::distance(begin, end) ? *begin : "");

      if (fs::path tmp = root / ".git";
          fs::exists(tmp) and fs::is_directory(tmp)) {
        println(stderr, "Initialized repository already exist, root: {}",
                root.string());
        return EXIT_FAILURE;
      }

      fs::create_directories(root / ".git");
      fs::create_directories(root / ".git/objects");
      fs::create_directories(root / ".git/refs");

      std::ofstream head(root / ".git/HEAD");
      if (!head.is_open()) {
        println(stderr, "Failed to create HEAD file");
        fs::remove_all(root / ".git");
        return EXIT_FAILURE;
      }

      head << "ref: refs/heads/main\n";

      println(stdout, "Initialized git repository");
    } catch (const fs::filesystem_error& err) {
      println(stderr, "{}", err.what());
      return EXIT_FAILURE;
    } catch (const std::bad_alloc& err) {
      println(stderr, "Cannot allocate memory: {}", err.what());
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }

}  // namespace tools
