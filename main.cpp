#include "heap23.hpp"

int main()
{
	Heap23 heap;
	for(int i = 0; i < 1000; i++)
	{
		heap.insert(i, i);
	}
}
