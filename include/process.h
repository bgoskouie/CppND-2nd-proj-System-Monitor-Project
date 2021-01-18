#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid)
    :  pid_(pid) {};
  int Pid();                               // DONE by BABAK: See src/process.cpp
  std::string User();                      // DONE by BABAK: See src/process.cpp
  std::string Command();                   // DONE by BABAK: See src/process.cpp
  float CpuUtilization() const;            // DONE by BABAK: See src/process.cpp
  std::string Ram();                       // DONE by BABAK: See src/process.cpp
  long int UpTime() const;                       // DONE by BABAK: See src/process.cpp

  // use this to sort processes by which is the most ACTIVE (e.g. higher CpuUtilization)
  bool operator<(Process const& a) const;  // DONE by BABAK: See src/process.cpp

  // DONE by BABAK: Declare any necessary private members
 private:
   int pid_;
};

#endif