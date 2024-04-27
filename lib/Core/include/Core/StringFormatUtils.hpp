#ifndef STRINGFORMATUTILS_H
#define STRINGFORMATUTILS_H

#include <string>

namespace StringFormatUtils
{
  std::string FormatInfoStr(const std::string &connectionsCountPrefix,
                            int connectionsCount,
                            const std::string &messagesCountPrefix,
                            unsigned long messagesCount);
}


#endif // STRINGFORMATUTILS_H
