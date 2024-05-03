#include <iostream>
#include <cstdlib>
#include <ctime>
#include "skewBinomialHeap.hpp"
#include <queue>
#include "binaryHeap.hpp"


using namespace std;

void bench()
{
    SkewBinomialHeap heap;
    BinaryHeap pq;
    // priority_queue<int, vector<int>, greater<int>> pq;

    // Test: Inserting random elements

    srand(time(nullptr)); // Seed for random number generator
    const int NUM_INSERTS = 10000;
    cout << "Inserting " << NUM_INSERTS << " random elements." << endl;
    clock_t start = clock();
    for (int i = 0; i < NUM_INSERTS; ++i)
    {
        int num = rand() % 3000;
        heap.insert(num);
    }
    clock_t end = clock();
    cout << "Time taken to insert " << NUM_INSERTS << " elements: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    // for pq
    start = clock();
    for (int i = 0; i < NUM_INSERTS; ++i)
    {
        int num = rand() % 3000;
        pq.insert(num);
    }
    end = clock();
    cout << "Time taken to insert " << NUM_INSERTS << " elements in pq: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    cout << "Deleting all elements..." << endl;

    start = clock();

    for (int i{}; i < NUM_INSERTS; ++i)
    { // Keep deleting until an exception is thrown
        heap.deleteMin();
    }
    end = clock();
    cout << "Time taken to delete " << NUM_INSERTS << " elements: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    // for pq
    start = clock();

    for (int i{}; i < NUM_INSERTS; ++i)
    { // Keep deleting until an exception is thrown
        pq.deleteMin();
    }
    end = clock();
    cout << "Time taken to delete " << NUM_INSERTS << " elements in pq: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    // Test: Merging two heaps
    SkewBinomialHeap heap1, heap2;
    const int heapSize = 10000;
    for (int i = 0; i < heapSize; ++i)
    {
        heap1.insert(rand() % 1000);
        heap2.insert(rand() % 1000 + 1000); // Different range to see clear distinction
    }
    cout << "Minimum key heap1: " << heap1.findMin() << endl;
    cout << "Minimum key heap2: " << heap2.findMin() << endl;

    start = clock();
    heap1.merge(heap2.getRoot());
    end = clock();
    cout << "Time taken to merge two heaps of size " << heapSize << ": " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
    
    //for pq
    BinaryHeap pq1, pq2;
    for (int i = 0; i < heapSize; ++i)
    {
        pq1.insert(rand() % 1000);
        pq2.insert(rand() % 1000 + 1000); // Different range to see clear distinction
    }
    cout << "Minimum key heap1: " << pq1.findMin() << endl;
    cout << "Minimum key heap2: " << pq2.findMin() << endl;

    start = clock();
    pq1.merge(pq2);
    end = clock();
    cout << "Time taken to merge two heaps of size " << heapSize << ": " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    
    cout << "Minimum key after merging: " << heap1.findMin() << endl;
}

int main()
{
    bench();
    return 0;
}
