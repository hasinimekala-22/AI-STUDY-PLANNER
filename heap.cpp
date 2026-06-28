#include "heap.h"
#include <iostream>
using namespace std;

int MinHeap::parent(int index) {
    return (index - 1) / 2;
}

int MinHeap::leftChild(int index) {
    return (2 * index) + 1;
}

int MinHeap::rightChild(int index) {
    return (2 * index) + 2;
}

void MinHeap::insertTask(Task task) {
    heap.push_back(task);
    heapifyUp(heap.size() - 1);
}

Task MinHeap::removeMin() {
    if (heap.empty()) {
        cout << "Heap is empty!" << endl;
        return Task();
    }

    Task minTask = heap[0];
    heap[0] = heap.back();
    heap.pop_back();

    if (!heap.empty()) {
        heapifyDown(0);
    }

    return minTask;
}

void MinHeap::heapifyUp(int index) {
    while (index > 0 && heap[index].priority < heap[parent(index)].priority) {
        swap(heap[index], heap[parent(index)]);
        index = parent(index);
    }
}

void MinHeap::heapifyDown(int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < heap.size() && heap[left].priority < heap[smallest].priority) {
        smallest = left;
    }

    if (right < heap.size() && heap[right].priority < heap[smallest].priority) {
        smallest = right;
    }

    if (smallest != index) {
        swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

void MinHeap::displayHeap() {
    if (heap.empty()) {
        cout << "Heap is empty!" << endl;
        return;
    }

    for (const Task& task : heap) {
        cout
<< task.subject << " | "
<< task.topic << " | "
<< task.deadline << " | "
<< task.status << "\n";
    }
}

bool MinHeap::isEmpty() {
    return heap.empty();
}
vector<Task>& MinHeap::getTasks()
{
    return heap;
}
