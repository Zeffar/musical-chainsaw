#ifndef NODE_SD
#define NODE_SD

#include <iostream>

class Node
{
	friend class Heap23;
	friend int mergeNodes(Node **a, Node **b);

	private:
		Node* parent;
		Node* child;
		Node* left;
		Node* right;
		Node* partner;

		bool extra;
		int dim;
		int key;
		int value;

	public:
		Node(int key, int value) :
			child(NULL),
			left(NULL),
			right(NULL),
			parent(NULL),
			partner(NULL),
			extra(false),
			dim(0),
			key(key),
			value(value)
	{}

		int getPriority() { return key; }
		int getValue() { return value; }

		void addChild(Node* node);
		void removeChild(Node* child);
		void replaceChild(Node* new_node);

		/*
		friend std::ostream& operator<<(std::ostream& os, const Node* node)
		{
			bool start = false;
			for (node = this; !start || node != this; node = node->right)
			{
				if(!start)
					start = true;

				os << " ";
				os << node->key << '[' << node->dim << "][" << node->extra << ']';
				if (node->partner != NULL && node->partner != node)
				{
					os << " | " << node->partner->key << '[' << node->partner->dim << "]["<< node->partner->extra << ']';
				}
				os << "\n";
				if (node->child != NULL)
					os<<node->child;
				if (node->partner != NULL && node->partner != node && node->partner->child != NULL)
				{
					os<<node->partner->child;
				}
			}

			return os;
		}
		*/
};

#endif
