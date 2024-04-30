#pragma once

#include <string>
#include <stdexcept>

namespace StrUtils
{
  inline unsigned long ParseUL(const std::string &s)
  {
    std::size_t pos;

    unsigned long result = std::stoul(s, &pos);
    if (pos != s.size())
      throw std::runtime_error("StrUtils: error parsing unsigned long");

    return result;
  }
}
