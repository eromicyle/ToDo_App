#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Task {
    private:
        string taskName, taskDescription;
        bool completed;
    public:
        Task(const string& taskName, const string& taskDescription)
        : taskName(taskName)
        , taskDescription(taskDescription)
        , completed(false)
        {
        }

        string getName() const {
            return taskName;
        }
        string getDescription() const {
            return taskDescription;
        }
        bool isComplete() const {
            return completed;
        }

        void setName(const string& taskName) {
            this->taskName=taskName;
        }
        void setDescription(const string& taskDescription) {
            this->taskDescription=taskDescription;
        }
        void markCompleted() {
            completed = true;
        }

        void displayTask();
};

class ToDoList {
    private:
        vector<Task> tasks;
        int taskNumber;
        char userInput;
    public:
        void displayMenu();
        void addTask();
        void deleteTask();
        void editTask();
        void markTaskCompleted();
        void displayTasks();
        void runProgram();
        void saveTasksToFile();
        void loadTasksFromFile();
};

int main() {

    ToDoList toDoList;
    toDoList.runProgram();

    cin.get();
    return 0;
}

void Task::displayTask() {
    cout << taskName << " (" 
         << (completed ? "completed" : "pending") 
         << ")" << endl 
         << "Description: " << taskDescription << endl;
}


void ToDoList :: displayMenu() {
    cout << "======= Home =======" << endl << endl;

    while(true) {
        
        cout << endl;
        cout << "1) Add Task." << endl;
        cout << "2) Edit Task." << endl;
        cout << "3) Delete Task." << endl;
        cout << "4) Mark Task as Completed." << endl;
        cout << "5) Display all Tasks." << endl;
        cout << "6) Exit." << endl;
        cout << "Enter your Choice (1-6) :: ";
        cin >> userInput;

        switch (userInput) {
        case '1': addTask(); break;
        case '2': editTask(); break;
        case '3': deleteTask(); break;
        case '4': markTaskCompleted(); break;
        case '5': displayTasks(); break;
        case '6':
            cout << "Exiting Program...";
            exit(0);
            break;
        default:
            cout << "Invalid Selection... Select option (1-6)... ";
            continue;
        }
     }
}
    

void ToDoList :: addTask() {
    cout << "======= Add Task =======" << endl << endl;
    string name, description;
    cout << "Enter the Task Name :> ";
    cin >> ws; getline(cin, name);
    cout << endl << "Enter the Description \n> ";
    cin >> ws; getline(cin, description);

    tasks.emplace_back(name, description);
    saveTasksToFile();
    cout << endl << "Task Added Successfully..." << endl;
}

void ToDoList :: deleteTask() {
    cout << "======= Delete Task =======" << endl << endl;

    if(tasks.empty()) {
        cout << "No Task to delete...";
        return;
    }

    for(int i=0; i < tasks.size(); ++i) {
        cout << "Task " << i+1 << " " << tasks[i].getName() << endl;
    }
    
    while(true) {
        cout << "Enter the Task number you want to Delete :: ";
        cin >> taskNumber;

        if(taskNumber >= 1 && taskNumber <= tasks.size()) {
            tasks.erase(tasks.begin() + taskNumber - 1);
            saveTasksToFile();
            cout << "Task Deleted Successfully..." << endl;
            break;
        } else {
            cout << "Invalid Task Number Selected... \nDo you want to try again? (Y/n) :: ";
            cin >> userInput;
        }

        if(userInput == 'N' || userInput == 'n') {
            cout << "Canceling Deletion..." << endl;
            break;
        } else if(userInput != 'Y' && userInput != 'y') {
            cout << "Invalid Input... Try again." << endl;
        }
    }

}

void ToDoList :: editTask() {
    string name, description;
    cout << "======= Edit Task =======" << endl << endl;

    if(tasks.empty()) {
        cout << "No Task to Edit...";
        return;
    }

    for(int i=0; i < tasks.size(); ++i) {
        cout << "Task " << i+1 << " " << tasks[i].getName() << endl;
    }

    while(true) {
        cout << "Enter the Task number you want to Edit :: ";
        cin >> taskNumber;

        if(taskNumber >= 1 && taskNumber <= tasks.size()) {
            Task& task = tasks[taskNumber - 1];
            cout << "Enter the new Task Name :: ";
            cin >> ws; getline(cin, name);
            cout << "Enter the new Task Description \n:> ";
            cin >> ws; getline(cin, description);

            task.setName(name);
            task.setDescription(description);
            saveTasksToFile();

            cout << "Task updated successfully!" << endl;
            break;

        } else {
            cout << "Invalid Task Number Selected... \nDo you want to try again? (Y/n) :: ";
            cin >> userInput;
        }

        if(userInput == 'N' || userInput == 'n') {
            cout << "Canceling Deletion..." << endl;
            break;
        } else if(userInput != 'Y' && userInput != 'y') {
            cout << "Invalid Input... Try again." << endl;
        }
    }
}

void ToDoList :: markTaskCompleted() {
    cout << "======= Task Completed/Pending =======" << endl << endl;

    if(tasks.empty()) {
        cout << "No Task to Edit...";
        return;
    }

    for(int i=0; i < tasks.size(); ++i) {
        cout << "Task " << i+1 << " " << tasks[i].getName() << endl;
    }

    while(true) {
        cout << "Enter the Task number you want to mark as completed :: ";
        cin >> taskNumber;

        if(taskNumber >= 1 && taskNumber <= tasks.size()) {
            tasks[taskNumber -1].markCompleted();
            saveTasksToFile();
            cout << "Task Marked as Completed successfully!" << endl;
            break;
        } else {
            cout << "Invalid Task Number Selected... \nDo you want to try again? (Y/n) :: ";
            cin >> userInput;
        }

        if(userInput == 'N' || userInput == 'n') {
            cout << "Canceling Deletion..." << endl;
            break;
        } else if(userInput != 'Y' && userInput != 'y') {
            cout << "Invalid Input... Try again." << endl;
        }
    }
}

void ToDoList :: displayTasks() {
    cout << "======= Displaying Tasks =======" << endl << endl;

    if(tasks.empty()) {
        cout << "No Task to Display...";
        return;
    }

    for (int i = 0; i < tasks.size(); ++i) {
        cout << "Task " << i + 1 << ":\n";
        tasks[i].displayTask();
        cout << "------------------------\n";
        cout << endl;
    }


    cout << "All Tasks Displayed Successfully" << endl;
}

void ToDoList :: runProgram() {
    loadTasksFromFile();
    displayMenu();
}

void ToDoList :: saveTasksToFile() {
    fstream taskFile("userTask.txt", ios::out | ios::trunc);
    if(!taskFile.is_open()) {
        cerr << "Error: Could not open the file for writing..." << endl;
        exit(1);
    }
    for(const Task& task : tasks) {
        taskFile << task.getName() << "|"
                 << task.getDescription() << "|"
                 << task.isComplete() << endl;
    }
    taskFile.close();
}

void ToDoList::loadTasksFromFile() {
    ifstream taskFile("userTask.txt");
    if (!taskFile.is_open()) {
        cerr << "Error: Could not open the file for reading..." << endl;
        return;
    }

    tasks.clear();
    string line;

    while (getline(taskFile, line)) {
        if (line.empty()) continue;

        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos) {
            cerr << "Warning: Malformed line skipped." << endl;
            continue;
        }

        string name = line.substr(0, pos1);
        string description = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string completedStr = line.substr(pos2 + 1);

        Task task(name, description);
        if (completedStr == "1") task.markCompleted();

        tasks.push_back(task);
    }

    taskFile.close();
}
