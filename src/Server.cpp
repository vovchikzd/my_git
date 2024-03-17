#include <expected>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace fs = std::filesystem;

auto init() -> std::optional<fs::filesystem_error> {
  std::optional<fs::filesystem_error> result;
  return result;
}

auto main(int argc, char* argv[]) -> int {
  std::vector<std::string> args(argv, argv + argc);

  if (args.size() < 2) {
    std::cerr << "No command provided.\n";
    return EXIT_FAILURE;
  }

  if (args[1] == "init") {
    try {
      fs::create_directory(".git");
      fs::create_directory(".git/objects");
      fs::create_directory(".git/refs");

      std::ofstream headFile(".git/HEAD");
      if (headFile.is_open()) {
        headFile << "ref: refs/heads/main\n";
        headFile.close();
      } else {
        std::cerr << "Failed to create .git/HEAD file.\n";
        return EXIT_FAILURE;
      }

      std::cout << "Initialized git directory\n";
    } catch (const fs::filesystem_error& e) {
      std::cerr << e.what() << '\n';
      return EXIT_FAILURE;
    }
  } else {
    std::cerr << "Unknown command " << args[1] << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
