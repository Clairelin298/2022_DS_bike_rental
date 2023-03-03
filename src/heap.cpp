#include <iostream>
#include "./nthu_bike.h"
#include <iostream>

using namespace std;

// thos file is the implementation of Heap (element is BikeType object)

MaxHeap::MaxHeap()
{

	heap_size = 0;
	capacity = MAX_BIKE_TYPE;
	harr = new BikeType[capacity];
}

int MaxHeap::get_size() { return heap_size; }

void MaxHeap::insertKey(BikeType k)
{
	if (heap_size == capacity)
	{
		return;
	}

	// First insert the new key at the end
	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;

	// Fix the max heap property
	while (i != 0 && (harr[parent(i)].price < harr[i].price || (harr[parent(i)].price == harr[i].price && (harr[parent(i)].index > harr[i].index))))
	{
		swap(harr, i, parent(i));
		i = parent(i);
	}
}

BikeType MaxHeap::getMax() { return harr[0]; }

// Method to remove max element (or root) from max heap
BikeType MaxHeap::extractMax()
{
	if (heap_size <= 0)
	{
		BikeType tmp;
		tmp.index = -1;
		return tmp;
	}

	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}

	// Store the max value, and remove it from heap
	BikeType root = harr[0];
	harr[0] = harr[heap_size - 1];
	heap_size--;
	MaxHeapify(0);

	return root;
}

// heapify a subtree with the root at given index
void MaxHeap::MaxHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int biggest = i;
	if (l < heap_size && (harr[l].price > harr[i].price || (harr[l].price == harr[i].price && (harr[l].index < harr[i].index))))
		biggest = l;
	if (r < heap_size && (harr[r].price > harr[biggest].price || (harr[r].price == harr[biggest].price && (harr[r].index < harr[biggest].index))))
		biggest = r;
	if (biggest != i)
	{
		swap(harr, i, biggest);
		MaxHeapify(biggest);
	}
}

// A utility function to swap two elements (BikeType object)
void swap(BikeType *harr, int x, int y)
{
	BikeType tmp(harr[x].type, harr[x].station, harr[x].price,
				 harr[x].index, harr[x].count, harr[x].return_time, harr[x].station);
	harr[x] = harr[y];
	harr[y] = tmp;
}
