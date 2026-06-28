#ifndef TASK_H
#define TASK_H

#include <string>

using namespace std;

struct Task
{
    string subject;
    string topic;
    string deadline;
    int priority;
    string status;
};

#endif