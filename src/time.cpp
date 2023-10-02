#include "../header/time.h"

using namespace std;
 
Time::Time() {
    this->hour = 0;
    this->minute = 0;
}
 
Time::Time(int hour, int minute){
    this->hour = hour;
    this->minute = minute;
}
 
void Time::setHour(int hour)
{
    this->hour = hour;
}

void Time::setMinute(int minute)
{
    this->minute = minute;
}

int Time::getMinute() const
{
    return minute;
}

int Time::getHour() const
{
    return hour;
}

ostream& operator<<(ostream& out, const Time time){
    if(time.getHour() < 10){
        out << "0" << to_string(time.getHour()) << ":";
    } else {
        out << to_string(time.getHour()) << ":";
    }

    if(time.getMinute() < 10){
        out << "0" << to_string(time.getMinute());
    } else {
        out << to_string(time.getMinute());
    }
    return out;
}