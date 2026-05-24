#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <string>
#include "task.h"
using namespace std;
vector<Task> loadSyllabus(string filename);
vector<Task> loadExamDates(string filename);
bool saveProgress(string filename, vector<Task>& tasks);
vector<Task> loadProgress(string filename);

#endif
