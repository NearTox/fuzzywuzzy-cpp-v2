#pragma once

#include <vector>

namespace fuzz {

  namespace utils {

    int percent_round(double val);

    std::vector<std::string> split_string(const std::string &str);

    void trim(std::string *str);

    std::string join(const std::vector<std::string> &v);

    void full_process(std::string *str);

  }

}