#include "fuzzywuzzy.hpp"
#include "wrapper.hpp"
#include "utils.hpp"

#include <algorithm>
#include <set>
#include <cmath>

namespace fuzz {

  int distance(const std::string &s1, const std::string &s2) {
    return utils::percent_round(wrapper::distance(s1, s2));
  }

  int ratio(const std::string &s1, const std::string &s2) {
    return utils::percent_round(wrapper::ratio(s1, s2));
  }

  /*int ratio(const std::wstring &s1, const std::wstring &s2) {
    return utils::percent_round(wrapper::ratio(s1, s2));
  }*/

  int partial_ratio(const std::string &shorter, const std::string &longer) {
    if(shorter.length() > longer.length()) {
      return partial_ratio(longer, shorter);
    }
    std::vector<LevOpCode> ops = wrapper::get_opcodes(shorter, longer);
    std::vector<LevMatchingBlock> blocks = wrapper::get_matching_blocks(ops, shorter, longer);


    /*
    * Each block represents a string of matching characters
    * in a string of the form (idx_1, idx_2, len). The best
    * partial match will block align with at least one
    * of those blocks.
    * e.g. shorter = "abcd", longer "XXXbcdeEEE"
    * block = (1, 3, 3)
    * best score == ratio("abcd", "Xbcd")
    */
    //std::vector<double> scores;
    double max = 0;
    for(const auto &block : blocks) {
      /*size_t long_start = std::max(0u, block.dpos - block.spos);
      if(block.dpos < block.spos) {
        long_start = 0;
      }*/
      size_t long_start = std::min(longer.size() - (shorter.size() - block.spos), block.dpos);

      auto long_substr = longer.substr(long_start, shorter.size() - block.spos);
      double r = wrapper::ratio(shorter.substr(block.spos), long_substr);

      if(r > 0.995)
        return 100;
      else if(max < r)
        max = r;
      //scores.push_back(r);
    }

    //if(scores.empty())
    //return 0;

    //double max = *std::max_element(scores.cbegin(), scores.cend());
    return utils::percent_round(max);
  }

  int partial_ratio(const std::wstring &shorter, const std::wstring &longer) {
    if(shorter.length() > longer.length()) {
      return partial_ratio(longer, shorter);
    }
    std::vector<LevOpCode> ops = wrapper::get_opcodes(shorter, longer);
    std::vector<LevMatchingBlock> blocks = wrapper::get_matching_blocks(ops, shorter, longer);


    /*
    * Each block represents a string of matching characters
    * in a string of the form (idx_1, idx_2, len). The best
    * partial match will block align with at least one
    * of those blocks.
    * e.g. shorter = "abcd", longer "XXXbcdeEEE"
    * block = (1, 3, 3)
    * best score == ratio("abcd", "Xbcd")
    */
    //std::vector<double> scores;
    double max = 0;
    for(const auto &block : blocks) {
      /*size_t long_start = std::max(0u, block.dpos - block.spos);
      if(block.dpos < block.spos) {
      long_start = 0;
      }*/
      size_t long_start = std::min(longer.size() - (shorter.size() - block.spos), block.dpos);

      auto long_substr = longer.substr(long_start, shorter.size() - block.spos);
      double r = wrapper::ratio(shorter.substr(block.spos), long_substr);

      if(r > 0.995)
        return 100;
      else if(max < r)
        max = r;
      //scores.push_back(r);
    }

    //if(scores.empty())
    //return 0;

    //double max = *std::max_element(scores.cbegin(), scores.cend());
    return utils::percent_round(max);
  }

  /* Returns a cleaned string with tokens sorted. */
  static void proccess_and_sort(std::string *s, bool full_process) {
    if(s) {
      if(full_process) {
        utils::full_process(s);
      }

      auto tokens = utils::split_string(*s);
      std::sort(tokens.begin(), tokens.end());

      *s = utils::join(tokens);
      utils::trim(s);
    }
  }

  int token_sort_ratio(const std::string &s1, const std::string &s2, bool full_proccess) {
    /* NOTE: do we need force_ascii? */
    std::string sorted1 = s1;
    std::string sorted2 = s2;
    proccess_and_sort(&sorted1, full_proccess);
    proccess_and_sort(&sorted2, full_proccess);

    return ratio(sorted1, sorted2);
  }

  int token_sort_partial_ratio(const std::string &s1, const std::string &s2, bool full_proccess) {
    /* NOTE: do we need force_ascii? */
    std::string sorted1 = s1;
    std::string sorted2 = s2;
    proccess_and_sort(&sorted1, full_proccess);
    proccess_and_sort(&sorted2, full_proccess);

    return partial_ratio(sorted1, sorted2);
  }

