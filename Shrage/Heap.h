#pragma once
#include "Task.h"

class Heap
{
private:
	int size;
	Task* tab;
	int capacity;
public:
	Heap(int n);
	~Heap();
	int parent(int i);
	int left(int i);
	int right(int i);
	void add(Task added);
	void Heapify(int i);
	int getSize();
	Task RemoveRoot();
	int top();
};

