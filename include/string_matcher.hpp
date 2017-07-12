#pragma once

#include <string>
#include <vector>

#include "levenshtein.hpp"

namespace fuzz {
  
  class string_matcher {
  public:
    explicit string_matcher(const std::string &s1, const std::string &s2) : s1_(s1), s2_(s2) {}

    void set_strings(const std::string &s1, const std::string s2);
    void set_string1(const std::string &s1);
    void set_string2(const std::string &s2);

    std::vector<LevMatchingBlock> get_matching_blocks();
    std::vector<LevOpCode> get_opcodes();
    std::vector<LevEditOp> get_editops();

    double distance();
    double ratio();
    double real_quick_ratio();

  private:
    std::string s1_, s2_;
    double ratio_ = -1;
    int distance_ = -1;

    std::vector<LevMatchingBlock> matching_blocks_;
    std::vector<LevOpCode> op_codes_;
    std::vector<LevEditOp> edit_ops_;

    void reset_cache();
  };
  
}
