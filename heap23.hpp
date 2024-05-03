#ifndef HEAP23_SD
#define HEAP23_SD

#include <iostream>
#include <cmath>
#include "node.hpp"

class Heap23
{
	private:
		Node2** trees;
		int maxTrees;
		int nNodes;
		int value;
	protected:
		void meld(Node2 *list);
	public:
		Heap23(int maxNodes = 100) : nNodes(0), value(0)
		{
			maxTrees = (int) (0.5 + std::log(maxNodes + 1) / std::log(2.0));
			trees = new Node2*[maxTrees];

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

		Node2* insert(int key, int value);
		Node2* min();
		Node2* extractMin();

		bool merge(Heap23& heap);
		void remove(Node2* node);
		void decreaseKey(Node2* node, int newKey);

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
