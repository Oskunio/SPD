#pragma once
#include "Task.h"
class MinHeap
{
private:
	int size;
	Task* tab;
	int capacity;
public:
	MinHeap(int n);
	~MinHeap();
	int parent(int i);
	int left(int i);
	int right(int i);
	void add(Task added);
	void Heapify(int i);
	int getSize();
	Task RemoveRoot();
	int top();
	
};

