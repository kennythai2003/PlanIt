#ifndef __DATE_H__
#define __DATE_H__
 
#include <iostream>
#include <string>
 
using namespace std;
 
class Date {
private:
    int month;
    int day;
    int year;

public:
    Date();
    Date(int, int, int);
 
    void setMonth(int);
    void setDay(int);
    void setYear(int);
    int getMonth() const;
    int getDay() const;
    int getYear() const;

    friend ostream& operator<<(ostream& out, const Date date);
};
 
#endif