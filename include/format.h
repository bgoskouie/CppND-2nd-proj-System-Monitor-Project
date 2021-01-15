#ifndef FORMAT_H
#define FORMAT_H

#include <string>
#include <algorithm>

namespace Format {
  std::string ElapsedTime(long times);  // DONE by BABAK: See src/format.cpp

  int StoI(const std::string& input);

  unsigned long int StoL(const std::string& input);

  unsigned long long int StoLL(const std::string& input);
};                                    // namespace Format


#endif