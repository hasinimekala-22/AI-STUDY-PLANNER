#ifndef STORAGE_H
#define STORAGE_H

#include "task.h"

#include <vector>
#include <string>

using namespace std;

vector<Task> loadTasks(const string& filename);

void saveTasks(
    const vector<Task>& tasks,
    const string& filename
);

void exportPlan(const vector<Task>& tasks);

#endif