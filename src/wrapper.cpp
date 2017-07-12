#include <iostream>

#include "wrapper.hpp"

namespace fuzz {
  namespace wrapper {

    double distance(const std::string &str1, const std::string &str2) {
      size_t len1 = str1.length(),
        len2 = str2.length();

      const uint8_t *lb1 = reinterpret_cast<const uint8_t *>(str1.c_str()),
        *lb2 = reinterpret_cast<const uint8_t *>(str2.c_str());

      size_t lensum = len1 + len2;
      size_t edit_dist = lev_edit_distance(len1, lb1, len2, lb2, false);

      return static_cast<double>(edit_dist);
    }

    double distance(const std::wstring &str1, const std::wstring &str2) {

      size_t lensum = str1.length() + str2.length();
      size_t edit_dist = lev_edit_distance(str1.length(), str1.c_str(),
        str2.length(), str2.c_str(), false);

      return static_cast<double>(edit_dist);
    }

    double ratio(const std::string &str1, const std::string &str2) {
      size_t len1 = str1.length(),
        len2 = str2.length();

      const uint8_t *lb1 = reinterpret_cast<const uint8_t *>(str1.c_str()),
        *lb2 = reinterpret_cast<const uint8_t *>(str2.c_str());

      size_t lensum = len1 + len2;
      size_t edit_dist = lev_edit_distance(len1, lb1, len2, lb2, true);

      return static_cast<double>(lensum - edit_dist) / lensum;
    }

    double ratio(const std::wstring &str1, const std::wstring &str2) {

      size_t lensum = str1.length() + str2.length();
      size_t edit_dist = lev_edit_distance(str1.length(), str1.c_str(),
        str2.length(), str2.c_str(), true);

      return static_cast<double>(lensum - edit_dist) / lensum;
    }

    std::vector<LevOpCode> get_opcodes(const std::string &s1, const std::string &s2) {
      //std::vector<LevEditOp> ops;
      std::vector<LevOpCode> codes;
      {
        size_t size = 0;
        LevEditOp* ops_1 = lev_editops_find(s1.length(), (const uint8_t*)s1.c_str(), s2.length(), (const uint8_t*)s2.c_str(), &size);
        if(ops_1) {
          size_t size_2 = 0;
          LevOpCode *ops_2 = lev_editops_to_opcodes(size, ops_1, &size_2, s1.length(), s2.length());
          //ops.assign(ops_1, ops_1 + size);
          if(ops_2) {
            codes.assign(ops_2, ops_2 + size_2);
            free(ops_2);
          }
          free(ops_1);
        }
      }
      return codes;
    }

    std::vector<LevOpCode> get_opcodes(const std::wstring &s1, const std::wstring &s2) {
      //std::vector<LevEditOp> ops;
      std::vector<LevOpCode> codes;
      {
        size_t size = 0;
        LevEditOp* ops_1 = lev_editops_find(s1.length(), s1.c_str(), s2.length(), s2.c_str(), &size);
        if(ops_1) {
          size_t size_2 = 0;
          LevOpCode *ops_2 = lev_editops_to_opcodes(size, ops_1, &size_2, s1.length(), s2.length());
          //ops.assign(ops_1, ops_1 + size);
          if(ops_2) {
            codes.assign(ops_2, ops_2 + size_2);
            free(ops_2);
          }
          free(ops_1);
        }
      }
      return codes;
    }

    /*std::vector<LevEditOp> get_editops(const std::string &s1, const std::string &s2) {
      return lev_editops_find(s1.length(), (const uint8_t*)s1.c_str(), s2.length(), (const uint8_t*)s2.c_str());
    }

    std::vector<LevEditOp> get_editops(const std::wstring &s1, const std::wstring &s2) {
      return lev_editops_find(s1.length(), s1.c_str(), s2.length(), s2.c_str());
    }

    std::vector<LevOpCode> get_opcodes(const std::vector<LevEditOp> &v, const std::string &s1, const std::string &s2) {
      return lev_editops_to_opcodes(v, s1.length(), s2.length());
    }*/

    std::vector<LevMatchingBlock> get_matching_blocks(const std::vector<LevOpCode> &v, const std::string &s1, const std::string &s2) {
      std::vector<LevMatchingBlock> outBlock;
      {
        size_t size = 0;
        LevMatchingBlock *block = lev_opcodes_matching_blocks(s1.length(), s2.length(), v.size(), v.data(), &size);
        if(block) {
          outBlock.assign(block, block + size);
          free(block);
        }
      }
      return outBlock;
    }

    std::vector<LevMatchingBlock> get_matching_blocks(const std::vector<LevOpCode> &v, const std::wstring &s1, const std::wstring &s2) {
      std::vector<LevMatchingBlock> outBlock;
      {
        size_t size = 0;
        LevMatchingBlock *block = lev_opcodes_matching_blocks(s1.length(), s2.length(), v.size(), v.data(), &size);
        if(block) {
          outBlock.assign(block, block + size);
          free(block);
        }
      }
      return outBlock;
    }

    std::vector<LevMatchingBlock> get_matching_blocks_2(const std::vector<LevOpCode> &v, const std::string &s1, const std::string &s2) {
      std::vector<LevMatchingBlock> outBlock;
      {
        size_t size = 0;
        LevMatchingBlock *block = lev_opcodes_matching_blocks_2(s1.length(), s2.length(), v.size(), v.data(), &size);
        if(block) {
          outBlock.assign(block, block + size);
          free(block);
        }
      }
      return outBlock;
    }

    std::vector<LevMatchingBlock> get_matching_blocks_2(const std::vector<LevOpCode> &v, const std::wstring &s1, const std::wstring &s2) {
      std::vector<LevMatchingBlock> outBlock;
      {
        size_t size = 0;
        LevMatchingBlock *block = lev_opcodes_matching_blocks_2(s1.length(), s2.length(), v.size(), v.data(), &size);
        if(block) {
          outBlock.assign(block, block + size);
          free(block);
        }
      }
      return outBlock;
    }
  }
}