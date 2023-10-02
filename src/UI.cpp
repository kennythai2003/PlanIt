#include "../header/UI.h"

UI::UI() {
    this->fileName = "save.txt";
}

void UI::setSaveFile(string fileName) {
    //for testing purposes
    this->fileName = fileName;
}

void UI::launch() {
    loadFromFile();

    bool quit = false;
    while (!quit) {
        cout << "____________TASKS____________" << endl;
        displayAllTasks();
        cout << "_____________________________" << endl;

        quit = getUserInput();
    }

}

bool UI::getUserInput() {
    Debug debug;

    string userInput = "";
    int intUserInput = -1;

    cout << "TASK MANAGER" << endl
        << "1: Add New Task" << endl
        << "2: Edit Existing Task" << endl
        << "3: Delete Task" << endl
        << "4: Sort Tasks By Date" << endl
        << "5: Sort Tasks By Higher Priority" << endl
        << "6: Search for Task" << endl
        << "7: View all Tasks" << endl
        << "h[number]: Help for Command" << endl
        << "s: SAVE" << endl
        << "q: SAVE AND QUIT" << endl << endl;

    cout << "> ";
    getline(cin, userInput, '\n');
    cin.clear();
    cout << endl;

    while (userInput != "1" && userInput != "2" && userInput != "3" && userInput != "4" && userInput != "5" && userInput != "6" && userInput != "7" && ((userInput.substr(0, 1) != "h" && userInput.substr(0, 1) != "H") || ((userInput.substr(0, 1) == "h" || userInput.substr(0, 1) == "H") && (userInput.substr(1) != "1" && userInput.substr(1) != "2" && userInput.substr(1) != "3" && userInput.substr(1) != "4" && userInput.substr(1) != "5" && userInput.substr(1) != "6" && userInput.substr(1) != "7" && (userInput.substr(1) != "h" && userInput.substr(1) != "H") && (userInput.substr(1) != "s" && userInput.substr(1) != "S") && (userInput.substr(1) != "q" && userInput.substr(1) != "Q")))) && (userInput != "s" && userInput != "S") && (userInput != "q" && userInput != "Q")) {
        cout << "Unrecognized Command: " << userInput << endl;
        cout << "> ";

        getline(cin, userInput, '\n');
        cin.clear();
        cout << endl;
    }

    if (userInput == "1") // add task
    {
        cout << "~~~~~~~~~~~~~ADD~~~~~~~~~~~~~" << endl;
        addTask();
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else if (userInput == "2") // edit task
    {
        cout << "~~~~~~~~~~~~~EDIT~~~~~~~~~~~~~" << endl;
        displayAllTasks();
        if (!taskList.size() == 0) {
            cout << "ENTER NUMBER OF TASK TO BE EDITED" << endl;
            cout << "> ";
            getline(cin, userInput, '\n');
            cin.clear();
            intUserInput = debug.isInRange(1, taskList.size(), userInput);

            // print task to be edited
            cout << "EDITING TASK: " << endl
                << taskList.at(intUserInput - 1) << endl;

            editTask(taskList.at(intUserInput - 1));
        }
        else cout << endl << "CANCELING EDIT" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else if (userInput == "3")
    {
        Debug debug;
        cout << "~~~~~~~~~~~~DELETE~~~~~~~~~~~~" << endl;
        displayAllTasks();
        if (!taskList.size() == 0) {
            cout << "ENTER NUMBER OF TASK TO DELETE" << endl
                << "CAUTION: IRREVERSIBLE" << endl;
            cout << "> ";
            getline(cin, userInput, '\n');
            cin.clear();
            intUserInput = debug.isInRange(1, taskList.size(), userInput);

            // validate input
            string delConfirm = "N";
            cout << "DELETING " << taskList.at(intUserInput - 1).getName() << endl;
            cout << "CONFIRM? (Y/N)" << endl;
            cout << "> ";
            getline(cin, delConfirm, '\n');
            cin.clear();

            if (delConfirm == "Y" || delConfirm == "y") deleteTask(intUserInput - 1);
            else cout << endl << "CANCELING DELETE" << endl;
        }
        else cout << endl << "CANCELING DELETE" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else if (userInput == "4") // sort date
    {
        sortByDate(taskList);
    }
    else if (userInput == "5") // sort priority
    {
        sortByPriority();
    }
    else if (userInput == "6") // search for task
    {
        cout << "~~~~~~~~~~~~SEARCH~~~~~~~~~~~~" << endl;
        cout << "Enter keyword" << endl;
        cout << "> ";
        getline(cin, userInput, '\n');
        cin.clear();

        vector<Task> results = search(userInput);
        // display vector
        cout << "~~~~~~~~~~~~RESULTS~~~~~~~~~~~" << endl;
        if (results.size() == 0) {
            cout << "No Results Found" << endl;
        }
        else {
            for (int resultsIdx = 0; resultsIdx < results.size(); resultsIdx++)
            {
                cout << results.at(resultsIdx) << endl;
            }
        }
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        return getUserInput();
    }
    else if (userInput == "7") // display all tasks
    {
        cout << "____________TASKS____________" << endl;
        displayAllTasks();
        cout << "_____________________________" << endl;

        return getUserInput();
    }
    else if (userInput.substr(0, 1) == "h" || userInput.substr(0, 1) == "H") // help
    {
        cout << "~~~~~~~~~~~~HELP~~~~~~~~~~~~" << endl;
        string cmdHelp = userInput.substr(1);

        if (cmdHelp == "1")
        {
            cout << "Add a new task. You will be prompted for a name, date, start and end time, description, and whether it should have higher priority." << endl;
        }
        else if (cmdHelp == "2")
        {
            cout << "Edit a pre-existing task." << endl;
        }
        else if (cmdHelp == "3")
        {
            cout << "Delete a task. This cannot be undone." << endl;
        }
        else if (cmdHelp == "4")
        {
            cout << "Sort tasks by date." << endl;
        }
        else if (cmdHelp == "5")
        {
            cout << "Sort tasks by order of higher priority. Higher Priority tasks (denoted by a 1 under 'higher priority') will be displayed first in the list and then ordered by Date if there are multiple." << endl;
        }
        else if (cmdHelp == "6")
        {
            cout << "Search for a task using a keyword. Enter a keyword that would be in the Title or Description of the task, any matching results will be listed." << endl;
        }
        else if (cmdHelp == "7")
        {
            cout << "View the current list of tasks." << endl;
        }
        else if (cmdHelp == "h" || cmdHelp == "H")
        {
            cout << "helpception" << endl;
        }
        else if (cmdHelp == "s" || cmdHelp == "S")
        {
            cout << "Save the current list of tasks. Please DO NOT edit the save file as it may lead to unknown results." << endl;
        }
        else if (cmdHelp == "q" || cmdHelp == "Q")
        {
            cout << "Save the current list of tasks and quit. Please DO NOT edit the save file as it may lead to unknown results." << endl;
        }
        else
        {
            cout << "you have gone against all odds and bypassed our error checks.\nWell done." << endl;
        }
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        return getUserInput();
    }
    else if (userInput == "s" || userInput == "S") // save
    {
        cout << "~~~~~~~~~~~~SAVE~~~~~~~~~~~~" << endl;
        cout << "Saving..." << endl;
        saveToFile(fileName);
        cout << "Saved." << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        return getUserInput();
    }
    else if (userInput == "q" || userInput == "Q") // save + quit
    {
        cout << "~~~~~~~~~~~~QUIT~~~~~~~~~~~~" << endl;
        cout << "Saving..." << endl;
        saveToFile(fileName);
        cout << "Saved." << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        return true;
    }
    else // other, unrecognized
    {
        cout << "you have gone against all odds and bypassed our error checks.\nWell done." << endl;
    }
    return false;
}

vector<Task> UI::search(string& keyword) const
{
    vector<Task> returnVector = {};
    if (taskList.size() == 0) return returnVector;

    for (int idx = 0; idx < taskList.size(); idx++)
    {
        Task currTask = taskList.at(idx);

        if (currTask.getName().find(keyword) != -1) // found in name
        {
            returnVector.push_back(taskList.at(idx));
            continue;
        }
        if (currTask.getDescription().find(keyword) != -1)
        {
            returnVector.push_back(taskList.at(idx));
            continue;
        }
    }
    return returnVector;
}

void UI::editTask(Task& task)
{
    Debug debug;

    cout << "What would you like to edit?" << endl
        << "1: Task Name" << endl
        << "2: Task Description" << endl
        << "3: Task Date" << endl
        << "4: Task Start Time" << endl
        << "5: Task End Time" << endl
        << "6: Task Priority" << endl
        << "0: Don't edit" << endl;

    string answer;
    cout << "> ";
    getline(cin, answer, '\n');
    cin.clear();
    // check validation
    int answerInt = debug.isInRange(0, 6, answer);

    switch (answerInt)
    {
    case 0: // don't edit
    {
        break;
    }
    case 1: // name
    {
        cout << "MODIFYING TASK NAME" << endl
            << "OLD TASK NAME: " << task.getName() << endl
            << "Enter new name: " << endl;

        cout << "> ";
        getline(cin, answer, '\n');
        cin.clear();

        task.setName(answer);
        break;
    }
    case 2: // desc
    {
        cout << "MODIFYING TASK DESCRIPTION" << endl
            << "OLD TASK DESCRIPTION: " << task.getDescription() << endl
            << "Enter new description: " << endl;
        cout << "> ";
        getline(cin, answer, '\n');
        cin.clear();

        task.setDescription(answer);
        break;
    }
    case 3: // date
    {
        cout << "MODIFYING TASK DATE" << endl
            << "OLD TASK DATE: " << task.getDate() << endl
            << "Enter year: " << endl;
        cout << "> ";
        getline(cin, answer, '\n');
        cin.clear();
        // check validation
        int newYear = debug.isInRange(1, 9999, answer);

        cout << "Enter month (1-12): " << endl;
        cout << "> ";
        getline(cin, answer, '\n');
        cin.clear();
        // check validation
        int newMonth = debug.isInRange(1, 12, answer);

        cout << "Enter day: " << endl;
        cout << "> ";
        getline(cin, answer, '\n');
        cin.clear();
        // check validation
        while (debug.containsNonDigit(answer) || !debug.isValidDay(answer, newMonth, newYear)) {
            cout << "INPUT A VALID DAY" << endl;
            cout << "> ";
            getline(cin, answer, '\n');
            cin.clear();
        }
        int newDay = stoi(answer);
        task.setDate(newMonth, newDay, newYear);
        break;
    }
    case 4: // task start time
    {
        cout << "MODIFYING TASK START TIME" << endl
            << ""
            << "Enter new starting hour (0-23): " << endl;
        cout << "> ";
        getline(cin, answer, '\n');
        cin.clear();
        // check validation
        int newStartHour = debug.isInRange(0, 23, answer);

        cout << "Enter new starting minute (0-59): " << endl;
        cout << "> ";
        getline(cin, answer, '\n');
        cin.clear();
        // check validation
        int newStartMinute = debug.isInRange(0, 59, answer);

        task.setStartTime(newStartHour, newStartMinute);
        break;
    }
    case 5: // task end time
    {
        cout << "Enter new ending hour (0-23): " << endl;
        cout << "> ";
        getline(cin, answer, '\n');
        cin.clear();
        // check validation
        int newEndHour = debug.isInRange(0, 23, answer);

        cout << "Enter new ending minute (0-59): " << endl;
        cout << "> ";
        getline(cin, answer, '\n');
        cin.clear();
        // check validation
        int newEndMinute = debug.isInRange(0, 59, answer);

        task.setEndTime(newEndHour, newEndMinute);
        break;
    }
    case 6: // priority
    {
        cout << "MODIFYING TASK PRIORITY" << endl
            << "Should this task have higher priority? (0/1): " << endl;
        cout << "> ";
        getline(cin, answer, '\n');
        cin.clear();
        // check validation
        answerInt = debug.isInRange(0, 1, answer);

        task.setPriority(answerInt);
        break;
    }
    }
}

void UI::deleteTask(int taskNumber) {
    taskList.erase(taskList.begin() + taskNumber);
    saveToFile(fileName);
}

void UI::addTask() {
    string taskName = "";
    cout << "Please enter task name: ";
    getline(cin, taskName, '\n');
    cin.clear();
    cout << endl;

    string taskDesc = "";
    cout << "Please enter task description: ";
    getline(cin, taskDesc, '\n');
    cin.clear();
    cout << endl;

    Date taskDate = inputDate();
    Time startTime = inputStartTime();
    Time endTime = inputEndTime();
    bool priority = inputPriority();

    Task newTask(taskName, taskDesc, taskDate, startTime, endTime, priority);
    cout << newTask << endl;
    taskList.push_back(newTask);
    saveToFile(fileName);
}

vector<Task> UI::sortByDate(vector<Task>& task) { 
    if(task.size() == 0){
        return task;
    }
    for (int i=0; i < task.size() - 1; i++)
    {
            for (int j = i + 1; j < task.size(); j++)
            {
                if (task.at(i).getDate().getYear() > task.at(j).getDate().getYear())
                {
                    swap(task.at(j), task.at(i));
                }
                else if (task.at(i).getDate().getYear() == task.at(j).getDate().getYear() && task.at(i).getDate().getMonth() > task.at(j).getDate().getMonth())
                {
                    swap(task.at(j), task.at(i));
                }
                else if (task.at(i).getDate().getYear() == task.at(j).getDate().getYear() && task.at(i).getDate().getMonth() == task.at(j).getDate().getMonth() && task.at(i).getDate().getDay() > task.at(j).getDate().getDay())
                {
                    swap(task.at(j), task.at(i));
                }
                else if (task.at(i).getDate().getYear() == task.at(j).getDate().getYear() && task.at(i).getDate().getMonth() == task.at(j).getDate().getMonth() && task.at(i).getDate().getDay() == task.at(j).getDate().getDay() && task.at(i).getStartTime().getHour() > task.at(j).getStartTime().getHour())
                {
                    swap(task.at(j), task.at(i));
                }
                else if (task.at(i).getDate().getYear() == task.at(j).getDate().getYear() && task.at(i).getDate().getMonth() == task.at(j).getDate().getMonth() && task.at(i).getDate().getDay() == task.at(j).getDate().getDay() && task.at(i).getStartTime().getHour() == task.at(j).getStartTime().getHour() && task.at(i).getStartTime().getMinute() > task.at(j).getStartTime().getMinute())
                {
                    swap(task.at(j), task.at(i));
                }
            }
    }
    return task;
}

void UI::sortByPriority() {
    if(taskList.size() == 0){
        return;
    }
    vector<Task> isPriority;
    vector<Task> noPriority;
    for(int i = 0; i < taskList.size(); i++){
        if(taskList.at(i).getPriority()){
            isPriority.push_back(taskList.at(i));
        } else {
            noPriority.push_back(taskList.at(i));
        }
    }

    isPriority = sortByDate(isPriority);
    noPriority = sortByDate(noPriority);

    for(int i = 0; i < noPriority.size(); i++){
        isPriority.push_back(noPriority.at(i));
    }

    taskList = isPriority;
}

void UI::saveToFile(string fileName) const {
    ofstream out(fileName);

    if (!out.is_open()) {
        cout << "[ERROR] - FILE COULD NOT BE FOUND" << endl;
    }
    else {
        //TEMPLATE for save file
        // "{\n";
        // "NAME\n";
        // "DESC\n";
        // "MM\n";
        // "DD\n";
        // "YYYY\n";
        // "HH\n";
        // "MM\n";
        // "EHH\n";
        // "EMM\n";
        // "P\n";
        // "}\n";

        for (int i = 0; i < taskList.size(); i++) {
            out << "{\n";
            out << taskList.at(i).getName() << "\n";
            out << taskList.at(i).getDescription() << "\n";
            out << taskList.at(i).getDate().getMonth() << "\n";
            out << taskList.at(i).getDate().getDay() << "\n";
            out << taskList.at(i).getDate().getYear() << "\n";
            out << taskList.at(i).getStartTime().getHour() << "\n";
            out << taskList.at(i).getStartTime().getMinute() << "\n";
            out << taskList.at(i).getEndTime().getHour() << "\n";
            out << taskList.at(i).getEndTime().getMinute() << "\n";
            out << taskList.at(i).getPriority() << "\n";
            out << "}\n";
        }
    }
}

bool UI::loadFromFile() {
    ifstream fin(fileName);
    Task currTask;
    assert((fin.is_open()) && "[ERROR] - COULDN'T OPEN FILE");
    Debug debug;
    string curr;
    while (fin >> curr) {
        //validate start of task
        if (curr == "{") {
            //load Name
            fin.ignore();
            getline(fin, curr, '\n');
            currTask.setName(curr);

            //load Description
            getline(fin, curr, '\n');
            currTask.setDescription(curr);

            //load Date
            //validate Month
            fin >> curr;
            int month = 0;
            assert((stoi(curr) >= 1 && stoi(curr) <= 12) && "[ERROR] - INVALID MONTH");
            month = stoi(curr);
            //validate Day
            fin >> curr;
            int day = 0;
            assert((((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (stoi(curr) >= 1 && stoi(curr) <= 31)) || ((month == 4 || month == 6 || month == 9 || month == 11) && (stoi(curr) >= 1 && stoi(curr) <= 30)) || ((month == 2) && (stoi(curr) >= 1 && stoi(curr) <= 29))) && "[ERROR] - INVALID DAY");
            day = stoi(curr);
            //validate Year
            fin >> curr;
            int year = 0;
            assert((stoi(curr) >= 1) && "[ERROR] - INVALID YEAR");
            year = stoi(curr);
            //validate leap year
            if (!debug.checkLeapYear(year)) {
                assert(!(month == 2 && day >= 29) && "[ERROR] - NOT LEAP YEAR");
            }
            currTask.setDate(month, day, year);

            //load Times
            //validate startHour
            fin >> curr;
            int startHour = 0;
            assert((stoi(curr) >= 0 && stoi(curr) <= 23) && "[ERROR] - INVALID START HOUR");
            startHour = stoi(curr);
            //validate startMinute
            fin >> curr;
            int startMinute = 0;
            assert((stoi(curr) >= 0 && stoi(curr) <= 59) && "[ERROR] - INVALID START MINUTE");
            startMinute = stoi(curr);
            currTask.setStartTime(startHour, startMinute);
            //validate endHour
            fin >> curr;
            int endHour = 0;
            assert(((stoi(curr) >= 0 && stoi(curr) <= 23)) && "[ERROR] - INVALID END HOUR");
            endHour = stoi(curr);
            //validate endMinute
            fin >> curr;
            int endMinute = 0;
            assert(((stoi(curr) >= 0 && stoi(curr) <= 59)) && "[ERROR] - INVALID END MINUTE");
            endMinute = stoi(curr);
            currTask.setEndTime(endHour, endMinute);

            //load Priority
            fin >> curr;
            int priority = 0;
            assert((stoi(curr) == 0 || stoi(curr) == 1) && "[ERROR] - INVALID PRIORITY");
            priority = stoi(curr);
            currTask.setPriority(priority);
            //validate end of task
            fin >> curr;
            if (curr == "}") {
                taskList.push_back(currTask);
            }
            else {
                return false;
            }
        }
    }
    return true;
}

void UI::displayAllTasks() const
{
    if (taskList.size() == 0) {
        cout << endl << endl << "You don't have any Tasks.\nEnter '1' to add one!" << endl << endl;
    }
    else {
        for (int idx = 0; idx < taskList.size(); idx++)
        {
            cout << (idx + 1) << ". " << endl << taskList.at(idx) << endl;
        }
    }
}

Date UI::inputDate() {

    Debug debug;
    string taskMonth = "";
    cout << "Please enter task month (1-12): ";
    getline(cin, taskMonth, '\n');
    cin.clear();
    cout << endl;

    while (cin.fail() || !debug.isValidMonth(taskMonth)) {
        cout << "Invalid month" << endl;
        cout << "Please enter task month (1-12): ";
        getline(cin, taskMonth, '\n');
        cin.clear();
        cout << endl;
    }
    int taskMonthInt = stoi(taskMonth);

    string taskYear = "";
    cout << "Please enter task year: ";
    getline(cin, taskYear, '\n');
    cin.clear();
    cout << endl;
    while (cin.fail() || !debug.isValidYear(taskYear)) {
        cout << "Invalid year" << endl;
        cout << "Please enter task year: ";
        getline(cin, taskYear, '\n');
        cin.clear();
        cout << endl;
    }
    int taskYearInt = stoi(taskYear);

    string taskDay = "";
    cout << "Please enter task day: ";
    getline(cin, taskDay, '\n');
    cin.clear();
    cout << endl;

    while (cin.fail() || !debug.isValidDay(taskDay, taskMonthInt, taskYearInt)) {
        cout << "Invalid day" << endl;
        cout << "Please enter task day: ";
        getline(cin, taskDay, '\n');
        cin.clear();
        cout << endl;
    }
    int taskDayInt = stoi(taskDay);

    Date taskDate(taskMonthInt, taskDayInt, taskYearInt);

    return taskDate;
}

Time UI::inputStartTime() {

    Debug debug;
    string taskStartHour = "";
    cout << "Please enter task start hour (0-23): ";
    getline(cin, taskStartHour, '\n');
    cin.clear();
    cout << endl;

    while (cin.fail() || !debug.isValidHour(taskStartHour)) {
        cout << "Invalid start hour" << endl;
        cout << "Please enter task start hour (0-23): ";
        getline(cin, taskStartHour, '\n');
        cin.clear();
        cout << endl;
    }
    int taskStartHourInt = stoi(taskStartHour);

    string taskStartMinute = "";

    cout << "Please enter task start minute (0-59): ";
    getline(cin, taskStartMinute, '\n');
    cin.clear();
    cout << endl;

    while (cin.fail() || !debug.isValidMinute(taskStartMinute)) {
        cout << "Invalid start minute" << endl;
        cout << "Please enter task start minute (0-59): ";
        getline(cin, taskStartMinute, '\n');
        cin.clear();
        cout << endl;
    }
    int taskStartMinuteInt = stoi(taskStartMinute);

    Time startTime(taskStartHourInt, taskStartMinuteInt);

    return startTime;
}

Time UI::inputEndTime() {

    Debug debug;
    string taskEndHour = "";
    cout << "Please enter task end hour (0-23): ";
    getline(cin, taskEndHour, '\n');
    cin.clear();
    cout << endl;

    while (cin.fail() || !debug.isValidHour(taskEndHour)) {
        cout << "Invalid end hour" << endl;
        cout << "Please enter task end hour (0-23): ";
        getline(cin, taskEndHour, '\n');
        cin.clear();
        cout << endl;
    }
    int taskEndHourInt = stoi(taskEndHour);

    string taskEndMinute = "";

    cout << "Please enter task end minute (0-59): ";
    getline(cin, taskEndMinute, '\n');
    cin.clear();
    cout << endl;

    while (cin.fail() || !debug.isValidMinute(taskEndMinute)) {
        cout << "Invalid end minute" << endl;
        cout << "Please enter task end minute (0-59): ";
        getline(cin, taskEndMinute, '\n');
        cin.clear();
        cout << endl;
    }
    int taskEndMinuteInt = stoi(taskEndMinute);

    Time endTime(taskEndHourInt, taskEndMinuteInt);

    return endTime;
}

bool UI::inputPriority() {

    Debug debug;
    string taskPriorityInput = "";
    cout << "Should this task have higher priority? (0/1): ";
    getline(cin, taskPriorityInput, '\n');
    cin.clear();
    cout << endl;
    while (cin.fail() || !debug.isValidPriority(taskPriorityInput)) {
        cout << "Invalid priority" << endl;
        cout << "Should this task have higher priority? (0/1): ";
        getline(cin, taskPriorityInput, '\n');
        cin.clear();
        cout << endl;
    }
    if (taskPriorityInput == "1") {
        return true;
    }
    else {
        return false;
    }
}