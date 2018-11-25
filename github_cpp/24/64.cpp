#ifndef __THREAD_SAFE_BINARY_SEARCH_TREE_H
#define __THREAD_SAFE_BINARY_SEARCH_TREE_H

#include "DS_BinarySearchTree.h"
#include "SimpleMutex.h"


#ifdef _MSC_VER
#pragma warning( push )
#endif

namespace DataStructures
{
	template <class BinarySearchTreeType>
	class ThreadSafeBinarySearchTree
	{
	private:
		BinarySearchTree<BinarySearchTreeType> m_tree;
		SimpleMutex mutex;
	public:
		BinarySearchTree<BinarySearchTreeType> *LockTree()
		{
			mutex.Lock();
			return &m_tree;
		}
		void ReleaseTree()
		{
			mutex.Unlock();
		}
	public:
		ThreadSafeBinarySearchTree() {}
		ThreadSafeBinarySearchTree( const BinarySearchTree<BinarySearchTreeType>& original_copy )
		{
			LockTree();
			m_tree = original_copy;
			ReleaseTree();
		}
		ThreadSafeBinarySearchTree( const ThreadSafeBinarySearchTree<BinarySearchTreeType>& original_copy )
		{
			LockTree();
			BinarySearchTree<BinarySearchTreeType> *original = original_copy.LockTree();
			m_tree = original;
			original_copy.ReleaseTree();
			ReleaseTree();
		}
		ThreadSafeBinarySearchTree& operator= ( const BinarySearchTree<BinarySearchTreeType>& original_copy )
		{
			LockTree();
			m_tree = original_copy;
			ReleaseTree();
			return *this;
		}
		ThreadSafeBinarySearchTree& operator= ( const ThreadSafeBinarySearchTree<BinarySearchTreeType>& original_copy )
		{
			LockTree();
			BinarySearchTree<BinarySearchTreeType> *original = original_copy.LockTree();
			m_tree = original;
			original_copy.ReleaseTree();
			ReleaseTree();
			return *this;
		}
		unsigned int Size( void )
		{
			LockTree();
			unsigned int size = m_tree.Size();
			ReleaseTree();
			return size;
		}
		void Clear( void )
		{
			LockTree();
			m_tree.Clear();
			ReleaseTree();
		}
		unsigned int Height( typename BinarySearchTree<BinarySearchTreeType>::node* starting_node = 0 )
		{
			LockTree();
			unsigned int height = m_tree.Height(starting_node);
			ReleaseTree();
			return height;
		}
		typename BinarySearchTree<BinarySearchTreeType>::node* Add ( const BinarySearchTreeType& input )
		{
			LockTree();
			typename BinarySearchTree<BinarySearchTreeType>::node * myNode = m_tree.Add(input);
			ReleaseTree();
			return myNode;
		}
		typename BinarySearchTree<BinarySearchTreeType>::node* Del( const BinarySearchTreeType& input, bool *deleted = 0 )
		{
			LockTree();
			typename BinarySearchTree<BinarySearchTreeType>::node *myNode = m_tree.Del(input, deleted);
			ReleaseTree();
			return myNode;
		}
		bool IsIn( const BinarySearchTreeType& input )
		{
			LockTree();
			bool isIn = m_tree.IsIn(input);
			ReleaseTree();
			return isIn;
		}
		void DisplayInorder( BinarySearchTreeType* return_array )
		{
			LockTree();
			m_tree.DisplayInorder(return_array);
			ReleaseTree();
		}
		void DisplayPreorder( BinarySearchTreeType* return_array )
		{
			LockTree();
			m_tree.DisplayPreorder(return_array);
			ReleaseTree();
		}
		void DisplayPostorder( BinarySearchTreeType* return_array )
		{
			LockTree();
			m_tree.DisplayPostorder(return_array);
			ReleaseTree();
		}
		void DisplayBreadthFirstSearch( BinarySearchTreeType* return_array )
		{
			LockTree();
			m_tree.DisplayBreadthFirstSearch(return_array);
			ReleaseTree();
		}
		BinarySearchTreeType* GetPointerToNode( const BinarySearchTreeType& element )
		{
			LockTree();
			BinarySearchTreeType * data = m_tree.GetPointerToNode(element);
			ReleaseTree();
			return data;
		}
		typename BinarySearchTree<BinarySearchTreeType>::node *&GetRoot() 
		{
			LockTree();
			typename BinarySearchTree<BinarySearchTreeType>::node *myRoot = m_tree.root;
			ReleaseTree();
			return myRoot; 
		}
	};
	
	
	template <class BinarySearchTreeType>
	class ThreadSafeAVLBalancedBinarySearchTree
	{
	private:
		AVLBalancedBinarySearchTree<BinarySearchTreeType> m_tree;
		SimpleMutex mutex;
	public:
		AVLBalancedBinarySearchTree<BinarySearchTreeType> *LockTree()
		{
			mutex.Lock();
			return &m_tree;
		}
		void ReleaseTree()
		{
			mutex.Unlock();
		}
	public:
		ThreadSafeAVLBalancedBinarySearchTree()	{}

		
		unsigned int Size( void )
		{
			LockTree();
			unsigned int size = m_tree.Size();
			ReleaseTree();
			return size;
		}
		void Clear( void )
		{
			LockTree();
			m_tree.Clear();
			ReleaseTree();
		}
		unsigned int Height( typename BinarySearchTree<BinarySearchTreeType>::node* starting_node = 0 )
		{
			LockTree();
			unsigned int height = m_tree.Height(starting_node);
			ReleaseTree();
			return height;
		}
		bool Add ( const BinarySearchTreeType& input )
		{
			LockTree();
			bool added = m_tree.Add(input);
			ReleaseTree();
			return added;
		}
		bool Del( const BinarySearchTreeType& input )
		{
			LockTree();
			bool deleted = m_tree.Del(input);
			ReleaseTree();
			return deleted;
		}
		bool IsIn( const BinarySearchTreeType& input )
		{
			LockTree();
			bool isIn = m_tree.IsIn(input);
			ReleaseTree();
			return isIn;
		}
		void DisplayInorder( BinarySearchTreeType* return_array )
		{
			LockTree();
			m_tree.DisplayInorder(return_array);
			ReleaseTree();
		}
		void DisplayPreorder( BinarySearchTreeType* return_array )
		{
			LockTree();
			m_tree.DisplayPreorder(return_array);
			ReleaseTree();
		}
		void DisplayPostorder( BinarySearchTreeType* return_array )
		{
			LockTree();
			m_tree.DisplayPostorder(return_array);
			ReleaseTree();
		}
		void DisplayBreadthFirstSearch( BinarySearchTreeType* return_array )
		{
			LockTree();
			m_tree.DisplayBreadthFirstSearch(return_array);
			ReleaseTree();
		}
		BinarySearchTreeType* GetPointerToNode( const BinarySearchTreeType& element )
		{
			LockTree();
			BinarySearchTreeType * data = m_tree.GetPointerToNode(element);
			ReleaseTree();
			return data;
		}
		typename BinarySearchTree<BinarySearchTreeType>::node *&GetRoot() 
		{
			LockTree();
			typename BinarySearchTree<BinarySearchTreeType>::node *myRoot = m_tree.root;
			ReleaseTree();
			return myRoot; 
		}

		ThreadSafeAVLBalancedBinarySearchTree( const BinarySearchTree<BinarySearchTreeType>& original_copy )
		{
			LockTree();
			m_tree = original_copy;
			ReleaseTree();
		}
		ThreadSafeAVLBalancedBinarySearchTree( const ThreadSafeAVLBalancedBinarySearchTree& original_copy )
		{
			LockTree();
			AVLBalancedBinarySearchTree<BinarySearchTreeType> *original = original_copy.LockTree();
			m_tree = original;
			original_copy.ReleaseTree();
			ReleaseTree();
		}
		ThreadSafeAVLBalancedBinarySearchTree& operator= ( const BinarySearchTree<BinarySearchTreeType>& original_copy )
		{
			LockTree();
			m_tree = original_copy;
			ReleaseTree();
			return *this;
		}
		ThreadSafeAVLBalancedBinarySearchTree& operator= ( const ThreadSafeAVLBalancedBinarySearchTree& original_copy )
		{
			LockTree();
			AVLBalancedBinarySearchTree<BinarySearchTreeType> *original = original_copy.LockTree();
			m_tree = original;
			original_copy.ReleaseTree();
			ReleaseTree();
			return *this;
		}

	};
	
	
} 

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif

