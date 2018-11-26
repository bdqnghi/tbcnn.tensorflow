/*
 * $Id$
 *
    Copyright (c) 2006-2014 Chung, Hyung-Hwan. All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR
    IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
    IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
    NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _QSE_CMN_REDBLACKTABLE_HPP_
#define _QSE_CMN_REDBLACKTABLE_HPP_

/// \file
/// Provides the RedBlackTable class.

#include <qse/cmn/Association.hpp>
#include <qse/cmn/RedBlackTree.hpp>

/////////////////////////////////
QSE_BEGIN_NAMESPACE(QSE)
/////////////////////////////////

template<typename T>
struct RedBlackTableComparator
{
	// it must return true if two values are equal
	int operator() (const T& v1, const T& v2) const
	{
		if (v1 > v2) return 1;
		if (v1 < v2) return -1;
		QSE_ASSERT (v1 == v2);
		return 0;
	}
};


///
/// The RedBlackTable class extends the RedBlackTree class to maintain the
/// pair of a key and a value.
///
template <typename K, typename V, typename COMPARATOR = RedBlackTableComparator<K> >
class RedBlackTable: public Mmged
{
public:
	typedef Association<K,V> Pair;
	typedef RedBlackTable<K,V,COMPARATOR> SelfType;

	typedef RedBlackTableComparator<K> DefaultComparator;

	struct PairComparator
	{
		qse_size_t operator() (const Pair& p1, const Pair& p2) const
		{
			COMPARATOR comparator;
			return comparator (p1.key, p2.key);
		}
	};

	struct PairHeteroComparator
	{
		qse_size_t operator() (const K& p1, const Pair& p2) const
		{
			COMPARATOR comparator;
			return comparator (p1, p2.key);
		}
	};

	template <typename MK, typename MCOMPARATOR>
	struct MHeteroComparator
	{
		qse_size_t operator() (const MK& p1, const Pair& p2) const
		{
			MCOMPARATOR mcomparator;
			return mcomparator (p1, p2.key);
		}
	};

	typedef RedBlackTree<Pair,PairComparator> PairTree;
	typedef typename PairTree::Node PairNode;
	typedef typename PairTree::Iterator Iterator;
	typedef typename PairTree::ConstIterator ConstIterator;


	RedBlackTable (qse_size_t mpb_size = 0):
		Mmged(QSE_NULL), pair_tree(QSE_NULL, mpb_size)
	{
	}

	RedBlackTable (Mmgr* mmgr, qse_size_t mpb_size = 0):
		Mmged(mmgr), pair_tree(mmgr, mpb_size)
	{
	}

	RedBlackTable (const SelfType& table): Mmged(table), pair_tree(table.pair_tree)
	{
	}

	SelfType& operator= (const SelfType& table)
	{
		if (this != &table)
		{
			this->pair_tree = table.pair_tree;
		}
		return *this;
	}

	Mpool& getMpool () 
	{
		return this->pair_tree.getMpool ();
	}

	const Mpool& getMpool () const
	{
		return this->pair_tree.getMpool ();
	}

	qse_size_t getSize() const
	{
		return this->pair_tree.getSize ();
	}

	bool isEmpty () const 
	{
		return this->pair_tree.isEmpty ();
	}

	PairNode* getHeadNode ()
	{
		return this->pair_tree.getHeadNode ();
	}

	const PairNode* getHeadNode () const
	{
		return this->pair_tree.getHeadNode ();
	}

	PairNode* getTailNode ()
	{
		return this->pair_tree.getTailNode ();
	}

	const PairNode* getTailNode () const
	{
		return this->pair_tree.getTailNode ();
	}

	Pair* inject (const K& key, const V& value, int mode, bool* injected = QSE_NULL)
	{
		PairNode* node = this->pair_tree.inject (Pair(key, value), mode, injected);
		if (!node) return QSE_NULL;
		return &node->value;
	}

	Pair* insert (const K& key, const V& value)
	{
		PairNode* node = this->pair_tree.insert (Pair(key, value));
		if (!node) return QSE_NULL;
		return &node->value;
	}

	Pair* ensert (const K& key, const V& value)
	{
		PairNode* node = this->pair_tree.ensert (Pair(key, value));
		if (!node) return QSE_NULL;
		return &node->value;
	}

	Pair* upsert (const K& key, const V& value)
	{
		//PairNode* node = this->pair_tree.upsert (Pair(key, value));
		//if (!node) return QSE_NULL;
		//return &node->value;

		// Don't call pair_tree.upsert() to make sure that the 'key' object
		// itself remains identical after potential update operation. 
		// pair_tree.upsert() changes the Pair object as a whole. so this
		// trick is required.
		bool injected;
		PairNode* node = this->pair_tree.inject (Pair(key, value), 0, &injected);
		QSE_ASSERT (node != QSE_NULL);
		Pair& pair = node->value;
		if (injected) pair.value = value;
		return &pair;
	}

	Pair* update (const K& key, const V& value)
	{
		//PairNode* node = this->pair_tree.update (Pair(key, value));
		//if (!node) return QSE_NULL;
		//return &node->value;

		PairNode* node = this->pair_tree.QSE_CPP_TEMPLATE_QUALIFIER heterofindNode<K,PairHeteroComparator> (key);
		if (!node) return QSE_NULL;
		Pair& pair = node->value;
		pair.value = value;
		return &pair;
	}

	Pair* search (const K& key)
	{
		//PairNode* node = this->pair_tree.update (Pair(key));
		PairNode* node = this->pair_tree.QSE_CPP_TEMPLATE_QUALIFIER heterofindNode<K,PairHeteroComparator> (key);
		if (!node) return QSE_NULL;
		return &node->value;
	}

	int remove (const K& key)
	{
		//return this->pair_tree.remove (Pair(key));
		return this->pair_tree.QSE_CPP_TEMPLATE_QUALIFIER heteroremove<K,PairHeteroComparator> (key);
	}

	template <typename MK, typename MCOMPARATOR>
	Pair* heterosearch (const MK& key)
	{
		typedef MHeteroComparator<MK,MCOMPARATOR> MComparator;
		PairNode* node = this->pair_tree.QSE_CPP_TEMPLATE_QUALIFIER heterosearch<MK,MComparator> (key);
		if (!node) return QSE_NULL;
		return &node->value;
	}

	template <typename MK, typename MCOMPARATOR>
	const Pair* heterosearch (const MK& key) const
	{
		typedef MHeteroComparator<MK,MCOMPARATOR> MComparator;
		PairNode* node = this->pair_tree.QSE_CPP_TEMPLATE_QUALIFIER heterosearch<MK,MComparator> (key);
		if (!node) return QSE_NULL;
		return &node->value;
	}

	template <typename MK, typename MCOMPARATOR>
	int heteroremove (const MK& key)
	{
		typedef MHeteroComparator<MK,MCOMPARATOR> MComparator;
		return this->pair_tree.QSE_CPP_TEMPLATE_QUALIFIER heteroremove<MK,MComparator> (key);
	}

	void clear (bool clear_mpool = false)
	{
		return this->pair_tree.clear (clear_mpool);
	}

	Iterator getIterator (typename Iterator::Mode mode = Iterator::ASCENDING) const
	{
		return this->pair_tree.getIterator (mode);
	}

	ConstIterator getConstIterator (typename ConstIterator::Mode mode = ConstIterator::ASCENDING) const
	{
		return this->pair_tree.getConstIterator (mode);
	}

protected:
	PairTree pair_tree;
};

/////////////////////////////////
QSE_END_NAMESPACE(QSE)
/////////////////////////////////

#endif
