#include "processor.h"
#include "linux_parser.h"
#include "format.h"


// DONE by BABAK: Return the aggregate CPU utilization
float Processor::Utilization() {
  /**
   *  should read /proc/stat and there are a few lines about each processor
   *  (e.g. cpu0, cpu1,..) There is also a cpu name (at the beginning) which
   *  is an aggreagate of all the cpus.
   *  Each cpu line has 10 attributes inside (jiffies). They are in unit of clockTicks
   *  (or jiffies) which is 100Hz for my computer. To get the time, divide each
   *  jiffy value by clockTick number.
   *  To get a more accurate measurement of utilization, don't return the cpu utilization
   *  time from when the computer has started, but instead return delta(cpu_util)/delta(time)
   *  This way you can return a more current/recent measurement of CPU utilization.
   *  For example within the past 2 seconds, the CPU utilization could be 1.5 seconds (or 75%)
   *
   *  The very first "cpu" line aggregates the numbers in all of the other "cpuN" lines.
   *  These numbers identify the amount of time the CPU has spent performing different kinds of work.
   *  Time units are in USER_HZ (typically hundredths of a second).
   *  The meanings of the columns are as follows, from left to right:
   *  user: normal processes executing in user mode
   *  nice: niced processes executing in user mode
   *  system: processes executing in kernel mode
   *  idle: twiddling thumbs
   *  iowait: In a word, iowait stands for waiting for I/O to complete. But there are several problems:
   *       Cpu will not wait for I/O to complete, iowait is the time that a task is waiting for I/O to complete.
   *           When cpu goes into idle state for outstanding task io, another task will be scheduled on this CPU.
   *       In a multi-core CPU, the task waiting for I/O to complete is not running on any CPU, so the iowait of
   *           each CPU is difficult to calculate.
   *       The value of iowait field in /proc/stat will decrease in certain conditions.
   *           So, the iowait is not reliable by reading from /proc/stat.
   *  irq: servicing interrupts
   *  softirq: servicing softirqs
   *  steal: involuntary wait
   *  guest: running a normal guest
   *  guest_nice: running a niced guest

   */
  if (!start) {
    // timePrev_ = std::chrono::high_resolution_clock::now();
    cpuUtilPrev_ = LinuxParser::CpuUtilization();
    start = true;
    return 0.0;
  }

  cpuUtilRecent_ = LinuxParser::CpuUtilization();
//   timeRecent_ = std::chrono::high_resolution_clock::now();
//   std::chrono::duration<double> durationTime = timeRecent_ - timePrev_;
//   // durationTime.count() is a double gives the time difference in second
//   float dc = durationTime.count();
  float cpuP = CpuPercentUsage();
  return cpuP;
}

float Processor::CpuPercentUsage() {
  // output:
  float cpuPercentage = 0.0;
  // extract each jiffi from the vector of strings
  // convert it to long and store in a local variable.
  //Recent:
  unsigned long long int usertime =   Format::StoLL(cpuUtilRecent_[LinuxParser::CPUStates::kUser_])     ;
  unsigned long long int guest =      Format::StoLL(cpuUtilRecent_[LinuxParser::CPUStates::kGuest_])    ;
  unsigned long long int nicetime =   Format::StoLL(cpuUtilRecent_[LinuxParser::CPUStates::kNice_])     ;
  unsigned long long int guestnice =  Format::StoLL(cpuUtilRecent_[LinuxParser::CPUStates::kGuestNice_]);
  unsigned long long int idletime =   Format::StoLL(cpuUtilRecent_[LinuxParser::CPUStates::kIdle_])     ;
  unsigned long long int ioWait =     Format::StoLL(cpuUtilRecent_[LinuxParser::CPUStates::kIOwait_])   ;
  unsigned long long int systemtime = Format::StoLL(cpuUtilRecent_[LinuxParser::CPUStates::kSystem_])   ;
  unsigned long long int irq =        Format::StoLL(cpuUtilRecent_[LinuxParser::CPUStates::kIRQ_])      ;
  unsigned long long int softIrq =    Format::StoLL(cpuUtilRecent_[LinuxParser::CPUStates::kSoftIRQ_])  ;
  unsigned long long int steal =      Format::StoLL(cpuUtilRecent_[LinuxParser::CPUStates::kSteal_])    ;
  //Prev:
  unsigned long long int usertimeP =   Format::StoLL(cpuUtilPrev_[LinuxParser::CPUStates::kUser_])     ;
  unsigned long long int guestP =      Format::StoLL(cpuUtilPrev_[LinuxParser::CPUStates::kGuest_])    ;
  unsigned long long int nicetimeP =   Format::StoLL(cpuUtilPrev_[LinuxParser::CPUStates::kNice_])     ;
  unsigned long long int guestniceP =  Format::StoLL(cpuUtilPrev_[LinuxParser::CPUStates::kGuestNice_]);
  unsigned long long int idletimeP =   Format::StoLL(cpuUtilPrev_[LinuxParser::CPUStates::kIdle_])     ;
  unsigned long long int ioWaitP =     Format::StoLL(cpuUtilPrev_[LinuxParser::CPUStates::kIOwait_])   ;
  unsigned long long int systemtimeP = Format::StoLL(cpuUtilPrev_[LinuxParser::CPUStates::kSystem_])   ;
  unsigned long long int irqP =        Format::StoLL(cpuUtilPrev_[LinuxParser::CPUStates::kIRQ_])      ;
  unsigned long long int softIrqP =    Format::StoLL(cpuUtilPrev_[LinuxParser::CPUStates::kSoftIRQ_])  ;
  unsigned long long int stealP =      Format::StoLL(cpuUtilPrev_[LinuxParser::CPUStates::kSteal_])    ;


  // from: https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
  // Guest time is already accounted in usertime
  //   Recent
  usertime = usertime - guest;                             // As you see here, it subtracts guest from user time
  nicetime = nicetime - guestnice;                         // and guest_nice from nice time
  // Fields existing on kernels >= 2.6
  // (and RHEL's patched kernel 2.4...)
  unsigned long long int idlealltime = idletime + ioWait;  // ioWait is added in the idleTime
  unsigned long long int systemalltime = systemtime + irq + softIrq;
  unsigned long long int virtalltime = guest + guestnice;
  unsigned long long int totaltime = usertime + nicetime + systemalltime + idlealltime + steal + virtalltime;
  // Prev:
  usertimeP = usertimeP - guestP;                             // As you see here, it subtracts guest from user time
  nicetimeP = nicetimeP - guestniceP;                         // and guest_nice from nice time
  // Fields existing on kernels >= 2.6
  // (and RHEL's patched kernel 2.4...)
  unsigned long long int idlealltimeP = idletimeP + ioWaitP;  // ioWait is added in the idleTime
  unsigned long long int systemalltimeP = systemtimeP + irqP + softIrqP;
  unsigned long long int virtalltimeP = guestP + guestniceP;
  unsigned long long int totaltimeP = usertimeP + nicetimeP + systemalltimeP + idlealltimeP + stealP + virtalltimeP;

  // difference:
  unsigned long long int totald = totaltime - totaltimeP;
  unsigned long long int idled = idlealltime - idlealltimeP;
  if (totald != 0) {
    cpuPercentage = (float)(totald - idled)/(float)totald;
  }
  return cpuPercentage;
}
