#ifndef HEAP23_SD
#define HEAP23_SD

#include <iostream>
#include <cmath>
#include "node.hpp"

class Heap23
{
	private:
		Node** trees;
		int maxTrees;
		int nNodes;
		int value;
	protected:
		void meld(Node *list);
	public:
		Heap23(int maxNodes = 100) : nNodes(0), value(0)
		{
			maxTrees = (int) (0.5 + std::log(maxNodes + 1) / std::log(2.0));
			trees = new Node*[maxTrees];

			for (int i = 0; i < maxTrees; i++)
			{
				trees[i] = NULL;
			}
		}

		~Heap23()
		{
			delete[] trees;
		}

		bool isEmpty();

		Node* insert(int key, int value);
		Node* min();
		Node* extractMin();

		bool merge(Heap23& heap);
		void remove(Node* node);
		void decreaseKey(Node* node, int newKey);

		/*
		friend std::ostream& operator<<(std::ostream& os, const Heap23& heap)
		{
			for (int i = 0; i < maxTrees; i++)
			{
				if(trees[i] != NULL)
				{
					os<<"Tree #" << i << "\n";
					os<<trees[i];
				}
			}
		}
		*/
};

#endif
