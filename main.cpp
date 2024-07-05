#include <cstring>
#include <print>
#include <string>
#include <vector>

import mgt;
import sha1;

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

  if (args.forward() == "init") return mgt::init(args.begin() + 1, args.end());

  const mgt::repository repo;

  if (!repo.isExist()) {
    println(stderr, "not a git repository");
    return EXIT_FAILURE;
  }

  for (auto begin = args.begin() + 1, end = argc.end(); begin < end; ++begin)
    begin = end;

  return EXIT_SUCCESS;
}