  /*
   * Find all alphanumeric tokens in each string and:
   *  - treat them as a set,
   *  - construct two strings of the form <sorted_intersection><sorted_remainder>,
   *  - take ratios of those two strings, and
   *  - check for unordered partial matches.
   */
  static int token_set_ratio(const std::string &s1, const std::string &s2, bool partial, bool full_process) {
    std::string p1 = s1;
    std::string p2 = s2;
    if(full_process) {
      utils::full_process(&p1);
      utils::full_process(&p2);
    }

    if(p1.length() == 0 || p2.length() == 0)
      return 0;

    auto split1 = utils::split_string(p1), split2 = utils::split_string(p2);
    auto tokens1 = std::set<std::string>(split1.cbegin(), split1.cend()),
      tokens2 = std::set<std::string>(split2.cbegin(), split2.cend());

    std::vector<std::string> intersection, diff1to2, diff2to1;

    std::set_intersection(tokens1.cbegin(), tokens1.cend(),
      tokens2.cbegin(), tokens2.cend(),
      std::back_inserter(intersection));

    std::set_difference(tokens1.cbegin(), tokens1.cend(),
      tokens2.cbegin(), tokens2.cend(),
      std::back_inserter(diff1to2));
    std::set_difference(tokens2.cbegin(), tokens2.cend(),
      tokens1.cbegin(), tokens1.cend(),
      std::back_inserter(diff2to1));

    std::sort(intersection.begin(), intersection.end());
    std::sort(diff1to2.begin(), diff1to2.end());
    std::sort(diff2to1.begin(), diff2to1.end());

    auto sorted_sect = utils::join(intersection),
      sorted_1to2 = utils::join(diff1to2),
      sorted_2to1 = utils::join(diff2to1);

    auto combined_1to2 = sorted_sect + ' ' + sorted_1to2,
      combined_2to1 = sorted_sect + ' ' + sorted_2to1;

    utils::trim(&sorted_sect);
    utils::trim(&combined_1to2);
    utils::trim(&combined_2to1);

    std::vector<int> pairwise;
    if(partial) {
      pairwise = std::vector<int>{
        partial_ratio(sorted_sect, combined_1to2),
        partial_ratio(sorted_sect, combined_2to1),
        partial_ratio(combined_1to2, combined_2to1)
      };
    } else {
      pairwise = std::vector<int>{
        ratio(sorted_sect, combined_1to2),
        ratio(sorted_sect, combined_2to1),
        ratio(combined_1to2, combined_2to1)
      };
    }
    return *std::max_element(pairwise.cbegin(), pairwise.cend());
  }

  int token_set_ratio(const std::string &s1, const std::string &s2, bool full_process) {
    return token_set_ratio(s1, s2, false, full_process);
  }

  int partial_token_set_ratio(const std::string &s1, const std::string &s2, bool full_process) {
    return token_set_ratio(s1, s2, true, full_process);
  }

  int quick_ratio(const std::string &s1, const std::string &s2) {
    std::string p1 = s1;
    std::string p2 = s2;
    utils::full_process(&p1);
    utils::full_process(&p2);

    if(p1.length() == 0 || p2.length() == 0)
      return 0;

    return ratio(p1, p2);
  }

  int weighted_ratio(const std::string &s1, const std::string &s2) {
    std::string p1 = s1;
    std::string p2 = s2;
    utils::full_process(&p1);
    utils::full_process(&p2);

    if(p1.length() == 0 || p2.length() == 0)
      return 0;

    bool try_partial = true;
    double unbase_scale = 0.95;
    double partial_scale = 0.90;

    double base = (double)ratio(p1, p2);
    double len_ratio = double(std::max(p1.length(), p2.length())) /
      std::min(p1.length(), p2.length());

    /* If strings are similar length, don't use partials. */
    if(len_ratio < 1.5)
      try_partial = false;

    /* If one string is much much shorter than the other. */
    if(len_ratio > 8)
      partial_scale = 0.60;

    if(try_partial) {
      double partial = partial_ratio(p1, p2) * partial_scale;
      double ptsor = token_sort_partial_ratio(p1, p2) * unbase_scale * partial_scale;
      double ptser = partial_token_set_ratio(p1, p2) * unbase_scale * partial_scale;

      return static_cast<int>(std::max({base, partial, ptsor, ptser}));
    } else {
      double tsor = token_sort_ratio(p1, p2, false) * unbase_scale;
      double tser = token_set_ratio(p1, p2, false) * unbase_scale;

      return static_cast<int>(std::max({base, tsor, tser}));
    }
  }

}