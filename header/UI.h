#ifndef __UI_H__
#define __UI_H__

#include "date.h"
#include "task.h"
#include "time.h"
#include "debug.h"
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
//uncomment to disable assert()
//#define NDEBUG
#include <assert.h>

using namespace std;

class UI {

public:
    UI();
    void setSaveFile(string);
    void launch();

private:
    string fileName;
    vector<Task> taskList;
    void addTask();
    bool loadFromFile();
    vector<Task> search(string&) const;
    void editTask(Task&);
    void deleteTask(int);
    vector<Task> sortByDate(vector<Task>&);
    void sortByPriority();
    void saveToFile(string fileName) const;
    void displayAllTasks() const;
    Date inputDate();
    Time inputStartTime();
    Time inputEndTime();
    bool inputPriority();
    bool getUserInput();
};
#endif