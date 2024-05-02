#ifndef SKEW_BINOMIAL_HPP
#define SKEW_BINOMIAL_HPP
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_set>
class Node // Left-Child Right-Sibling representation
{
private:
    int key;  // Priority
    int rank; // Number or children
    Node *parent;
    Node *left;  // LC
    Node *right; // RS

public:
    // Initialization //
    Node() : key(0), rank(0), parent(nullptr), left(nullptr), right(nullptr){};
    Node(int key) : key(key), rank(0), parent(nullptr), left(nullptr), right(nullptr){};
    ~Node(){}; //to do

    // Access //
    Node *getChild() const
    {
        return left;
    }
    Node *getSibling() const
    {
        return right;
    }
    Node *getParent() const
    {
        return parent;
    }
    int getRank() const
    {
        return rank;
    }
    int getKey() const
    {
        return key;
    }
    void resetParent()
    {
        parent = nullptr;
        return;
    }
};

class skewBinomial
{
private:
    std::unordered_set<Node *> roots;
    Node *Min;

public:
    skewBinomial() : Min(nullptr){};
    skewBinomial(int key)
    {
        Node *newNode = new Node(key);
        roots.insert(newNode);
        Min = newNode;
    }
    ~skewBinomial()
    {
        for (Node *root : roots)
        {
            deleteSubtree(root);
        }
    }
    void deleteSubtree(Node *node)
    {
        if (node != nullptr)
        {
            deleteSubtree(node->getChild());
            deleteSubtree(node->getSibling());
            delete node;
        }
    }

    void merge(skewBinomial &other)
    {
        // merging two arrays or roots
        // to do
    }

    void insert(int key)
    {
        skewBinomial temp(key);
        merge(temp);
    }

    void deleteMin(int key)
    {
        if (Min == nullptr)
            return;
        Node *child = Min->getChild();
        std::vector<int> temp;
        skewBinomial newHeap;
        while (child != nullptr)
        {
            child->resetParent();
            if (child->getRank()) // rank > 0
            {
                newHeap.roots.insert(child);
            }
            else // rank == 0
            {
                temp.push_back(child->getKey());
            }
            child = child->getSibling();
        }
        merge(newHeap);

        for (const auto it : temp)
        {
            insert(it);
        }
        roots.erase(Min);
        delete Min;
    }

    Node *findMin()
    {
        return Min;
    }
};
#endif