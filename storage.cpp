#include "storage.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool saveProgress(string filename, vector<Task>& tasks) {
    ofstream file(filename);
    if (!file.is_open()) return false;
    for (const auto& t : tasks) {
        file << t.topic << " | " << t.subject << " | " << t.deadline
             << " | " << t.priority << " | " << t.status << "\n";
    }
    file.close();
    return true;
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
            t.topic    = topic;
            t.subject  = subject;
            t.deadline = deadline;
            t.priority = stoi(priorityStr);
            t.status   = status;
            tasks.push_back(t);
        }
    }
    file.close();
    return tasks;
}

// Stub: load tasks from a syllabus CSV/text file
vector<Task> loadSyllabus(string filename) {
    // Reuse loadProgress format for now
    return loadProgress(filename);
}

// Stub: load tasks from an exam dates file
vector<Task> loadExamDates(string filename) {
    // Reuse loadProgress format for now
    return loadProgress(filename);
}
