#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  System()
  :  cpu_(Processor()) {
  }
  Processor& Cpu();                   // DONE by BABAK: See src/system.cpp
  std::vector<Process>& Processes();  // DONE by BABAK: See src/system.cpp
  float MemoryUtilization();          // DONE by BABAK: See src/system.cpp
  long UpTime();                      // DONE by BABAK: See src/system.cpp
  int TotalProcesses();               // DONE by BABAK: See src/system.cpp
  int RunningProcesses();             // DONE by BABAK: See src/system.cpp
  std::string Kernel();               // DONE by BABAK: See src/system.cpp
  std::string OperatingSystem();      // DONE by BABAK: See src/system.cpp

  // DONE by BABAK: Define any necessary private members
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
};

#endif