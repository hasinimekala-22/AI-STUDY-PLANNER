#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "task.h"

using namespace std;

class MinHeap {
private:
    vector<Task> heap;

    int parent(int index);
    int leftChild(int index);
    int rightChild(int index);

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void insertTask(Task task);
    Task removeMin();
    void displayHeap();
    bool isEmpty();
};

#endif
