#ifndef __TIME_H__
#define __TIME_H__
 
#include <iostream>
#include <string> 

using namespace std;
 
class Time {
private:
    int hour;
    int minute;
public:
    Time();
    Time(int, int);

    void setHour(int);
    void setMinute(int);
    int getHour() const;
    int getMinute() const;

    friend ostream& operator<<(ostream& out, const Time time);
};
 
#endif