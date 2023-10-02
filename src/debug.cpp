#include "../header/debug.h"

using namespace std;

bool Debug::containsNonDigit(string s) const {
    if (s.length() == 0) {
        return true;
    }
    for (int i = 0; i < s.length(); i++) {
        if (!isdigit(s.at(i))) {
            return true;
        }
    }
    return false;
}

bool Debug::checkLeapYear(int year) const {
    //validate leap year
    if (year < 1) {
        return false;
    }
    if (year % 100 == 0)
    {
        if (year % 400 == 0) { return true; }
        return false;
    }
    if (year % 4 == 0) { return true; }
    return false;
}

bool Debug::isValidMonth(string month) const {
    if (month.length() > 2 || containsNonDigit(month) || stoi(month) < 1 || stoi(month) > 12) {
        return false;
    }
    return true;
}

bool Debug::isValidYear(string year) const {
    if (year.length() > 4 || containsNonDigit(year) || stoi(year) < 1) {
        return false;
    }
    return true;
}

bool Debug::isValidDay(string day, int month, int year) const {
    if (day.length() > 2) {
        return false;
    }
    int daysInMonth = 0;
    if (month == 2) {
        if (!checkLeapYear(year)) {
            daysInMonth = 28;
        }
        else {
            daysInMonth = 29;
        }
    }
    else if (((month < 8) && (month % 2 == 1)) || ((month >= 8) && (month % 2 == 0))) {
        daysInMonth = 31;
    }
    else {
        daysInMonth = 30;
    }

    if (containsNonDigit(day) || stoi(day) < 1 || stoi(day) > daysInMonth) {
        return false;
    }
    return true;
}

bool Debug::isValidPriority(string priority) const {
    if (!(priority == "0" || priority == "1")) {
        return false;
    }
    return true;
}

bool Debug::isValidHour(string hour) const {
    if (hour.length() > 2 || containsNonDigit(hour) || stoi(hour) < 0 || stoi(hour) > 23) {
        return false;
    }
    return true;
}

bool Debug::isValidMinute(string minute) const {
    if (minute.length() > 2 || containsNonDigit(minute) || stoi(minute) < 0 || stoi(minute) > 59) {
        return false;
    }
    return true;
}

bool Debug::isValidTime(Time time) const {
    if (time.getHour() > 23 || time.getHour() < 0 || time.getMinute() > 59 || time.getMinute() < 0) {
        return false;
    }
    return true;
}

bool Debug::endTimeIsAfterStartTime(Time startTime, Time endTime) const {
    if (endTime.getHour() < startTime.getHour() || ((endTime.getHour() == startTime.getHour()) && endTime.getMinute() < startTime.getMinute())) {
        return false;
    } else {
        return true;
    }
}

bool Debug::isMatchingTimes(Time startTime, Time endTime) const {
    if (endTime.getHour() == startTime.getHour() && endTime.getMinute() == startTime.getMinute()) {
        return true;
    }
    else {
        return false;
    }
}

int Debug::isInRange(int min, int max, string input) const {
    while (input.length() > 9 || containsNonDigit(input) || (stoi(input) < min || stoi(input) > max)) {
        cout << "INPUT A VALID NUMBER" << endl;
        cout << "> ";
        getline(cin, input, '\n');
        cin.clear();
    }
    return stoi(input);
}