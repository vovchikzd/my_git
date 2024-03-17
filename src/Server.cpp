#include <expected>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace fs = std::filesystem;

auto init() -> std::optional<std::string> {
  std::optional<std::string> result;
  try {
    fs::create_directory(".git");
    fs::create_directory(".git/objects");
    fs::create_directory(".git/refs");

    std::ofstream head_file(".git/HEAD");
    if (head_file.is_open()) {
      head_file << "ref: refs/heads/main\n";
    } else {
      result = "Failed to create .git/Head file";
      return result;
    }

    std::cout << "Initialized git directory\n";
  } catch (const fs::filesystem_error& e) {
    result = e.what();
    return result;
  }
  return result;
}

auto main(int argc, char* argv[]) -> int {
  std::vector<std::string> args(argv, argv + argc);

  if (args.size() < 2) {
    std::cerr << "No command provided.\n";
    return EXIT_FAILURE;
  }

  if (args[1] == "init") {
    auto result = init();
    if (result) {
      std::cerr << result.value() << '\n';
      return EXIT_FAILURE;
    }
  } else {
    std::cerr << "Unknown command: '" << args[1] << "'\n";
    return EXIT_FAILURE;
  }


  return EXIT_SUCCESS;
}
