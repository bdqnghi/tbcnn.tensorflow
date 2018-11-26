#ifndef AVL_TREE_H
#define AVL_TREE_H

class comparable
{
public:
	virtual bool operator<(const comparable &o) = 0;
	virtual bool operator>(const comparable &o) = 0;
	virtual bool operator==(const comparable &o) = 0;
	virtual bool operator<=(const comparable &o) = 0;
	virtual bool operator>=(const comparable &o) = 0;
	virtual int operator-(const comparable &o);
};

template <typename comparable>
class avltree;

template <typename T>
class avltree_node
{
	friend class avltree<T>;
public:
	avltree_node() : 
	  left(NULL),
	  right(NULL),
	  parent(NULL),
	  balance(0) 
	  {
	  }
	avltree_node(const T &e) :
	  element(e),
	  left(NULL),
	  right(NULL),
	  parent(NULL)
	  {
	  }
private:
	T element;
	avltree_node *left;
	avltree_node *right;
	avltree_node *parent;
	int balance;
};

template <typename T>
class avltree
{
public:
	avltree() :
	  root(NULL),
	  first(NULL),
	  last(NULL),
	  length(-1)
	  {
	  }
	avltree_node<T> *insert(const T &data);
	avltree_node<T> *find(const T &data);
	avltree_node<T> *remove(const T &data);
	avltree_node<T> *get_root(){ return root; }
	avltree_node<T> *get_first(){ return first;}
	avltree_node<T> *get_last() { return last; }
	avltree_node<T> *priv(const avltree_node<T> *node);
	avltree_node<T> *next(const avltree_node<T> *node);
	int height();
private:
	avltree_node<T> *find(const T &data, 
		avltree_node<T> **unbalance, avltree_node<T> **parent);
	void rotate_left(avltree_node<T> *node);
	void rotate_right(avltree_node<T> *node);
	avltree_node<T> *get_first(avltree_node<T> *node);
	avltree_node<T> *get_last(avltree_node<T> *node);
	avltree_node<T> *root;
	avltree_node<T> *first;
	avltree_node<T> *last;
	int height;
};

template <typename T>
avltree_node<T> *avltree<T>::find(const T &data, 
	avltree_node<T> **unbalance, avltree_node<T> **parent)
{
	avltree_node<T> *p = root;
	*parent = NULL;
	*unbalance = NULL;

	while(p && p->element != data)
	{
		*parent = p;
		if (p->balance)
		{
			*unbalance = p;
		}

		if (p->element > data)
			p = p->left;
		else
			p = p->right;
	}

	return p;
}

template <typename T>
avltree_node<T> *avltree<T>::find(const T &data)
{
	avltree_node<T> *p, *q;
	return find(data, &p, &q);
}

template <typename T>
avltree_node<T> *avltree<T>::next(avltree_node<T> *node)
{
	if( !node )
		return NULL;
	if (node->right)
		return get_first(node->right);
	
	avltree_node<T> *p;
	while ( ( p = node->parent) && p->right == node)
		node = p;

	return p;
}

template <typename T>
avltree_node<T> *avltree<T>::priv(avltree_node<T> *node)
{
	if( !node )
		return NULL;
	if (node->left)
		return get_last(node->right);
	
	avltree_node<T> *p;
	while ( ( p = node->parent) && p->left == node)
		node = p;

	return p;
}

template <typename T>
avltree_node<T> *avltree<T>::get_first(avltree_node<T> *node)
{
	while(node)
		node = node->left;
	return node;
}

template <typename T>
avltree_node<T> *avltree<T>::get_last(avltree_node<T> *node)
{
	while(node)
		node = node->right;
	return node;
}

template <typename T>
avltree_node<T> *avltree<T>::insert(const T &data)
{
	avltree_node<T> *parent, *unbalance;
	unbalance = root;
	avltree_node<T> *p = find(data, &unbalance, &parent);

	if (p)
		return p;
	avltree_node<T> *node =  new avltree_node<T>(data);

	if (!root)
	{
		root = node;
		first = last = node;
		++height;

		return node;
	}

	if (data < parent->element) // insert at left subtree
	{
		if (first == parent)
		{
			first = node;
		}
		parent->left = node;
	}
	else
	{
		if (last == parent)
		{
			last = node;
		}
		parent->right = node;
	}
	node->parent = parent;

	for(;;)
	{
		if (parent->left == node)
			parent->balance++;
		else
			parent->balance--;

		if (parent == unbalance)
			break;
		node = parent;
		parent = parent->parent;
	}

	switch(unbalance->balance)
	{
		case -1:
		case 1:
			tree->height++;
		case 0:
			break;
		case 2:
	}
}

#endif  
