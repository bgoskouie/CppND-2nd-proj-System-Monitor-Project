#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// DONE by BABAK: Return the system's CPU
Processor& System::Cpu() {
  cpu_ = Processor();  // at every display cycle we need to find all the processes to update if an app is quit/killed or just aunched.
  return cpu_;
}

// DONE by BABAK: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  vector<int> allPids = LinuxParser::Pids();
  processes_.clear();  // in case this func gets calld twice we should remove all the old processes first.
  for (int pid : allPids) {
    processes_.push_back(Process(pid));
  }
  // Below sorts in ascending order (so smallest somes first)
  std::sort(processes_.begin(), processes_.end());
  std::reverse(processes_.begin(), processes_.end());

  // REVIEWER: recommends to sort in one shot by. Note that rbegin and rend reverse the order.
  // std::sort(processes_.rbegin(), processes_.rend());

  return processes_;
}

// DONE by BABAK: Return the system's kernel identifier (string)
std::string System::Kernel() {
  return LinuxParser::Kernel();
//   return string();
}

// DONE by BABAK: Return the system's memory utilization
float System::MemoryUtilization() {
  return LinuxParser::MemoryUtilization();
  // return 0.0;
}

// DONE by BABAK: Return the operating system name
std::string System::OperatingSystem() {
  return LinuxParser::OperatingSystem();
  // return string();
}

// DONE by BABAK: Return the number of processes actively running on the system
int System::RunningProcesses() {
  return LinuxParser::RunningProcesses();
  // return 0;
}

// DONE by BABAK: Return the total number of processes on the system
int System::TotalProcesses() {
  return LinuxParser::TotalProcesses();
  // return 0;
}

// DONE by BABAK: Return the number of seconds since the system started running
long int System::UpTime() {
  return LinuxParser::UpTime();
  // return 0;
}