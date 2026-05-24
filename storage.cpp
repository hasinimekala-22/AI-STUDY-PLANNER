#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;


struct Task {
    string topic;
    string subject;
    string deadline;
    int priority;
    string status; 
};


void saveProgress(string filename, vector<Task>& tasks) {
    ofstream file(filename);
    for (const auto& t : tasks) {
        file << t.topic << " | " << t.subject << " | " << t.deadline << " | " << t.priority << " | " << t.status << "\n";
    }
    file.close();
}

vector<Task> loadProgress(string filename) {
    vector<Task> tasks;
    ifstream file(filename);
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string topic, subject, deadline, priorityStr, status;
        
       
        if (getline(ss, topic, '|') && getline(ss, subject, '|') && 
            getline(ss, deadline, '|') && getline(ss, priorityStr, '|') && 
            getline(ss, status, '|')) {
            
            Task t;
            t.topic = topic;
            t.subject = subject;
            t.deadline = deadline;
            t.priority = stoi(priorityStr); 
            t.status = status;
            tasks.push_back(t);
        }
    }
    file.close();
    return tasks;
}


Task parseGeminiMock() {
    Task t;
    t.topic = "Asymptotic Time Complexity Analysis";
    t.subject = "Computer Science";
    t.deadline = "2026-05-30";
    t.priority = 1;
    t.status = "PENDING";
    return t;
}


int main() {
    cout << "--- Starting Simple AI Study Planner ---" << endl;

 
    Task aiTask = parseGeminiMock();
    cout << "1. Received Task from AI: " << aiTask.topic << endl;

   
    vector<Task> currentWorkspace;
    currentWorkspace.push_back(aiTask);


    cout << "2. Saving data array to progress.txt..." << endl;
    saveProgress("progress.txt", currentWorkspace);


    cout << "3. Reading data back from progress.txt..." << endl;
    vector<Task> savedData = loadProgress("progress.txt");

   
    cout << "\n=== Current Task Array Saved on Disk ===" << endl;
    for(const auto& item : savedData) {
        cout << "Topic:    " << item.topic << endl;
        cout << "Subject:  " << item.subject << endl;
        cout << "Priority: " << item.priority << endl;
    }
    
    return 0;
}
