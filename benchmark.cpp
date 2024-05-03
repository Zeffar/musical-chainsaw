#include <iostream>
#include <cstdlib>
#include <ctime>
#include "skewBinomialHeap.hpp"
#include "fibonacciHeap.hpp"
#include <queue>
#include "binaryHeap.hpp"


using namespace std;

void bench()
{
    SkewBinomialHeap heap;
    FibonacciHeap heapFib;
    BinaryHeap pq;
    // priority_queue<int, vector<int>, greater<int>> pq;

    // Test: Inserting random elements

    srand(time(nullptr)); // Seed for random number generator
    const int NUM_INSERTS = 10000;
    clock_t start = clock();
    for (int i = 0; i < NUM_INSERTS; ++i)
    {
        int num = rand() % 3000;
        heap.insert(num);
    }
    clock_t end = clock();
    cout << NUM_INSERTS << " " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

    start = clock();
    for (int i = 0; i < NUM_INSERTS; ++i)
    {
        int num = rand() % 3000;
        heapFib.insert(num);
    }
    end = clock();
    cout << NUM_INSERTS << " " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;


    // for pq
    start = clock();
    for (int i = 0; i < NUM_INSERTS; ++i)
    {
        int num = rand() % 3000;
        pq.insert(num);
    }
    end = clock();
    cout << NUM_INSERTS << " " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

    start = clock();

    for (int i{}; i < NUM_INSERTS; ++i)
    { // Keep deleting until an exception is thrown
        heap.deleteMin(); 
    }
    end = clock();
    cout << NUM_INSERTS << " " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

    start = clock();

    for (int i{}; i < NUM_INSERTS; ++i)
    { // Keep deleting until an exception is thrown
        heapFib.extractMin();
    }
    end = clock();
    cout << NUM_INSERTS << " " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;


    // for pq
    start = clock();

    for (int i{}; i < NUM_INSERTS; ++i)
    { // Keep deleting until an exception is thrown
        pq.deleteMin();
    }
    end = clock();
    cout << NUM_INSERTS << " " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

    // Test: Merging two heaps
    SkewBinomialHeap heap1, heap2;
    const int heapSize = 10000;
    for (int i = 0; i < heapSize; ++i)
    {
        heap1.insert(rand() % 1000);
        heap2.insert(rand() % 1000 + 1000); // Different range to see clear distinction
    }

    start = clock();
    heap1.merge(heap2.getRoot());
    end = clock();
    cout << heapSize << " " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;
     // Test: Merging two heaps
    FibonacciHeap fibHeap1, fibHeap2;
    for (int i = 0; i < heapSize; ++i)
    {
        fibHeap1.insert(rand() % 1000);
        fibHeap2.insert(rand() % 1000 + 1000); // Different range to see clear distinction
    }

    start = clock();
    fibHeap1.merge(fibHeap2);
    end = clock();
    cout << heapSize << " " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;
    
    //for pq
    BinaryHeap pq1, pq2;
    for (int i = 0; i < heapSize; ++i)
    {
        pq1.insert(rand() % 1000);
        pq2.insert(rand() % 1000 + 1000); // Different range to see clear distinction
    }

    start = clock();
    pq1.merge(pq2);
    end = clock();
    cout << heapSize << " " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;
}

int main()
{
    bench();
    return 0;
}
