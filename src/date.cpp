#include "../header/date.h"

Date::Date() {
   this->month = 1;
   this->day = 1;
   this->year = 1;
}
 
Date::Date(int month, int day, int year){
   this->month = month;
   this->day = day;
   this->year = year;
}
 
void Date::setMonth(int month)
{
   this->month = month;
}
 
void Date::setDay(int day)
{
   this->day = day;
}
 
void Date::setYear(int year)
{
   this->year = year;
}
 
int Date::getMonth() const
{
   return this->month;
}
 
int Date::getDay() const
{
   return this->day;
}
 
int Date::getYear() const
{
   return this->year;
}

ostream& operator<<(ostream& out, const Date date){
   out << to_string(date.getMonth()) << "/";
   if(date.getDay() < 10){
      out << "0" << to_string(date.getDay()) << "/";
   } else {
      out << to_string(date.getDay()) << "/";
   }
   if(date.getYear() < 10){
      out << "000" << to_string(date.getYear());
   } else if(date.getYear() < 100) {
      out << "00" << to_string(date.getYear());
   } else if(date.getYear() < 1000) {
      out << "0" << to_string(date.getYear());
   } else {
      out << to_string(date.getYear());
   }

    return out;
}