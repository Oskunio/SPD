#include "Heap.h"
#include <iostream>
#include <algorithm>
#include <cmath>


using namespace std;


Heap::Heap(int n)
{
	tab = new Task[n];
	size = 0;
	capacity = n;
}

Heap::~Heap()
{
}

int Heap::parent(int i)
{
	return i / 2;
}
int Heap::left(int i)
{
	return 2 * i;
}

int Heap::right(int i)
{
	return 2 * i + 1;
}

void Heap::add(Task added)
{
	if (capacity == size)
	{
		cout << "stos jest pelny" << endl;
		return;
	}

	tab[size] = added;
	int k = size;
	size++;
	while (k != 0 && tab[parent(k)].q < tab[k].q)
	{
		swap(tab[k], tab[parent(k)]);
		k = parent(k);
	}
}

void Heap::Heapify(int i)
{
	int l = left(i);
	int r = right(i);
	int bigger = i;
	if (tab[l].q > tab[i].q && l < size)
	{
		bigger = l;
	}
	if (tab[r].q > tab[bigger].q && r < size)
	{
		bigger = r;
	}
	if (bigger != i)
	{
		swap(tab[i], tab[bigger]);
		Heapify(bigger);
	}
}

int Heap::getSize()
{
	return this->size;
}

Task Heap::RemoveRoot()
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

int Heap::top()
{
	return tab[0].q;
}

void Heap::show()
{
	for (int i = 0; i < size; i++)
	{
		cout << tab[i].index << " ";
	}
}



