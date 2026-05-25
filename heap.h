#ifndef HEAP_H
#define HEAP_H

#include "task.h"
#include <vector>
using namespace std;

class MinHeap {
private:
    vector<Task> heap;

    int parent(int index);
    int leftChild(int index);
    int rightChild(int index);

public:
    void insertTask(Task task);
    Task removeMin();
    void heapifyUp(int index);
    void heapifyDown(int index);
    void displayHeap();
    bool isEmpty();
};

#endif
