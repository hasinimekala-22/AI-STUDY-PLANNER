#ifndef PLANNER_H
#define PLANNER_H

#include "task.h"
#include <vector>
#include <string>

using namespace std;

class Planner {
private:
    int calculateDaysRemaining(const string& deadlineDate, const string& currentDate);

public:
    Planner();
    vector<Task> detectSlippage(const vector<Task>& currentTasks, const string& currentDate);
    void replanTasks(vector<Task>& allTasks, const string& currentDate);
    void updateHeap(const vector<Task>& updatedTasks);
    void runReActLoop(vector<Task>& currentTasks, const string& currentDate);
};

#endif