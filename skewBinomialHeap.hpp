#ifndef SKEW_BINOMIAL_HEAP_HPP
#define SKEW_BINOMIAL_HEAP_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// Node structure for Skew Binomial Tree
struct Node
{
    int key;                       // priority of the node
    int rank;                      // rank of the node
    std::shared_ptr<Node> child;   // Left-Child pointer
    std::shared_ptr<Node> sibling; // Right-Sibling pointer

    Node(int k) : key(k), rank(0), child(nullptr), sibling(nullptr) {}
};

class SkewBinomialHeap
{
private:
    std::shared_ptr<Node> root; // Tarjan's Bootstrap optimization structure
    std::shared_ptr<Node> minNode;

    // simple link between two trees of the same rank
    std::shared_ptr<Node> link(std::shared_ptr<Node> t1, std::shared_ptr<Node> t2)
    {
        if (t1->key > t2->key)
        {
            std::swap(t1, t2);
        }
        t2->sibling = t1->child;
        t1->child = t2;
        t1->rank++;
        return t1;
    }

    // Update the minimum node pointer
    void updateMinNode()
    {
        if (!root)
        {
            minNode = nullptr;
            return;
        }
        minNode = root;
        std::shared_ptr<Node> curr = root->sibling;
        while (curr)
        {
            if (curr->key < minNode->key)
            {
                minNode = curr;
            }
            curr = curr->sibling;
        }
    }

public:
    SkewBinomialHeap() : root(nullptr), minNode(nullptr) {}
    std::shared_ptr<Node> getRoot()
    {
        return root;
    }

    void merge(std::shared_ptr<Node> otherHeap)
    {
        if (!root) // first heap is empty
        {
            root = minNode = otherHeap;
            return;
        }
        if (!otherHeap) // second heap is empty
            return;

        // Merge roots and maintain minimum pointer
        std::shared_ptr<Node> firstHeap = root, last = nullptr, res = nullptr;

        while (firstHeap && otherHeap)
        {
            std::shared_ptr<Node> next;
            if (firstHeap->rank < otherHeap->rank)
            {
                next = firstHeap;
                firstHeap = firstHeap->sibling;
            }

            else
            {
                next = otherHeap;
                otherHeap = otherHeap->sibling;
            }

            if (!res)
            {
                res = next;
            }

            else
            {
                last->sibling = next;
            }
            last = next;

            // Automatically link trees of the same rank
            if (last->sibling && last->sibling->rank == last->rank)
            {
                last = link(last, last->sibling);
            }
        }

        last->sibling = (firstHeap ? firstHeap : otherHeap);

        // Update root and minNode pointers
        root = res;
        updateMinNode();
    }

    // Insert a new key into the heap
    void insert(int key)
    {
        SkewBinomialHeap temp;
        temp.root = std::make_shared<Node>(key);
        merge(temp.root);
    }

    // Find the minimum key in the heap
    int findMin()
    {
        if (!minNode)
            throw std::logic_error("Heap is empty");
        return minNode->key;
    }

    // Delete the minimum key from the heap
    void deleteMin()
    {
        if (!minNode)
            return;

        // Remove minNode from the root list
        std::shared_ptr<Node> curr = root, prev = nullptr;
        while (curr != minNode)
        {
            prev = curr;
            curr = curr->sibling;
        }
        if (prev)
            prev->sibling = curr->sibling;
        else
            root = curr->sibling;

        // Reverse the children of minNode and merge back
        std::shared_ptr<Node> child = nullptr;
        curr = minNode->child;
        while (curr)
        {
            std::shared_ptr<Node> next = curr->sibling;
            curr->sibling = child;
            child = curr;
            curr = next;
        }

        merge(child);
        updateMinNode(); // Update minNode after deletion
    }
};
#endif
