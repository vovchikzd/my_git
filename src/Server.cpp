#include <expected>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <iterator>

#include "zstr.hpp"

namespace fs = std::filesystem;

auto init() -> std::optional<const char*> {
  std::optional<const char*> result;
  try {
    fs::create_directory(".git");
    fs::create_directory(".git/objects");
    fs::create_directory(".git/refs");

    std::ofstream head_file(".git/HEAD");
    if (head_file.is_open()) {
      head_file << "ref: refs/heads/main\n";
    } else {
      result = "Failed to create .git/HEAD file";
      return result;
    }

    std::cout << "Initialized git directory\n";
  } catch (const fs::filesystem_error& e) {
    result = e.what();
    return result;
  }
  return result;
}

auto cat_file(const std::string& blob_sha) -> std::optional<const char*> {
  std::optional<const char*> result;
  const fs::path blob_folder = blob_sha.substr(0, 2);
  const fs::path blob_file   = blob_sha.substr(2);
  const fs::path ifile(".git/objects"/blob_folder/blob_file);

  if (not fs::exists(ifile)) return "Invalid blob_sha";
  zstr::ifstream input(ifile, std::ios::binary);
  if (not input.is_open()) return "Failed to open object file";

  input >> std::noskipws;
  std::string file((std::istream_iterator<char>(input)), std::istream_iterator<char>());
  std::copy(file.begin() + file.find('\0') + 1, file.end(),
            std::ostream_iterator<char>(std::cout));

  return result;
}

auto main(int argc, char* argv[]) -> int {
  if (argc < 2) {
    std::cerr << "No command provided.\n";
    return EXIT_FAILURE;
  }

  const std::vector<std::string> args(argv, argv + argc);

  if (args[1] == "init") {
    const auto result = init();
    if (result) {
      std::cerr << result.value() << '\n';
      return EXIT_FAILURE;
    }
  } else if (args[1] == "cat-file") {
    if (args.size() <= 3) {
      std::cerr << "Invalid arguments, required '-p <blob_sha>'\n";
      return EXIT_FAILURE;
    }

    if (args[2] != "-p") {
      std::cerr << "Invalid flag for cat-file, expected '-p'\n";
      return EXIT_FAILURE;
    }

    const auto result = cat_file(args[3]);
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
