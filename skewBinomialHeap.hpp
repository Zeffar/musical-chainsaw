#ifndef SKEW_BINOMIAL_HEAP_HPP
#define SKEW_BINOMIAL_HEAP_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>

class Node
{
public:
    int key;
    int rank;
    std::vector<Node *> children;

    Node(int k) : key(k), rank(0) {}
};

class SkewBinomialHeap
{
private:
    std::vector<Node *> roots;

    // Ensure each heap has unique ranks
    void makeUnique()
    {
        if (roots.empty())
            return;
        std::sort(roots.begin(), roots.end(), [](const Node *a, const Node *b)
                  { return a->rank < b->rank; });
        std::vector<Node *> uniqueRoots;
        Node *last = roots[0];
        uniqueRoots.push_back(last);

        for (size_t i = 1; i < roots.size(); ++i)
        {
            if (last->rank == roots[i]->rank)
            {
                Node *merged = link(last, roots[i]);
                uniqueRoots.pop_back();
                uniqueRoots.push_back(merged);
                last = merged;
            }
            else
            {
                uniqueRoots.push_back(roots[i]);
                last = roots[i];
            }
        }
        roots.swap(uniqueRoots);
    }

    // Link two nodes of the same rank
    Node *link(Node *x, Node *y)
    {
        if (x->key > y->key)
        {
            std::swap(x, y);
        }
        x->children.push_back(y);
        x->rank++;
        return x;
    }
    
    Node *skewLink(Node *newNode, Node *t1, Node *t2)
    {
        if (newNode->key > t1->key)
            std::swap(newNode, t1);
        if (newNode->key > t2->key)
            std::swap(newNode, t2);

        // newNode becomes the root, t1 and t2 become its children
        newNode->children.push_back(t1);
        newNode->children.push_back(t2);
        newNode->rank = t1->rank + 1;
        return newNode;
    }

public:
    SkewBinomialHeap() {}

    void insert(int key)
    {
        Node *newNode = new Node(key);
        if (roots.size() >= 2)
        {
            auto it1 = roots.begin();
            auto it2 = std::next(it1);

            if ((*it1)->rank == (*it2)->rank)
            {
                Node *t1 = *it1;
                Node *t2 = *it2;
                roots.erase(it1, std::next(it2)); // Remove the first two trees

                Node *newRoot = skewLink(newNode, t1, t2);
                roots.push_back(newRoot); // Insert the new tree at the end
                std::sort(roots.begin(), roots.end(), [](Node *a, Node *b)
                          { return a->rank < b->rank; });
                return;
            }
        }
        // If no trees to link, or they don't have the same rank
        roots.insert(roots.begin(), newNode); // Insert at the front
    }

    int findMin()
    {
        if (roots.empty())
        {
            throw std::runtime_error("Heap is empty");
        }
        int min = 1 << 30;
        for (const auto it : roots)
        {
            if (it->key < min)
            {
                min = it->key;
            }
        }
        return min;
    }

    void deleteMin()
    {
        if (roots.empty())
        {
            return;
        }
        auto minIt = std::min_element(roots.begin(), roots.end(), [](Node *a, Node *b)
                                      { return a->key < b->key; });
        Node *minNode = *minIt;
        roots.erase(minIt);

        SkewBinomialHeap tempHeap;
        for (Node *child : minNode->children)
        {
            tempHeap.roots.push_back(child);
        }
        merge(tempHeap);

        delete minNode;
    }

    void merge(SkewBinomialHeap &other)
    {
        roots.insert(roots.end(), other.roots.begin(), other.roots.end());
        makeUnique();
    }
};

#endif // SKEW_BINOMIAL_HEAP_HPP
