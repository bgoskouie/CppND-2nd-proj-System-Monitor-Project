#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <unistd.h>   // for sysconf(_SC_CLK_TCK)
#include <string>
#include <vector>
#include <chrono>
#include "linux_parser.h"

class Processor {
public:
  Processor()
    : clockTicks_(sysconf(_SC_CLK_TCK)),
      numOfCpus_(LinuxParser::NumberOfCpus()) {
        Utilization();
      };
  float Utilization();  // DONE by BABAK: See src/processor.cpp

  // DONE by BABAK: Declare any necessary private members
private:
 long clockTicks_;
 int numOfCpus_;
 std::vector<std::string> cpuUtilPrev_;
 std::vector<std::string> cpuUtilRecent_;
 std::chrono::time_point<std::chrono::system_clock> timePrev_;
 std::chrono::time_point<std::chrono::system_clock> timeRecent_;
 bool start = false;

private:
  // private method to compute the Total CPU time from the content extracted from /proc/stat CPU line
  float CpuPercentUsage();
};

#endif