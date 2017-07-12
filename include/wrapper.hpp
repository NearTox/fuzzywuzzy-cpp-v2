#pragma once

#include <vector>
#include <string>

#include "levenshtein.hpp"

namespace fuzz {
  namespace wrapper {

    double distance(const std::string &str1, const std::string &str2);
    double distance(const std::wstring &str1, const std::wstring &str2);

    double ratio(const std::string &str1, const std::string &str2);
    double ratio(const std::wstring &str1, const std::wstring &str2);

    std::vector<LevMatchingBlock> get_matching_blocks(const std::vector<LevOpCode> &v, const std::string &s1, const std::string &s2);
    std::vector<LevMatchingBlock> get_matching_blocks(const std::vector<LevOpCode> &v, const std::wstring &s1, const std::wstring &s2);
    std::vector<LevMatchingBlock> get_matching_blocks_2(const std::vector<LevOpCode> &v, const std::string &s1, const std::string &s2);
    std::vector<LevMatchingBlock> get_matching_blocks_2(const std::vector<LevOpCode> &v, const std::wstring &s1, const std::wstring &s2);

    std::vector<LevOpCode> get_opcodes(const std::string &s1, const std::string &s2);
    std::vector<LevOpCode> get_opcodes(const std::wstring &s1, const std::wstring &s2);

    //std::vector<LevOpCode> get_opcodes(const std::vector<LevEditOp> &ops, const std::string &s1, const std::string &s2);

    //std::vector<LevEditOp> get_editops(const std::string &s1, const std::string &s2);
    //std::vector<LevEditOp> get_editops(const std::wstring &s1, const std::wstring &s2);

  }
}
