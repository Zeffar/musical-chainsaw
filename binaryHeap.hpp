#ifndef BINARY_HEAP_HPP
#define BINARY_HEAP_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

class BinaryHeap
{
private:
    std::vector<int> heap; // Vector to store heap elements

    // Helper function to maintain heap property after insertion
    void bubbleUp(int index)
    {
        while (index > 0 && heap[(index - 1) / 2] > heap[index])
        {
            std::swap(heap[(index - 1) / 2], heap[index]);
            index = (index - 1) / 2;
        }
    }

    // Helper function to maintain heap property after deletion
    void bubbleDown(int index)
    {
        int childIndex = 2 * index + 1; // Left child index
        while (childIndex < heap.size())
        {
            // Find the min child
            int rightChildIndex = childIndex + 1;
            if (rightChildIndex < heap.size() && heap[rightChildIndex] < heap[childIndex])
            {
                childIndex = rightChildIndex;
            }

            // If the min child is less than the current node, swap them
            if (heap[index] > heap[childIndex])
            {
                std::swap(heap[index], heap[childIndex]);
                index = childIndex;
                childIndex = 2 * index + 1;
            }
            else
            {
                break;
            }
        }
    }

public:
    BinaryHeap() {}

    // Merge another binary heap with this one
    void merge(const BinaryHeap& other)
    {
        for (int elem : other.heap)
        {
            insert(elem);
        }
    }

    // Insert a new key into the heap
    void insert(int key)
    {
        heap.push_back(key);
        bubbleUp(heap.size() - 1);
    }

    // Find the minimum key in the heap
    int findMin() const
    {
        if (heap.empty())
            throw std::logic_error("Heap is empty");
        return heap.front();
    }

    // Delete the minimum key from the heap
    void deleteMin()
    {
        if (heap.empty())
            return;

        // Move the last element to the root and remove the last element
        heap.front() = heap.back();
        heap.pop_back();
        if (!heap.empty())
            bubbleDown(0);
    }

    // Utility function to get the size of the heap
    size_t size() const
    {
        return heap.size();
    }

    // Utility function to check if the heap is empty
    bool isEmpty() const
    {
        return heap.empty();
    }
};

#endif // BINARY_HEAP_HPP
