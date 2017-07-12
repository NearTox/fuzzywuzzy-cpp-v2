#include <iostream>
#include <chrono>

#include "fuzzywuzzy.hpp"

int main() {
  const std::string a = "I'm in your mind", b = "I'm in your mind fuzz";
  const std::string c = "fuzzy wuzzy was a bear", d = "wuzzy fuzzy was a bear";
  const std::string e = "fuzzy was a bear", f = "fuzzy fuzzy was a bear";
  auto time_1 = std::chrono::high_resolution_clock::now();

  auto str1 = fuzz::ratio(a, b);
  auto str2 = fuzz::partial_ratio(a, b);
  auto str3 = fuzz::token_sort_ratio(c, d);
  auto str4 = fuzz::token_sort_ratio(e, f);

  for(size_t i = 0; i < 99999; i++) {
    str1 = fuzz::ratio(a, b);
    str2 = fuzz::partial_ratio(a, b);
    str3 = fuzz::token_sort_ratio(c, d);
    str4 = fuzz::token_sort_ratio(e, f);
  }

  auto time_2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_3 = time_2 - time_1;
  std::cout << str1 << '\n';
  std::cout << str2 << '\n';
  std::cout << str3 << '\n';
  std::cout << str4 << '\n';
  std::cout << time_3.count() << '\n';
  return 0;
}
