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
}

// DONE by BABAK: Return the command that generated this process
string Process::Command() {
  return LinuxParser::Command(pid_);
}

// DONE by BABAK: Return this process's memory utilization
string Process::Ram() {
  return LinuxParser::Ram(pid_);
}
// DONE by BABAK: Return the user (name) that generated this process
string Process::User() {
  return LinuxParser::User(pid_);
}

// DONE by BABAK: Return the age of this process (in seconds)
long int Process::UpTime() const {
  // REVIEWER: We need to subtract the system uptime from every process' uptime.
  // LinuxParser::UpTime(pid_) is just the static time stamp depicting when a process was started
  // the time now is indicated with the overall system uptime LinuxParser::UpTime();
  return LinuxParser::UpTime() - LinuxParser::UpTime(pid_);
  // System uptime LinuxParser::UpTime(): is how many seconds the whole system has been on
  // process uptime LinuxParser::UpTime(pid_) is the timestamp of when the process pid started (0 is when the whole system has turned on)
}
// DONE by BABAK: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return this->CpuUtilization() < a.CpuUtilization();
  // sort based on UpTime (the recent openned application has a smaller process uptime)
  // return this->UpTime() < a.UpTime();
}
