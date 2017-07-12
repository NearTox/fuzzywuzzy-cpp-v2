#include "string_matcher.hpp"
#include "wrapper.hpp"

#include <algorithm>

namespace fuzz {

  void string_matcher::set_strings(const std::string &s1, const std::string s2) {
    s1_ = s1;
    s2_ = s2;

    reset_cache();
  }

  void string_matcher::set_string1(const std::string &s1) {
    s1_ = s1;
    reset_cache();
  }

  void string_matcher::set_string2(const std::string &s2) {
    s2_ = s2;
    reset_cache();
  }

  void string_matcher::reset_cache() {
    ratio_ = -1;
    distance_ = -1;

    matching_blocks_.clear();
    op_codes_.clear();
    edit_ops_.clear();
  }

  std::vector<LevOpCode> string_matcher::get_opcodes() {
    if(op_codes_.empty())
      op_codes_ = wrapper::get_opcodes(s1_, s2_);

    return op_codes_;
  }

  /*std::vector<LevEditOp> string_matcher::get_editops() {
    if(edit_ops_.empty())
      edit_ops_ = wrapper::get_editops(s1_, s2_);
    return edit_ops_;
  }*/

  std::vector<LevMatchingBlock> string_matcher::get_matching_blocks() {
    if(matching_blocks_.empty()) {
      auto ops = get_opcodes();
      matching_blocks_ = wrapper::get_matching_blocks(ops, s1_, s2_);
    }
    return matching_blocks_; 
  }

  double string_matcher::distance() {
    if(ratio_ < 0)
      ratio_ = wrapper::distance(s1_, s2_);
    return ratio_;
  }

  double string_matcher::ratio() {
    if(ratio_ < 0)
      ratio_ = wrapper::ratio(s1_, s2_);
    return ratio_;
  }

  double string_matcher::real_quick_ratio() {
    size_t len1 = s1_.length(), len2 = s2_.length();
    return 2.0 * std::min(len1, len2) / (len1 + len2);
  }

} 
