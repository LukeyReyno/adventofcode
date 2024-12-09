#include "common/string/string.h"

#include <vector>

namespace AOC {

std::vector<String> String::split(const String& delimiter) {
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  String token;
  std::vector<String> res;

  while ((pos_end = this->find(delimiter, pos_start)) != String::npos) {
    token = this->substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    if (token.size() == 0) {
      continue;
    }

    res.push_back(token);
  }

  res.push_back(this->substr(pos_start));
  return res;
}

} // namespace AOC
