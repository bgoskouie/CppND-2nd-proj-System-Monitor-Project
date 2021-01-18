#include <iostream>
#include "format.h"
#include "linux_parser.h"

int main()
{
    std::cout << "Elapsed time 5000 is: " << Format::ElapsedTime(5000) << std::endl;
    std::cout << "Elapsed time 5000 is: " << Format::ElapsedTime(359999) << std::endl;
    std::cout << "Elapsed time 5000 is: " << Format::ElapsedTime(360000) << std::endl;
    std::cout << "Elapsed time 5000 is: " << Format::ElapsedTime(360059) << std::endl;
    std::cout << "Elapsed time 5000 is: " << Format::ElapsedTime(360060) << std::endl;


    std::cout << "Linux Parser Operating System: " <<  LinuxParser::OperatingSystem() << std::endl;
    std::cout << "Linux Parser Kernel: " <<  LinuxParser::Kernel() << std::endl;
    std::cout << "Linux Parser RunningProcesses: " <<  LinuxParser::RunningProcesses() << std::endl;
    std::cout << "Linux Parser Total Processes: " <<  LinuxParser::TotalProcesses() << std::endl;
    std::cout << "Linux Parser UpTime: " <<  LinuxParser::UpTime() << std::endl;
    std::cout << "Linux Parser Memory Utilization: " <<  LinuxParser::MemoryUtilization() << std::endl;
    std::cout << "Linux Parser pids are as follows: " << std::endl;
    std::vector<int> pids = LinuxParser::Pids();
    // for (auto pid : pids)
    // {
    //     std::cout << "Linux Parser pid: " <<  pid << std::endl;
    // }
    std::cout << "Linux Parser pid[0]: " << pids[0] << std::endl;

    std::vector<std::string> cpuutil = LinuxParser::CpuUtilization();
    for (auto cput : cpuutil)
    {
        std::cout << "Linux Parser cpuutil: " <<  cput << std::endl;
    }
    std::cout << "Linux Parser NumberOfCpus:       " <<  LinuxParser::NumberOfCpus()    << std::endl;
    std::cout << "Linux Parser Jiffies:            " <<  LinuxParser::Jiffies()         << std::endl;
    std::cout << "Linux Parser ActiveJiffies:      " <<  LinuxParser::ActiveJiffies()   << std::endl;
    std::cout << "Linux Parser ActiveJiffied(pid): " <<  LinuxParser::ActiveJiffies(5)  << std::endl;  // int pid is input
    std::cout << "Linux Parser IdleJiffies:        " <<  LinuxParser::IdleJiffies()     << std::endl;

    // Processes
    int pid = 26208;  //111626;  //80390;  //65534;//4644;  //2843;
    std::cout << "Linux Parser Command:     " <<   LinuxParser::Command(pid)  << std::endl;
    std::cout << "Linux Parser Ram:         " <<   LinuxParser::Ram(pid)      << std::endl;
    std::cout << "Linux Parser Uid:         " <<   LinuxParser::Uid(pid)      << std::endl;
    std::cout << "Linux Parser User:        " <<   LinuxParser::User(pid)     << std::endl;
    std::cout << "Linux Parser UpTime:      " <<   LinuxParser::UpTime(pid)   << std::endl;
    std::cout << "Linux Parser UpTimeString:      " <<   LinuxParser::UpTimeString(pid)   << std::endl;
    std::cout << "Linux Parser ProcessUtilization:      " <<   LinuxParser::ProcessUtilization(pid)   << std::endl;

    std::cin.get();
    return 0;
}