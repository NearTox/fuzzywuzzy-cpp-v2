#include "utils.hpp"

#include <algorithm>
#include <cmath>
#include <cctype>

namespace fuzz {

  namespace utils {

    /*
     * Return a rounded percentage in the range [0,100].
     */
    int percent_round(double val) {
      return static_cast<int>(std::round(100 * val));
    }


    /*
     * Split a string into multiple strings when a character is met.
     * Returns all tokens in an array.
     */
    std::vector<std::string> split_string(const std::string &str) {

      std::vector<std::string> tokens;
      std::string::const_iterator itt_2 = str.begin();
      for(std::string::const_iterator itt = itt_2, itt_end = str.end(); itt != itt_end; ++itt) {
        if(*itt == ' ') {
          if(itt_2 != itt) {
            tokens.emplace_back(itt_2, itt);
          }
          itt_2 = itt + 1;
        }
      }

      if(itt_2 != str.end()) {
        tokens.emplace_back(itt_2, str.end());
      }
      return std::move(tokens);
    }

    /*
     * Removes leading and trailing whitespace characters from
     * the passed string.
     */
    void trim(std::string *str) {
      if(str) {
        /* Strip leading whitespace.. */
        auto start = std::find_if_not(str->cbegin(), str->cend(), std::isspace);
        str->erase(str->cbegin(), start);

        /* .. and trailing. */
        auto end = std::find_if_not(str->crbegin(), str->crend(), std::isspace);
        str->erase(end.base(), str->cend());

      }
    }

    /*
     * Akin to Pythons join: concatenate a vector of strings
     * with intervening occurrences of sep.
     */
    std::string join(const std::vector<std::string> &v) {
      std::string retstr;
      for(const auto &str : v) {
        retstr += str;
        retstr += ' ';
      }
      if(v.size()) {
        retstr.pop_back();
      }
      return std::move(retstr);
    }

    /*
     * Process the string by
     *  - replace non-alphanumeric characters with whitespace,
     *  - trim whitespace, and
     *  - forcing to lower case.
     */
    void full_process(std::string *str) {
      if(str) {
        /* Replace non-alphanumeric characters with whitespace, */
        for(auto &for_itt : *str) {
          /* NOTE: same thing here: specify locale? */
          if(!std::isalnum(for_itt)) {
            for_itt = ' ';
          } else {
            /* force to lower case. */
            for_itt = tolower(for_itt);
          }
        }

        /* trim whitespace, and */
        utils::trim(str);
      }
    }

  }  // ns utils

}  // ns fuzz
