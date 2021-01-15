#include <string>
#include <iostream>
#include "string.h"
#include "format.h"
#define MAXTIME 360000  // i.e. 100 hours. 99hr:59min:59sec is acceptable but 100hr:00min:00sec is not acceptable
#define HOUR 3600
#define MIN 60


using std::string;

// DONE by BABAK: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
// string Format::ElapsedTime(long seconds[[maybe_unused]]) { return string(); }

string Format::ElapsedTime(long seconds)
{
    char out[10];
    std::string outputStr{};
    seconds %= MAXTIME;
    int hour=seconds/HOUR;
    int second=seconds % HOUR;
    int minute=second/MIN;
    second %= MIN;
    // printf("%.2d:%.2d:%.2d"),hour,minute,second);
    sprintf(out, "%.2d:%.2d:%.2d", hour, minute, second);  // is there a better way of doing this to store it in a std::string directly?
    // std::cout << strlen(out) << std::endl;
    out[strlen(out)] = 0;
    return std::string(out);
}