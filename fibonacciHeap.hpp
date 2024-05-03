#ifndef FIB_HEAP_HPP
#define FIB_HEAP_HPP

#include <cmath>
#include <list>
#include <memory>
#include <vector>


class Node : public std::enable_shared_from_this<Node> {
public:
  int key, degree;
  bool mark;
  std::shared_ptr<Node> parent, child, left, right;

  Node(int value)
      : key(value), degree(0), mark(false), parent(nullptr), child(nullptr),
        left(nullptr), right(nullptr) {}

  void initialize() {
    left = shared_from_this();
    right = shared_from_this();
  }
};

class FibonacciHeap {
private:
  std::shared_ptr<Node> min_node;
  int total_nodes;

public:
  FibonacciHeap() : min_node(nullptr), total_nodes(0) {}

  void insert(int key) {
    std::shared_ptr<Node> node = std::make_shared<Node>(key);
    node->initialize();
    if (!min_node) {
      min_node = node;
    } else {
      node->right = min_node;
      node->left = min_node->left;
      min_node->left->right = node;
      min_node->left = node;
      if (node->key < min_node->key) {
        min_node = node;
      }
    }
    total_nodes++;
  }

  std::shared_ptr<Node> extractMin() { return removeMin(); }

  std::shared_ptr<Node> removeMin() {
    std::shared_ptr<Node> z = min_node;
    if (z != nullptr) {
      if (z->child != nullptr) {
        std::shared_ptr<Node> child = z->child;
        do {
          auto next = child->right;
          addNodeToRootList(child);
          child->parent = nullptr;
          child = next;
        } while (child != z->child);
      }
      removeNodeFromRootList(z);
      if (z == z->right) {
        min_node = nullptr;
      } else {
        min_node = z->right;
        consolidate();
      }
      total_nodes--;
    }
    return z;
  }

  void merge(FibonacciHeap &other) {
    if (!other.min_node)
      return;
    if (!min_node) {
      min_node = other.min_node;
      total_nodes = other.total_nodes;
      return;
    }

    min_node->right->left = other.min_node->left;
    other.min_node->left->right = min_node->right;
    min_node->right = other.min_node;
    other.min_node->left = min_node;

    if (other.min_node->key < min_node->key) {
      min_node = other.min_node;
    }
    total_nodes += other.total_nodes;
  }

private:
  void addNodeToRootList(std::shared_ptr<Node> node) {
    if (min_node != nullptr) {
      node->left = min_node;
      node->right = min_node->right;
      min_node->right = node;
      node->right->left = node;
    }
  }

  void removeNodeFromRootList(std::shared_ptr<Node> node) {
    node->left->right = node->right;
    node->right->left = node->left;
  }

  void consolidate() {
    int max_degree = static_cast<int>(std::log(total_nodes) *
                                      1.44); // approximation of log base phi
    std::vector<std::shared_ptr<Node>> A(max_degree + 1, nullptr);

    std::list<std::shared_ptr<Node>> root_nodes;
    std::shared_ptr<Node> current = min_node;
    do {
      root_nodes.push_back(current);
      current = current->right;
    } while (current != min_node);

    for (auto &w : root_nodes) {
      std::shared_ptr<Node> x = w;
      int d = x->degree;
      while (A[d] != nullptr) {
        std::shared_ptr<Node> y = A[d];
        if (x->key > y->key) {
          std::swap(x, y);
        }
        link(y, x);
        A[d] = nullptr;
        d++;
      }
      A[d] = x;
    }

    min_node = nullptr;
    for (auto &n : A) {
      if (n != nullptr) {
        if (min_node == nullptr || n->key < min_node->key) {
          min_node = n;
        }
      }
    }
  }

  void link(std::shared_ptr<Node> y, std::shared_ptr<Node> x) {
    removeNodeFromRootList(y);
    y->left = y->right = y;
    y->parent = x;

    if (x->child == nullptr) {
      x->child = y;
    } else {
      y->right = x->child;
      y->left = x->child->left;
      x->child->left->right = y;
      x->child->left = y;
    }
    x->degree++;
    y->mark = false;
  }
};

#endif