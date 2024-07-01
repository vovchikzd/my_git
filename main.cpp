#include <cstring>
#include <print>
#include <string>
#include <vector>

import tools;
import repository;

using std::println;

void usage(const char* name) {
  println(stdout, "usage: {} command/flag", name);
}

auto main(int argc, const char* argv[]) -> int {
  if (argc == 1) {
    println(stderr, "empty call of {}", argv[0]);
    usage(argv[0]);
    return EXIT_FAILURE;
  }

  if (argc == 2
      and (std::strcmp(argv[1], "help") == 0
           or std::strcmp(argv[1], "--help") == 0
           or std::strcmp(argv[1], "-h") == 0)) {
    usage(argv[0]);
    return EXIT_SUCCESS;
  }

  const std::vector<std::string> args(argv + 1, argv + argc);
  const Repository repo;

  for (auto&& arg: args)
    if (arg == "init") return tools::init(repo, args.begin() + 1, args.end());
}
