#ifndef STRICT_FIBONACCI_HEAP_H
#define STRICT_FIBONACCI_HEAP_H

#include <cmath>
#include <memory>
#include <unordered_map>
#include <vector>

template <typename T> class StrictFibonacciHeap {
public:
  class Node;
  using NodePtr = std::shared_ptr<Node>;

  class Node {
  public:
    T key;
    int degree = 0;
    bool marked = false;
    NodePtr parent;
    NodePtr child;
    NodePtr left;
    NodePtr right;

    explicit Node(T k) : key(k), left(nullptr), right(nullptr) {}
  };

private:
  NodePtr min;
  size_t n = 0;

  void consolidate() {
    if (!min)
      return;

    std::unordered_map<int, NodePtr> degreeMap;
    std::vector<NodePtr> roots;
    NodePtr current = min;

    do {
      roots.push_back(current);
      current = current->right;
    } while (current != min);

    for (auto &root : roots) {
      NodePtr x = root;
      int d = x->degree;
      while (degreeMap.find(d) != degreeMap.end()) {
        NodePtr y = degreeMap[d];
        if (x->key > y->key)
          std::swap(x, y);
        link(y, x);
        degreeMap.erase(d);
        d++;
      }
      degreeMap[d] = x;
    }

    min = nullptr;
    for (auto &pair : degreeMap) {
      if (!min) {
        min = pair.second;
        min->left = min->right = min;
      } else {
        insertNode(pair.second);
      }
    }
  }

  void link(NodePtr y, NodePtr x) {
    y->left->right = y->right;
    y->right->left = y->left;
    y->parent = x;
    if (!x->child) {
      x->child = y;
      y->right = y->left = y;
    } else {
      y->left = x->child;
      y->right = x->child->right;
      x->child->right->left = y;
      x->child->right = y;
    }
    x->degree++;
    y->marked = false;
  }

  void insertNode(NodePtr node) {
    if (!min) {
      min = node;
      node->left = node->right = node;
    } else {
      node->right = min;
      node->left = min->left;
      min->left->right = node;
      min->left = node;
      if (node->key < min->key) {
        min = node;
      }
    }
  }

public:
  StrictFibonacciHeap() : min(nullptr), n(0) {}

  void insert(T key) {
    NodePtr node = std::make_shared<Node>(key);
    if (!node->left) { // Set self-referential left and right on first use
                       // outside constructor
      node->left = node->right = node;
    }
    insertNode(node);
    n++;
  }

  T extractMin() {
    if (!min)
      return T(); // Returns default-constructed value of T if heap is empty

    NodePtr z = min;
    if (z->child) {
      NodePtr x = z->child;
      do {
        NodePtr next = x->right;
        insertNode(x);
        x->parent.reset();
        x = next;
      } while (x != z->child);
    }
    z->left->right = z->right;
    z->right->left = z->left;
    if (z == z->right) {
      min = nullptr;
    } else {
      min = z->right;
      consolidate();
    }
    n--;
    return z->key;
  }

  void meld(StrictFibonacciHeap &other) {
    if (!other.min)
      return;
    if (!min) {
      min = other.min;
      n = other.n;
    } else {
      NodePtr minRight = min->right;
      min->right = other.min->right;
      other.min->right->left = min;
      other.min->right = minRight;
      minRight->left = other.min;
      if (other.min->key < min->key) {
        min = other.min;
      }
      n += other.n;
    }
    other.min = nullptr;
    other.n = 0;
  }

  // Alias merge to meld for compatibility and clarity
  void merge(StrictFibonacciHeap &other) { meld(other); }
};

#endif // STRICT_FIBONACCI_HEAP_H
