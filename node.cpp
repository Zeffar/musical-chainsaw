#include "Node.h"

int mergeNodes(Node** a, Node** b)
{
	Node *tree, *nextTree, *other, *nextOther;
	int c = 0;

	if ((*a)->getPriority() <= (*b)->getPriority())
	{
		tree = (*a);
		other = (*b);
	}
	else
	{
		tree = (*b);
		other = (*a);
	}
	++c;

	nextTree = tree->partner;
	nextOther = other->partner;

	if (!nextTree)
	{
		if (nextOther)
		{
			tree->addChild(other);
			tree->dim++;
			*a = NULL;
			*b = tree;
		}
		else
		{
			tree->partner = other;
			other->partner = tree;
			other->extra = true;

			*a = tree;
			*b = NULL;
		}
	}
	else if (!nextOther)
	{
		tree->partner = NULL;
		other->partner = nextTree;
		nextTree->partner = other;

		if (other->getPriority() < nextTree->getPriority())
		{
			tree->addChild(other);
		}
		else
		{
			nextTree->extra = false;
			other->extra = true;
			tree->addChild(nextTree);
		}

		++(tree->dim);

		++c;
		*a = NULL;
		*b = tree;
	}
	else
	{
		tree->partner = NULL;
		nextTree->partner = NULL;
		nextTree->extra = false;
		nextTree->left = nextTree->right = nextTree;
		nextTree->parent = NULL;

		tree->addChild(other);
		++(tree->dim);

		*a = nextTree;
		*b = tree;
	}

	return c;
}

void Node::addChild(Node* node)
{
	Node *left, *right;

	if((left = child))
	{
		right = left->right;
		node->left = left;
		node->right = right;
		right->left = node;
		left->right = node;
	}
	else
	{
		node->left = node->right = node;
	}
	child = node;
	node->parent = this;
}

void Node::removeChild(Node* node)
{
	Node *left, * right;

	if (node->dim)
	{
		left = node->left;
		right = node->right;
		left->right = right;
		right->left = left;
		child = left;
	}
	else
	{
		child = NULL;
	}
}

void Node::replaceChild(Node* new_node)
{
	Node *l, *r = right;

	if (r == this)
	{
		new_node->right = new_node->left = new_node;
	}
	else
	{
		l = left;
		l->right = new_node;
		r->left = new_node;
		new_node->left = l;
		new_node->right = r;
	}

	new_node->parent = parent;
	if (parent->child == this)
		parent->child = new_node;
}
