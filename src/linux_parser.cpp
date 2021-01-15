#include <dirent.h>
#include <unistd.h>   // for sysconf(_SC_CLK_TCK)
#include <string>
#include <vector>

#include "format.h"   // for Format::ElapsedTime()
#include "linux_parser.h"

using std::stof;    // string to float
using std::string;
using std::to_string;    // convert an integer to a string
using std::vector;

// DONE by BABAK: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE by BABAK: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string key, value, kb;
  int memtotal, memfree;   //, memavailable, buffers, cached;
  string line;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      // std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value >> kb) {
        if (key == "MemTotal") {
          // std::replace(value.begin(), value.end(), '_', ' ');
          memtotal = Format::StoI(value);
        }
        if (key == "MemFree") {
          // std::replace(value.begin(), value.end(), '_', ' ');
          memfree = Format::StoI(value);
        }
        /*
        if (key == "MemAvailable") {
          memavailable = stoi(value);
          // std::replace(value.begin(), value.end(), '_', ' ');
        }
        if (key == "Buffers") {
          // std::replace(value.begin(), value.end(), '_', ' ');
          buffers = stoi(value);
        }
        if (key == "Cached") {
          // std::replace(value.begin(), value.end(), '_', ' ');
          cached = stoi(value);
        }
        */
        // https://stackoverflow.com/questions/41224738/how-to-calculate-system-memory-usage-from-proc-meminfo-like-htop/41251290#41251290
        // int totalusedMem = memtotal - memfree;
        // int nonCachedMemGreen = totalusedMem - (buffers + cached);
        // int cachedMemYellow = cached + SReclaimable - Shmem
        // Swap = SwapTotal - SwapFree
      }
    }
  }
  return ((float)memtotal - (float)memfree)/((float)memtotal);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string suspend, idle;
  float suspendTime;   //, idleTime;
  string line;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> suspend >> idle;
    suspendTime = stof(suspend);
    // idleTime = stof(idle);
  }
  return suspendTime;  // There are 2 numbers here, returning just one of them. What to do with the idleTime? func has only one return.
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  return 0;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  (void)pid;
  return 0;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  return 0;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  return 0;
  }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> out;
  string keyword("cpu");
  string value, attribute;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line) && (out.size() == 0)) {
      std::istringstream linestream(line);
      linestream >> attribute;
      if (attribute == keyword) {
        while (linestream >> value) {
          out.push_back(value);
        }
      }
    }
  }
  return out;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string keyValue;
  if (GetAttributeValueFromFile(keyValue,"processes", kProcDirectory + kStatFilename))
  {
    if (std::all_of(keyValue.begin(), keyValue.end(), isdigit)) {
      return Format::StoI(keyValue);
    }
  }
  return 0;   // not found
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string keyValue;
  if (GetAttributeValueFromFile(keyValue, "procs_running", kProcDirectory + kStatFilename))
  {
    if (std::all_of(keyValue.begin(), keyValue.end(), isdigit)) {
      return Format::StoI(keyValue);
    }
  }
  return 0;   // not found
}

bool LinuxParser::GetAttributeValueFromFile(string& keyValue,
                                           const string& keyword,
                                           const string& path) {
  string keyString;
  string line;
  std::ifstream stream(path);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> keyString >> keyValue) {
        if (keyString == keyword) {
          return true;   // found!
        }
      }
    }
  }
  return false;  // not found!
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
  }
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string keyValue;
  (void)GetAttributeValueFromFile(keyValue, "VmSize:", kProcDirectory + to_string(pid) + kStatusFilename);
  // return keyValue + " kB";
  long int megaBytes = Format::StoL(keyValue)/1000; // converts kB to MB
  return to_string(megaBytes);
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string keyValue;
  (void)GetAttributeValueFromFile(keyValue, "Uid:", kProcDirectory + to_string(pid) + kStatusFilename);
  return keyValue;  // is an int!!
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string uidOfThisPid = Uid(pid);
  
  int uidOfThisPid_i = Format::StoI(uidOfThisPid);
  string line;
  string delimiter(":");
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      string user;
      string x;
      string uidStart;
      string uidEnd;
      std::getline(linestream, user, ':');
      std::getline(linestream, x, ':');
      std::getline(linestream, uidStart, ':');
      std::getline(linestream, uidEnd, ':');
      // if (stoi(uidStart) <= uidOfThisPid_i && uidOfThisPid_i <= stoi(uidEnd)) {
      if (Format::StoI(uidStart) == uidOfThisPid_i) {
        return user;
      }
    }
  }
  return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  long valueLong;
  string value;
  string line;
  int startTimeIdx = 22;   // one based index of UpTime
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i = 0; i < startTimeIdx; ++i) {
      linestream >> value;
    }
    valueLong = Format::StoL(value);
  }
  return valueLong;
}

string LinuxParser::UpTimeString(int pid) {
  long ut = UpTime(pid);
  long clockTicks = sysconf(_SC_CLK_TCK);
  return Format::ElapsedTime((long)(ut/clockTicks));
}

float LinuxParser::ProcessUtilization(int pid) {
  float systemUpTime = UpTime();  // in seconds
  long clockTicks = sysconf(_SC_CLK_TCK);
  long uTime, sTime, cuTime, csTime, startTime;
  long uTimeIdx = 14;  // CPU time spent in user code, measured in clock ticks
  long sTimeIdx = 15;  // CPU time spent in kernel code, measured in clock ticks
  long cuTimeIdx = 16;  // Waited-for children's CPU time spent in user code (in clock ticks)
  long csTimeIdx = 17;  // Waited-for children's CPU time spent in kernel code (in clock ticks)
  long startTimeIdx = 22;   // Time when the process started, measured in clock ticks
  string value;
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    int idx = 0;
    while (linestream >> value) {
      idx++;
      if (idx == uTimeIdx) {
        uTime = Format::StoL(value);
      }
      if (idx == sTimeIdx) {
        sTime = Format::StoL(value);
      }
      if (idx == cuTimeIdx) {
        cuTime = Format::StoL(value);
      }
      if (idx == csTimeIdx) {
        csTime = Format::StoL(value);
      }
      if (idx == startTimeIdx) {
        startTime = Format::StoL(value);
      }
    }
  }
  // from: https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
  long totalTime = uTime + sTime;
  totalTime += cuTime + csTime;
  float seconds = systemUpTime - (startTime / clockTicks);
  // do not multiply by 100 in the below line. The UI will do that.
  float cpuUsagePercentage = (((float)totalTime / (float)clockTicks) / seconds);
  // returning 0.5 for 50%
  return cpuUsagePercentage;
}

int LinuxParser::NumberOfCpus() {
  string line;
  int num = 0;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      if (line.rfind("cpu", 0) == 0) {   // the line string starts with word cpu
        num++;
      }
      else {
        break;
      }
    }
  }
  // first line being the aggreate line needs to be excluded
  return (num - 1);
}