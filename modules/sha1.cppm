module;

#include <climits>
#include <string>
#include <vector>
#include <sstream>
#include <array>

export module sha1;
using uint = unsigned int;
using citer = std::string::const_iterator;

namespace sha {

  export struct sha1 {
  private:
    size_t bmsl_;

    const uint h0_init_ = 0x67452301;
    const uint h1_init_ = 0xEFCDAB89;
    const uint h2_init_ = 0x98BADCFE;
    const uint h3_init_ = 0x10325476;
    const uint h4_init_ = 0xC3D2E1F0;

    uint h0_ = h0_init_;
    uint h1_ = h1_init_;
    uint h2_ = h2_init_;
    uint h3_ = h3_init_;
    uint h4_ = h4_init_;

    std::vector<std::array<uint, 512 / (CHAR_BIT * sizeof(uint))>> chunks;

    void pre_process_(citer begin, citer end) {

    }

  /*
    void pre_process_() {
      const size_t last_chunk_length = bmsl_ % 512;
      const size_t bits_count        = sizeof(uint) * CHAR_BIT;
      const uint mask                = 0x0;

      if (0 <= last_chunk_length and last_chunk_length <= 447) {
        suffix.insert(
            suffix.end(),
            static_cast<size_t>((448 - last_chunk_length) / bits_count), 0x0);
        suffix.push_back(mask | (bmsl_ >> 32));
        suffix.push_back(mask | bmsl_);

      } else {
        suffix.insert(
            suffix.end(),
            static_cast<size_t>((512 - last_chunk_length) / bits_count), 0x0);
        suffix.insert(suffix.end(), 14, 0x0);
        suffix.push_back(mask | (bmsl_ >> 32));
        suffix.push_back(mask | bmsl_);
      }
    }
  */

    auto lrotate(uint value, uint count = 1) -> uint {
      const uint mask = CHAR_BIT * sizeof(value) - 1;
      count &= mask;
      return (value << count) | (value >> (-count & mask));
    }

  public:
    sha1(const std::string& str = ""): bmsl_(CHAR_BIT * sizeof(char) * str.size()) {
      pre_process_(str.begin(), str.end());
      // main_cycle();
    }

    /*
      Different sources give different information about this,
      will be point my finger at he sky
    */
    auto hash() -> std::string {
      std::stringstream res;
      res << lrotate(h0_, 128) << lrotate(h1_, 96) << lrotate(h2_, 64)
          << lrotate(h3_, 32) << h4_;
      return res.str();
    }

  };

}  // namespace sha
