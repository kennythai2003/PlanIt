#ifndef __TASK_H__
#define __TASK_H__

#include <iostream>
#include <string>
#include "date.h"
#include "time.h"
#include "debug.h"

using namespace std;

class Task {
    private:
        string name;
        string description;
        Date date;
        Time startTime;
        Time endTime;
        bool priority;
    public:
        Task();
        Task(string, string, Date, Time, Time, bool);

        string getName() const;
        string getDescription() const;
        Date getDate() const; 
        Time getStartTime() const;
        Time getEndTime() const;
        bool getPriority() const;
        
        void setName(string);
        void setDescription(string);
        void setDate(int, int, int);
        void setStartTime(int, int);
        void setEndTime(int, int);
        void setPriority(bool);
        
        friend ostream& operator<<(ostream& out, const Task& task);
};

#endif