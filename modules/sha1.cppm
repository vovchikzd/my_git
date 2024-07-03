module;

#include <string>

export module sha1;

export struct sha1 {
private:
  const std::string input_;
  std::string res_;

public:
  sha1(const sha1&) = delete;
  sha1& operator=(const sha1&) = delete;

  template<typename T = const char*>
  requires std::convertible_to<T, std::string>
  sha1(T&& str = ""): input_(str) {}
};
