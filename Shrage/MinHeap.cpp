#include "MinHeap.h"
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;


MinHeap::MinHeap(int n)
{
	tab = new Task[n];
	size = 0;
	capacity = n;
}


MinHeap::~MinHeap()
{
}

int MinHeap::parent(int i)
{
	return i / 2;
}

int MinHeap::left(int i)
{
	return 2 * i;
}

int MinHeap::right(int i)
{
	return 2 * i + 1;
}

void MinHeap::add(Task added)
{
	if (capacity == size)
	{
		cout << "stos jest pelny" << endl;
		return;
	}

	tab[size] = added;
	int k = size;
	size++;
	while (k != 0 && tab[parent(k)].r > tab[k].r)
	{
		swap(tab[k], tab[parent(k)]);
		k = parent(k);
	}
}

void MinHeap::Heapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (tab[l].r < tab[i].r && l < size)
	{
		smallest = l;
	}
	if (tab[r].r < tab[smallest].r && r < size)
	{
		smallest = r;
	}
	if (smallest != i)
	{
		swap(tab[i], tab[smallest]);
		Heapify(smallest);
	}
}

int MinHeap::getSize()
{
	return this->size;
}

Task MinHeap::RemoveRoot()
{ 
	if (size == 1)
	{
		size--;
		return tab[0];
	}
	Task root = tab[0];
	tab[0] = tab[size - 1];
	size--;
	Heapify(0);
	return root;

}

int MinHeap::top()
{
	return tab[0].r;
}

