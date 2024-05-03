#ifndef POINTER_BINARY_HEAP_HPP
#define POINTER_BINARY_HEAP_HPP

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <functional>

// Node structure for Binary Heap

class PointerBinaryHeap
{
private:
    struct Node
    {
        int key;                     // Key or priority of the node
        std::shared_ptr<Node> left;  // Pointer to the left child
        std::shared_ptr<Node> right; // Pointer to the right child
        std::weak_ptr<Node> parent;  // Weak pointer to the parent node to avoid ownership cycles

        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };
    std::shared_ptr<Node> root;     // Pointer to the root of the heap
    std::shared_ptr<Node> lastNode; // Pointer to the last node inserted in the heap

    // Bubble up the newly inserted node to maintain heap property
    void bubbleUp(std::shared_ptr<Node> node)
    {
        while (node != root && node->key < node->parent.lock()->key)
        {
            std::swap(node->key, node->parent.lock()->key);
            node = node->parent.lock();
        }
    }

    // Find the right position to insert the new node
    void findPositionForNewNode(std::shared_ptr<Node> &node, int &size)
    {
        std::vector<std::shared_ptr<Node>> path;
        while (size > 0)
        {
            path.push_back(node);
            if (size % 2 == 0)
            {
                node = node->right;
            }
            else
            {
                node = node->left;
            }
            size = (size - 1) / 2;
        }
        std::reverse(path.begin(), path.end());
        for (auto n : path)
        {
            if (!n->left)
            {
                node = n;
                return;
            }
            else if (!n->right)
            {
                node = n;
                return;
            }
        }
    }

    // Get the size of the heap
    int getSize()
    {
        int size = 0;
        std::function<void(std::shared_ptr<Node>)> countSize = [&](std::shared_ptr<Node> node)
        {
            if (node)
            {
                size++;
                countSize(node->left);
                countSize(node->right);
            }
        };
        countSize(root);
        return size;
    }

public:
    PointerBinaryHeap() : root(nullptr), lastNode(nullptr) {}

    // Insert a new key into the heap
    void insert(int key)
    {
        std::shared_ptr<Node> newNode = std::make_shared<Node>(key);
        if (!root)
        {
            root = newNode;
            lastNode = newNode;
        }
        else
        {
            int size = getSize();
            findPositionForNewNode(lastNode, size);
            if (!lastNode->left)
            {
                lastNode->left = newNode;
            }
            else
            {
                lastNode->right = newNode;
            }
            newNode->parent = lastNode;
            bubbleUp(newNode);
            lastNode = newNode;
        }
    }

    // Find the minimum key in the heap
    int findMin() const
    {
        if (!root)
            throw std::logic_error("Heap is empty");
        return root->key;
    }

    // Delete the minimum key from the heap
    void deleteMin()
    {
        if (!root)
            return;

        if (!root->left && !root->right)
        {
            root = nullptr;
            return;
        }

        root->key = lastNode->key;
        if (lastNode == lastNode->parent.lock()->left)
        {
            lastNode->parent.lock()->left = nullptr;
        }
        else
        {
            lastNode->parent.lock()->right = nullptr;
        }
        bubbleDown(root);
        // Update lastNode to the last inserted node before the one we just removed
    }

    // Helper function to maintain heap property after deleting the root
    void bubbleDown(std::shared_ptr<Node> node)
    {
        while (node->left || node->right)
        {
            std::shared_ptr<Node> smallerChild = node->left;
            if (node->right && node->right->key < smallerChild->key)
            {
                smallerChild = node->right;
            }
            if (smallerChild && node->key > smallerChild->key)
            {
                std::swap(node->key, smallerChild->key);
                node = smallerChild;
            }
            else
            {
                break;
            }
        }
    }
};

#endif // BINARY_HEAP_HPP
