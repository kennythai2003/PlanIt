#include "../header/task.h"

Task::Task() {
    string name = "";
    string description = "";
    Date date;
    Time startTime;
    Time endTime;
    bool priority = false;
}

Task::Task(string name, string description, Date date, Time startTime, Time endTime, bool priority) 
: name(name), description(description), date(date), startTime(startTime), endTime(endTime), priority(priority) {}

string Task::getName() const {
    return this->name;
}

void Task::setName(string name) {
    this->name = name;
}

string Task::getDescription() const {
    return this->description;
}

void Task::setDescription(string description) {
    this->description = description;
}

bool Task::getPriority() const {
    return this->priority;
}

void Task::setPriority(bool priority) {
    this->priority = priority;
}

Date Task::getDate() const {
    return this->date;
}

void Task::setDate(int month, int day, int year) {
    date.setMonth(month);
    date.setDay(day);
    date.setYear(year);
}

Time Task::getStartTime() const {
    return this->startTime;
}

Time Task::getEndTime() const {
    return this->endTime;
}

void Task::setStartTime(int hour, int minute) {
    startTime.setHour(hour);
    startTime.setMinute(minute);
}

void Task::setEndTime(int hour, int minute) {
    endTime.setHour(hour);
    endTime.setMinute(minute);
}

ostream& operator<<(ostream& out, const Task& task){
    Debug debug;

    out << "Name: " << task.getName() << endl;
    out << "Description: " << task.getDescription() << endl;
    out << "Date: " << task.getDate() << endl;
    out << "Time: " << task.getStartTime();
    //Determine whether startTime < endTime, startTime > endTime, startTime == endTime and print Time(s) accordingly 
    if(!debug.endTimeIsAfterStartTime(task.getStartTime(), task.getEndTime())){
        out << " - " << task.getEndTime() << " (next day)" << endl;
    } else if (debug.isMatchingTimes(task.getStartTime(), task.getEndTime())) {
        out << endl;
    } else {
        out << " - " << task.getEndTime() << endl;
    }
    out << "Higher Priority: " << task.getPriority() << endl;
    return out;
}