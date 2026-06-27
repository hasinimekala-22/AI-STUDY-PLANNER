#ifndef PLANNER_H
#define PLANNER_H

#include <vector>
#include <string>
#include "task.h"
#include "heap.h"

using namespace std;

class Planner {
private:
    MinHeap taskHeap;

    int calculateDaysRemaining(const string& deadlineDate, const string& currentDate);
    vector<Task> detectSlippage(const vector<Task>& currentTasks, const string& currentDate);
    void replanTasks(vector<Task>& allTasks, const string& currentDate);
    void updateHeap(const vector<Task>& updatedTasks);

public:
    Planner();
    void runReActLoop(vector<Task>& currentTasks, const string& currentDate);
};

#endif
