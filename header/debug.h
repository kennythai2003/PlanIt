#ifndef __DEBUG_H__
#define __DEBUG_H__
#include "time.h"
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

class Debug {
    public:
        bool containsNonDigit(string s) const;
        bool checkLeapYear(int year) const;
        bool isValidMonth(string month) const;
        bool isValidYear(string year) const;
        bool isValidDay(string day, int month, int year) const;
        bool isValidPriority(string priority) const;
        bool isValidHour(string hour) const;
        bool isValidMinute(string minute) const;
        bool isValidTime(Time time) const;
        bool endTimeIsAfterStartTime(Time startTime, Time endTime) const;
        bool isMatchingTimes(Time startTime, Time endTime) const;
        int isInRange(int min, int max, string input) const;
};

#endif