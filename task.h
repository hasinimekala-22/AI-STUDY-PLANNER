#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>
using namespace std;

struct Task
{
    string topic;
    string subject;
    string deadline;
    int priority;
    string status;
};

#endif