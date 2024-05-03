#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "skewBinomialHeap.hpp"
#include "fibonacciHeap.hpp"
#include "binaryHeap.hpp"
#include "heap23.hpp"

using namespace std;

void bench()
{
    ofstream g("benchmark.txt");
    SkewBinomialHeap heap;
    StrictFibonacciHeap<int> heapFib;
    BinaryHeap pq;
    // priority_queue<int, vector<int>, greater<int>> pq;
    Heap23 heap23(10000000);

    // Test: Inserting random elements
    clock_t start;
    clock_t end;
    int NUM_INSERTS;
    srand(time(nullptr)); // Seed for random number generator
    NUM_INSERTS = 100;

    for (int i = 1; i <= 10000; i *= 10)
    {
        NUM_INSERTS *= 10;
        // g << NU/M_INSERTS << endl;
        start = clock();
        for (int i = 0; i < NUM_INSERTS; ++i)
        {
            int num = rand() % 3000;
            heap.insert(num);
        }
        end = clock();
        g << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

        start = clock();
        for (int i = 0; i < NUM_INSERTS; ++i)
        {
            int num = rand() % 3000;
            heapFib.insert(num);
        }
        end = clock();
        g << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

        // for pq
        start = clock();
        for (int i = 0; i < NUM_INSERTS; ++i)
        {
            int num = rand() % 3000;
            pq.insert(num);
        }
        end = clock();
        g << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

        // for heap23
        start = clock();
        for (int i = 0; i < NUM_INSERTS; ++i)
        {
            int num = rand() % 3000;
            heap23.insert(num);
        }
        end = clock();
        g << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;
    }

    NUM_INSERTS = 100;
    for (int i = 1; i <= 10000; i *= 10)
    {
        NUM_INSERTS *= 10;
        // g << NUM_INSERTS << endl;

        start = clock();
        for (int i{}; i < NUM_INSERTS; ++i)
        { // Keep deleting until an exception is thrown
            heap.deleteMin();
        }
        end = clock();
        g << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

        start = clock();

        for (int i{}; i < NUM_INSERTS; ++i)
        { // Keep deleting until an exception is thrown
            heapFib.extractMin();
        }
        end = clock();
        g << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

        // for pq
        start = clock();

        for (int i{}; i < NUM_INSERTS; ++i)
        { // Keep deleting until an exception is thrown
            pq.deleteMin();
        }
        end = clock();
        g << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

        // for heap23
        start = clock();

        for (int i{}; i < NUM_INSERTS; ++i)
        { // Keep deleting until an exception is thrown
            heap23.extractMin();
        }
        end = clock();
        g << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;
    }

    // Test: Merging two heaps

    int heapSize = 100;
    for (int i = 1; i <= 10000; i *= 10)
    {

        heapSize *= 10;
        // g << heapSize << endl;
        SkewBinomialHeap heap1, heap2;

        for (int i = 0; i < heapSize; ++i)
        {
            heap1.insert(rand() % 1000);
            heap2.insert(rand() % 1000 + 1000); // Different range to see clear distinction
        }

        start = clock();
        heap1.merge(heap2);
        end = clock();
        g << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;
        // Test: Merging two heaps
        StrictFibonacciHeap<int> fibHeap1, fibHeap2;
        for (int i = 0; i < heapSize; ++i)
        {
            fibHeap1.insert(rand() % 1000);
            fibHeap2.insert(rand() % 1000 + 1000); // Different range to see clear distinction
        }

        start = clock();
        fibHeap1.merge(fibHeap2);
        end = clock();
        g << heapSize << " " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;

        // for pq
        BinaryHeap pq1, pq2;
        for (int i = 0; i < heapSize; ++i)
        {
            pq1.insert(rand() % 1000);
            pq2.insert(rand() % 1000 + 1000); // Different range to see clear distinction
        }

        start = clock();
        pq1.merge(pq2);
        end = clock();
        g << heapSize << " " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;
        // for heap23
        Heap23 heap231(heapSize), heap232(heapSize);
        for (int i = 0; i < heapSize; ++i)
        {
            heap231.insert(rand() % 1000);
            heap232.insert(rand() % 1000 + 1000); // Different range to see clear distinction
        }

        start = clock();
        heap231.merge(heap232);
        end = clock();
        g << heapSize << " " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;
    }
}

int main()
{
    bench();
}
