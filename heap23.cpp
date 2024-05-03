#include "heap23.hpp"
#include "node.hpp"

bool Heap23::isEmpty()
{
	return nNodes == 0;
}

Node2* Heap23::insert(int key, int value = 0)
{
	Node2* node = new Node2(key, value);
	meld(node);
	++nNodes;
	return node;
}

Node2* Heap23::min()
{
	Node2* minNode, *next;
	long k, k2;
	int r, v;

	v = value;
	r = -1;

	while(v)
	{
		v = v >> 1;
		r++;
	}

	minNode = trees[r];
	k = minNode->getPriority();
	while (r > 0)
	{
		r--;
		next = trees[r];
		if (next)
		{
			if ((k2 = next->getPriority()) < k)
			{
				k = k2;
				minNode = next;
			}
		}
	}

	return minNode;
}

Node2* Heap23::extractMin()
{
	Node2 *child, *next, *partner, *minNode = min();

	int r = minNode->dim;
	if ((partner = minNode->partner))
	{
		partner->partner = NULL;
		partner->extra = false;
		partner->parent = NULL;
		partner->left = partner->right = partner;
		trees[r] = partner;
	}
	else
	{
		trees[r] = NULL;
		value -= (1 << r);
	}
	nNodes--;

	child = minNode->child;
	if(child)
	{
		next = child->right;
		next->left = child->right = NULL;
		meld(next);
	}

	return minNode;
}

bool Heap23::merge(Heap23& heap)
{
	for (int i = 0; i < heap.maxTrees; i++)
	{
		if (heap.trees[i] != NULL)
		{
			heap.trees[i]->right = heap.trees[i]->left = NULL;
			meld(heap.trees[i]);
			heap.trees[i] = NULL;
		}
	}

	nNodes += heap.nNodes;
	heap.nNodes = 0;

	return true;
}

void Heap23::remove(Node2* node)
{
	Node2 *p, *m, *ax, *bx, *ap, *bp, *b1, *a1, *a2, *l, *r, *partner = node->partner;
	int d;

	if (node->extra)
	{
		node->partner->partner = NULL;
		node->partner = NULL;
		node->extra = false;
	}
	else if(partner)
	{
		partner->partner = NULL;
		node->partner = NULL;
		partner->extra = false;

		node->replaceChild(partner);
	}
	else
	{
		m = node->right;
		if (m->dim)
		{
			ax = ap = NULL;
			bx = m->child->partner;
			bp = (Node2*)(bx ? NULL : m->child);
		}
		else
		{
			m = node->parent;
			if (m->extra)
			{
				bx = bp = NULL;
				m = m->partner;
				ax = m->child->partner;
				ap = (Node2*) (ax ? NULL : m->child);
			}
			else
			{
				if(m->parent)
				{
					ax = m->left->partner;
					ap = (Node2*) (ax ? NULL : m->left);
				}
				else
				{
					ax = ap = NULL;
				}

				if ((m = m->partner))
				{
					bx = m->child->partner;
					bp = (Node2*) (bx ? NULL : m->child);
				}
				else
				{
					bx = bp = NULL;
				}
			}
		}

		if (bx)
		{
			bx->partner->partner = NULL;
			bx->partner = NULL;
			bx->extra = false;

			node->replaceChild(bx);
		}
		else if (bp)
		{
			 b1 = bp->parent;

			 remove(b1);
			 b1->removeChild(bp);
			 bp->partner = b1;
			 b1->partner = bp;
			 bp->extra = true;
			 b1->dim = node->dim;

			 node->replaceChild(b1);
		}
		else if (ax)
		{
			p = node->parent;
			a2 = ax->partner;
			a1 = a2->parent;

			p->removeChild(node);

			ax->partner = NULL;
			ax->extra = false;

			d = a2->dim;
			a2->dim = p->dim;
			p->dim = d;

			a2->addChild(ax);

			if (p->extra)
			{
				p->partner = NULL;
				p->extra = false;

				a2->partner = a1;
				a1->partner = a2;
				a2->extra = true;

				a2->replaceChild(p);
			}
			else
			{
				a2->partner = NULL;
				if ((l = a2->left) != p)
				{
					r = p->right;
					p->left = l;
					a2->right = r;
					p->right = a2;
					a2->left = p;
					l->right = p;
					r->left = a2;

					if (a1->child == p)
					{
						a1->child = a2;
					}
				}
				else
				{
					a1->child = a2;
				}
			}
		}
		else if(ap)
		{
			p = node->parent;
			p->removeChild(node);
			remove(p);
			p->dim = node->dim;

			p->partner = ap;
			ap->partner = p;

			if (p->getPriority() < ap->getPriority())
			{
				p->extra = false;
				ap->replaceChild(p);
				ap->extra = true;
			}
			else
			{
				p->extra = true;
			}
		}
		else
		{
			d = node->dim;
			p = node->parent;

			p->removeChild(node);

			trees[d + 1] = NULL;
			value -= (1 << (d + 1));
			p->dim = d;

			p->left = p->right = NULL;
			meld(p);
		}
	}
}

void Heap23::decreaseKey(Node2* node, int newKey)
{
	node->key = newKey;

	if(!(node->parent || node->extra))
	{
		return;
	}

	remove(node);
	node->right = node->left = NULL;

	meld(node);
}

void Heap23::meld(Node2* list)
{
	Node2 *next, *addTree, *carryTree;
	int d;

	addTree = list;
	carryTree = NULL;

	do 
	{
		if (addTree)
		{
			next = addTree->right;
			addTree->right = addTree->left = addTree;
			addTree->parent = NULL;
		}
		else
		{
			addTree = carryTree;
			carryTree = NULL;
		}

		if (carryTree)
		{
			mergeNodes(&addTree, &carryTree);
		}

		if (addTree)
		{
			d = addTree->dim;
			if (trees[d])
			{
				mergeNodes(&trees[d], &addTree);
				if (!trees[d]) 
					value -= (1 << d);
				carryTree = addTree;
			}
			else
			{
				trees[d] = addTree;
				value += (1 << d);
			}
		}

		addTree = next;
	} while(addTree || carryTree);
}
