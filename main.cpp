#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include "skewBinomialHeap.hpp"

using namespace std;

void extensiveTesting()
{
    SkewBinomialHeap heap;

    // Test: Inserting random elements
    srand(time(nullptr)); // Seed for random number generator
    const int NUM_INSERTS = 1000;
    cout << "Inserting " << NUM_INSERTS << " random elements." << endl;
    for (int i = 0; i < NUM_INSERTS; ++i)
    {
        int num = rand() % 2000; // Random numbers between 0 and 1999
        heap.insert(num);
    }
    cout << "Expected minimum is near the smallest random number inserted." << endl;

    cout << "Minimum key after inserts: " << heap.findMin() << endl;

    cout << "Deleting all elements..." << endl;
    try
    {
        while (true)
        { // Keep deleting until an exception is thrown
            heap.deleteMin();
            int a = heap.findMin(); // Just to check if the heap is still valid
        }
    }
    catch (const std::logic_error &e)
    {
        cout << "Caught exception when trying to find min in an empty heap: " << e.what() << endl;
    }

    // Test: Merging two heaps
    SkewBinomialHeap heap1, heap2;
    for (int i = 0; i < 500; ++i)
    {
        heap1.insert(rand() % 1000);
        heap2.insert(rand() % 1000 + 1000); // Different range to see clear distinction
    }
    cout << "Minimum key heap1: " << heap1.findMin() << endl;
    cout << "Minimum key heap2: " << heap2.findMin() << endl;

    heap1.merge(heap2.getRoot());
    cout << "Minimum key after merging: " << heap1.findMin() << endl;
    
    // Test: Inserting and deleting alternately
    SkewBinomialHeap alternatingHeap;
    alternatingHeap.insert(rand() % 300);
    for (int i = 0; i < 3; ++i)
    {
        alternatingHeap.insert(rand() % 300);
        alternatingHeap.deleteMin();
    }
    cout << "Final minimum after alternate inserts and deletes: " << alternatingHeap.findMin() << endl;
}

int main()
{
    extensiveTesting();
    return 0;
}
