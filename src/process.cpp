#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// DONE by BABAK: Return this process's ID
int Process::Pid() { return pid_; }

// DONE by BABAK: Return this process's CPU utilization
float Process::CpuUtilization() const {
  return LinuxParser::ProcessUtilization(pid_);
//   return 0;
}

// DONE by BABAK: Return the command that generated this process
string Process::Command() {
  return LinuxParser::Command(pid_);
  //return string();
}

// DONE by BABAK: Return this process's memory utilization
string Process::Ram() {
  return LinuxParser::Ram(pid_);
  //return string();
}
// DONE by BABAK: Return the user (name) that generated this process
string Process::User() {
  return LinuxParser::User(pid_);
  //return string();
}

// DONE by BABAK: Return the age of this process (in seconds)
long int Process::UpTime() {
  return LinuxParser::UpTime(pid_);
  //return 0;
}
// DONE by BABAK: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return this->CpuUtilization() < a.CpuUtilization();
  // return true;
}
