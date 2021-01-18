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

// below is the approach recommended by the Reviewer:
// #include <string>
// #include <iomanip>
// #include "format.h"

// using std::string;

// // INPUT: Long int measuring seconds
// // OUTPUT: HH:MM:SS
// string Format::ElapsedTime(long seconds) {
//   long h = seconds / 3600;
//   long m = (seconds % 3600) / 60;
//   long s = (seconds % 3600 % 60);
//   std::ostringstream elapsedTime;    // important that an output string stream can be used here!
//   elapsedTime << std::setw(2) << std::setfill('0') << h
//               << ":" << std::setw(2) << std::setfill('0') << m
//               << ":" << std::setw(2) << std::setfill('0') << s;
//   return elapsedTime.str();
//  }


int Format::StoI(const std::string& input) {
    int out = 0;
    if (std::all_of(input.begin(), input.end(), isdigit) && (input.size() > 0)) {
        out = stoi(input);
    }
    return out;
}

unsigned long int Format::StoL(const std::string& input) {
    unsigned long int out = 0;
    if (std::all_of(input.begin(), input.end(), isdigit) && (input.size() > 0)) {
        out = stol(input);
    }
    return out;
}

unsigned long long int Format::StoLL(const std::string& input) {
    unsigned long long int out = 0;
    if (std::all_of(input.begin(), input.end(), isdigit) && (input.size() > 0)) {
        out = stoll(input);
    }
    return out;
}

// float Format::StoF(const std::string& input) {
//     float out = 0.0F;
//     if (std::all_of(input.begin(), input.end(), is_numeric) && (input.size() > 0)) {
//         out = stof(input);
//     }
//     return out;
// }