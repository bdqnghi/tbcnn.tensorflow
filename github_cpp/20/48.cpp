#ifndef REDBLACK_H
#define REDBLACK_H

#include "index.h"

using namespace std;

template<class T> class RedBlackTree;

template<class T> class NodeVisitor
{
public:
	virtual ~NodeVisitor() {}
	virtual void visit(const RedBlackTree<T> *node,int depth) = 0;
};



template<class T> class RedBlackTree : public INDEX
{

private:
	static const int red   = 0;
	static const int black = 1;

	int               m_color;
	T                 m_val;
	RedBlackTree      *m_left;
	RedBlackTree     *m_right;

	RedBlackTree(RedBlackTree *b) {
		m_val      = b->m_val;
		m_left     = b->m_left;
		m_right    = b->m_right;
		m_color    = red;
	}

	void copy(RedBlackTree *x) {
		m_val     = x->m_val;
		m_left    = x->m_left;
		m_right   = x->m_right;
		m_color   = x->m_color;

		
		
		
		x->m_left  = 0;
		x->m_right = 0;
		delete x;
	}

	RedBlackTree *RBinsertLeft(T k,int sw) {
		RedBlackTree *l;
		RedBlackTree *b;

		l = m_left;
		if (l == 0) {
			m_left = b = new RedBlackTree(k);
		}
		else {
			b = l->RBinsert(k,sw);
		}
		return b;
	}

	RedBlackTree *RBinsertRight(T k,int sw) {
		RedBlackTree *r;
		RedBlackTree *b;

		r = m_right;
		if (r == 0) {
			m_right = b = new RedBlackTree(k);
		}
		else {
			b = r->RBinsert(k,sw);
		}
		return b;
	}

	RedBlackTree *rotLeft()
	{
		RedBlackTree *x;
		RedBlackTree *me;

		if (m_right == 0) return 0;
		
		
		me          = new RedBlackTree(this);
		x           = me->m_right;
		me->m_right = x->m_left;
		x->m_left   = me;
		return   x;
	}

	RedBlackTree *rotRight()
	{
		RedBlackTree *x;
		RedBlackTree *me;

		if (m_left == 0) return 0;

		
		
		me          = new RedBlackTree(this);
		x           = me->m_left;
		me->m_left  = x->m_right;
		x->m_right  = me;
		return x;
	}

	RedBlackTree *RBinsert(T k,int sw) {
		RedBlackTree *b = 0;
		RedBlackTree *x;
		RedBlackTree *l;
		RedBlackTree *ll;
		RedBlackTree *r;
		RedBlackTree *rr;

		
		
		
		l = m_left;
		r = m_right;
		if ((l != 0)&&(l->m_color==red)&&(r != 0)&&(r->m_color==red)) {
			m_color = red;
			l->m_color = black;
			r->m_color = black;
		}

		
		if (k < m_val) {
			
			b = RBinsertLeft(k,0);

			
			
			
			l = m_left;
			if ((m_color == red)&&(l != 0)&&(l->m_color == red)&&(sw == 1)) {
				x = rotRight();
				if (x != 0) {
					
					copy(x);
				}
			}

			
			l = m_left;
			if (l != 0) {
				ll = l->m_left;
				if (ll != 0) {
					if ((l->m_color == red)&&(ll->m_color == red)) {
						x = rotRight();
						if (x != 0) {
							copy(x);
						}
						m_color = black;
						r = m_right;
						if (r != 0) {
							r->m_color = red;
						}
					}
				}
			}
		}
		else {
			b = RBinsertRight(k,1);

			
			
			
			r = m_right;
			if ((m_color == red)&&(r != 0)&&(r->m_color == red)&&(sw == 0)) {
				x = rotLeft();
				if (x != 0) {
					
					copy(x);
				}
			}

			
			r = m_right;
			if (r != 0) {
				rr = r->m_right;
				if (rr != 0) {
					if ((r->m_color == red)&&(rr->m_color == red)) {
						x = rotLeft();
						if (x != 0) {
							
							copy(x);
						}
						m_color = black;
						l = m_left;
						if (l != 0) {
							l->m_color = red;
						}
					}
				}
			}
		}            

		return b;
	}

	
	
	
public:
	
	RedBlackTree(T x) {
		m_val      = x;
		m_left     = 0;
		m_right    = 0;
		m_color    = red;
	}

	~RedBlackTree() {

		if (m_left != 0) {
			delete m_left;
		}
		if (m_right != 0) {
			delete m_right;
		}
	}

	
	string str() const {
		stringstream s(stringstream::out);
		
		
		s << "[" << m_val << "," << m_color << "]";
		return s.str();
	}

	
	T val() const {
		return m_val;
	}

	
	int color() const {
		return m_color;
	}

	
	
	
	const RedBlackTree *find(const T &key) const {
		const RedBlackTree *result = 0;
		if (key == m_val) {
			result = this;
		}
		else if (key < m_val) {
			if (m_left != 0) {
				result = m_left->find(key);
			}
		}
		else {
			if (m_right != 0) {
				result = m_right->find(key);
			}
		}
		return result;
	}

	
	
	
	
	
	
	void inorder(NodeVisitor<T> *visitor,int depth) const
	{
		if (m_left != 0) {
			m_left->inorder(visitor,depth+1);
		}
		visitor->visit(this,depth);
		if (m_right != 0) {
			m_right->inorder(visitor,depth+1);
		}
	}

	RedBlackTree *insert(T k) {
		RedBlackTree *b;
		b = RBinsert(k,0);
		m_color = black;
		return b;
	}
};

#endif