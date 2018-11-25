
















#ifndef __BINARY_SEARCH_TREE_H
#define __BINARY_SEARCH_TREE_H

#include "QueueLinkedList.h"
#include "Export.h"



namespace BasicDataStructures
{
	
	template <class BinarySearchTreeType>
	class RAK_DLL_EXPORT BinarySearchTree
	{
	
	public:

		struct node
		{
			BinarySearchTreeType* item;
			node* left;
			node* right;
		};
		
		BinarySearchTree();
		virtual ~BinarySearchTree();
		BinarySearchTree( const BinarySearchTree& original_type );
		BinarySearchTree& operator= ( const BinarySearchTree& original_copy );
		unsigned int size( void );
		void clear( void );
		unsigned int height( node* starting_node = 0 );
		node* add ( const BinarySearchTreeType& input );
		node* del( const BinarySearchTreeType& input );
		bool is_in( const BinarySearchTreeType& input );
		void display_inorder( BinarySearchTreeType* return_array );
		void display_preorder( BinarySearchTreeType* return_array );
		void display_postorder( BinarySearchTreeType* return_array );
		void display_breadth_first_search( BinarySearchTreeType* return_array );
		BinarySearchTreeType*& get_pointer_to_node( const BinarySearchTreeType& element );
		
	protected:

		node* root;
		
		enum Direction_Types
		{
			NOT_FOUND, LEFT, RIGHT, ROOT
		}
		
		direction;
		unsigned int height_recursive( node* current );
		unsigned int BinarySearchTree_size;
		node*& find( const BinarySearchTreeType& element, node** parent );
		node*& find_parent( const BinarySearchTreeType& element );
		void display_postorder_recursive( node* current, BinarySearchTreeType* return_array, unsigned int& index );
		void fix_tree( node* current );
		
	};
	
	
	template <class BinarySearchTreeType>
	class RAK_DLL_EXPORT AVLBalancedBinarySearchTree : public BinarySearchTree<BinarySearchTreeType>
	{
	
	public:
		AVLBalancedBinarySearchTree()	{}
		virtual ~AVLBalancedBinarySearchTree();
		void add ( const BinarySearchTreeType& input );
		void del( const BinarySearchTreeType& input );
		BinarySearchTree<BinarySearchTreeType>& operator= ( BinarySearchTree<BinarySearchTreeType>& original_copy )
		{
			return BinarySearchTree<BinarySearchTreeType>::operator= ( original_copy );
		}
		
	private:
		void balance_tree( typename BinarySearchTree<BinarySearchTreeType>::node* current, bool rotateOnce );
		void rotate_right( typename BinarySearchTree<BinarySearchTreeType>::node *C );
		void rotate_left( typename BinarySearchTree<BinarySearchTreeType>::node* C );
		void double_rotate_right( typename BinarySearchTree<BinarySearchTreeType>::node *A );
		void double_rotate_left( typename BinarySearchTree<BinarySearchTreeType>::node* A );
		bool right_higher( typename BinarySearchTree<BinarySearchTreeType>::node* A );
		bool left_higher( typename BinarySearchTree<BinarySearchTreeType>::node* A );
	};
	
	template <class BinarySearchTreeType>
	void AVLBalancedBinarySearchTree<BinarySearchTreeType>::balance_tree( typename BinarySearchTree<BinarySearchTreeType>::node* current, bool rotateOnce )
	{
		int left_height, right_height;
		
		while ( current )
		{
			if ( current->left == 0 )
				left_height = 0;
			else
				left_height = height( current->left );
				
			if ( current->right == 0 )
				right_height = 0;
			else
				right_height = height( current->right );
				
			if ( right_height - left_height == 2 )
			{
				if ( right_higher( current->right ) )
					rotate_left( current->right );
				else
					double_rotate_left( current );
					
				if ( rotateOnce )
					break;
			}
			
			else
				if ( right_height - left_height == -2 )
				{
					if ( left_higher( current->left ) )
						rotate_right( current->left );
					else
						double_rotate_right( current );
						
					if ( rotateOnce )
						break;
				}
				
			if ( current == this->root )
				break;
				
			current = find_parent( *( current->item ) );
			
		}
	}
	
	template <class BinarySearchTreeType>
	void AVLBalancedBinarySearchTree<BinarySearchTreeType>::add ( const BinarySearchTreeType& input )
	{
	
		typename BinarySearchTree<BinarySearchTreeType>::node * current = BinarySearchTree<BinarySearchTreeType>::add ( input );
		balance_tree( current, true );
	}
	
	template <class BinarySearchTreeType>
	void AVLBalancedBinarySearchTree<BinarySearchTreeType>::del( const BinarySearchTreeType& input )
	{
		typename BinarySearchTree<BinarySearchTreeType>::node * current = BinarySearchTree<BinarySearchTreeType>::del( input );
		balance_tree( current, false );
		
	}
	
	template <class BinarySearchTreeType>
	bool AVLBalancedBinarySearchTree<BinarySearchTreeType>::right_higher( typename BinarySearchTree<BinarySearchTreeType>::node *A )
	{
		if ( A == 0 )
			return false;
			
		return height( A->right ) > height( A->left );
	}
	
	template <class BinarySearchTreeType>
	bool AVLBalancedBinarySearchTree<BinarySearchTreeType>::left_higher( typename BinarySearchTree<BinarySearchTreeType>::node *A )
	{
		if ( A == 0 )
			return false;
			
		return height( A->left ) > height( A->right );
	}
	
	template <class BinarySearchTreeType>
	void AVLBalancedBinarySearchTree<BinarySearchTreeType>::rotate_right( typename BinarySearchTree<BinarySearchTreeType>::node *C )
	{
		typename BinarySearchTree<BinarySearchTreeType>::node * A, *B, *D;
		
		
		B = find_parent( *( C->item ) );
		A = find_parent( *( B->item ) );
		D = C->right;
		
		if ( A )
		{
			
			
			if ( this->direction == this->LEFT )
				A->left = C;
			else
				A->right = C;
		}
		
		else
			this->root = C;  
			
		B->left = D;
		
		C->right = B;
	}
	
	template <class BinarySearchTreeType>
	void AVLBalancedBinarySearchTree<BinarySearchTreeType>::double_rotate_right( typename BinarySearchTree<BinarySearchTreeType>::node *A )
	{
		
		rotate_left( A->left->right );
		rotate_right( A->left );
	}
	
	template <class BinarySearchTreeType>
	void AVLBalancedBinarySearchTree<BinarySearchTreeType>::rotate_left( typename BinarySearchTree<BinarySearchTreeType>::node *C )
	{
		typename BinarySearchTree<BinarySearchTreeType>::node * A, *B, *D;
		
		
		B = find_parent( *( C->item ) );
		A = find_parent( *( B->item ) );
		D = C->left;
		
		if ( A )
		{
			
			
			if ( this->direction == this->LEFT )
				A->left = C;
			else
				A->right = C;
		}
		
		else
			this->root = C;  
			
		B->right = D;
		
		C->left = B;
	}
	
	template <class BinarySearchTreeType>
	void AVLBalancedBinarySearchTree<BinarySearchTreeType>::double_rotate_left( typename BinarySearchTree<BinarySearchTreeType>::node *A )
	{
		
		rotate_right( A->right->left );
		rotate_left( A->right );
	}
	
	template <class BinarySearchTreeType>
	AVLBalancedBinarySearchTree<BinarySearchTreeType>::~AVLBalancedBinarySearchTree()
	{
		this->clear();
	}
	
	template <class BinarySearchTreeType>
	unsigned int BinarySearchTree<BinarySearchTreeType>::size( void )
	{
		return BinarySearchTree_size;
	}
	
	template <class BinarySearchTreeType>
	unsigned int BinarySearchTree<BinarySearchTreeType>::height( typename BinarySearchTree::node* starting_node )
	{
		if ( BinarySearchTree_size == 0 || starting_node == 0 )
			return 0;
		else
			return height_recursive( starting_node );
	}
	
	
	template <class BinarySearchTreeType>
	unsigned int BinarySearchTree<BinarySearchTreeType>::height_recursive( typename BinarySearchTree::node* current )
	{
		unsigned int left_height = 0, right_height = 0;
		
		if ( ( current->left == 0 ) && ( current->right == 0 ) )
			return 1; 
			
		if ( current->left != 0 )
			left_height = 1 + height_recursive( current->left );
			
		if ( current->right != 0 )
			right_height = 1 + height_recursive( current->right );
			
		if ( left_height > right_height )
			return left_height;
		else
			return right_height;
	}
	
	template <class BinarySearchTreeType>
	BinarySearchTree<BinarySearchTreeType>::BinarySearchTree()
	{
		BinarySearchTree_size = 0;
		root = 0;
	}
	
	template <class BinarySearchTreeType>
	BinarySearchTree<BinarySearchTreeType>::~BinarySearchTree()
	{
		this->clear();
	}
	
	template <class BinarySearchTreeType>
	BinarySearchTreeType*& BinarySearchTree<BinarySearchTreeType>::get_pointer_to_node( const BinarySearchTreeType& element )
	{
		static typename BinarySearchTree::node * tempnode;
		static BinarySearchTreeType* dummyptr = 0;
		tempnode = find ( element, &tempnode );
		
		if ( this->direction == this->NOT_FOUND )
			return dummyptr;
			
		return tempnode->item;
	}
	
	template <class BinarySearchTreeType>
	typename BinarySearchTree<BinarySearchTreeType>::node*& BinarySearchTree<BinarySearchTreeType>::find( const BinarySearchTreeType& element, typename BinarySearchTree<BinarySearchTreeType>::node** parent )
	{
		static typename BinarySearchTree::node * current;
		
		current = this->root;
		*parent = 0;
		this->direction = this->ROOT;
		
		if ( BinarySearchTree_size == 0 )
		{
			this->direction = this->NOT_FOUND;
			return current = 0;
		}
		
		
		if ( element == *( current->item ) )
		{
			this->direction = this->ROOT;
			return current;
		}

#ifdef _MSC_VER
#pragma warning( disable : 4127 ) 
#endif
		while ( true )
		{
			
			
			if ( element < *( current->item ) )
			{
				*parent = current;
				this->direction = this->LEFT;
				current = current->left;
			}
			
			else
				if ( element > *( current->item ) )
				{
					*parent = current;
					this->direction = this->RIGHT;
					current = current->right;
				}
				
			if ( current == 0 )
				break;
				
			
			if ( element == *( current->item ) )
			{
				return current;
			}
		}
		
		
		this->direction = this->NOT_FOUND;
		return current = 0;
	}
	
	template <class BinarySearchTreeType>
	typename BinarySearchTree<BinarySearchTreeType>::node*& BinarySearchTree<BinarySearchTreeType>::find_parent( const BinarySearchTreeType& element )
	{
		static typename BinarySearchTree::node * parent;
		find ( element, &parent );
		return parent;
	}
	
	
	template <class BinarySearchTreeType>
	void BinarySearchTree<BinarySearchTreeType>::fix_tree( typename BinarySearchTree::node* current )
	{
		BinarySearchTreeType temp;
		
		while ( 1 )
		{
			if ( ( ( current->left ) != 0 ) && ( *( current->item ) < *( current->left->item ) ) )
			{
				
				temp = *( current->left->item );
				*( current->left->item ) = *( current->item );
				*( current->item ) = temp;
				current = current->left;
			}
			
			else
				if ( ( ( current->right ) != 0 ) && ( *( current->item ) > *( current->right->item ) ) )
				{
					
					temp = *( current->right->item );
					*( current->right->item ) = *( current->item );
					*( current->item ) = temp;
					current = current->right;
				}
				
				else
					break;  
		}
	}
	
	template <class BinarySearchTreeType>
	typename BinarySearchTree<BinarySearchTreeType>::node* BinarySearchTree<BinarySearchTreeType>::del( const BinarySearchTreeType& input )
	{
		typename BinarySearchTree::node * node_to_delete, *current, *parent;
		
		if ( BinarySearchTree_size == 0 )
			return 0;
			
		if ( BinarySearchTree_size == 1 )
		{
			clear();
			return 0;
		}
		
		node_to_delete = find( input, &parent );
		
		if ( direction == NOT_FOUND )
			return 0;  
			
		current = node_to_delete;
		
		
		if ( ( current->right ) == 0 && ( current->left ) == 0 )    
		{
		
			if ( parent )
			{
				if ( direction == LEFT )
					parent->left = 0;
				else
					parent->right = 0;
			}
			
			delete node_to_delete->item;
			delete node_to_delete;
			BinarySearchTree_size--;
			return parent;
		}
		else
			if ( ( current->right ) != 0 && ( current->left ) == 0 )   
			{
			
				if ( parent )
				{
					if ( direction == RIGHT )
						parent->right = current->right;
					else
						parent->left = current->right;
				}
				
				else
					root = current->right; 
					
				delete node_to_delete->item;
				
				delete node_to_delete;
				
				BinarySearchTree_size--;
				
				return parent;
			}
			else
				if ( ( current->right ) == 0 && ( current->left ) != 0 )   
				{
				
					if ( parent )
					{
						if ( direction == RIGHT )
							parent->right = current->left;
						else
							parent->left = current->left;
					}
					
					else
						root = current->left; 
						
					delete node_to_delete->item;
					
					delete node_to_delete;
					
					BinarySearchTree_size--;
					
					return parent;
				}
				else 
				{
					parent = current;
					direction = RIGHT;
					current = current->right; 
					
					while ( current->left )
					{
						direction = LEFT;
						parent = current;
						current = current->left;
					}
					
					
					*( node_to_delete->item ) = *( current->item );
					
					
					
					if ( current->right == 0 )
					{
						if ( direction == RIGHT )
							parent->right = 0;
						else
							parent->left = 0;
							
						delete current->item;
						
						delete current;
						
						BinarySearchTree_size--;
						
						return parent;
					}
					
					else
					{
						
						
						if ( direction == RIGHT )
							parent->right = current->right;
						else
							parent->left = current->right;
							
						delete current->item;
						
						delete current;
						
						BinarySearchTree_size--;
						
						return parent;
					}
				}
	}
	
	template <class BinarySearchTreeType>
	typename BinarySearchTree<BinarySearchTreeType>::node* BinarySearchTree<BinarySearchTreeType>::add ( const BinarySearchTreeType& input )
	{
		typename BinarySearchTree::node * current, *parent;
		
		
		
		
		
		
		if ( BinarySearchTree_size == 0 )
		{
			BinarySearchTree_size = 1;
			root = new typename BinarySearchTree::node;
			root->item = new BinarySearchTreeType;
			*( root->item ) = input;
			root->left = 0;
			root->right = 0;
			
			return root;
		}
		
		else
		{
			
			current = parent = root;

#ifdef _MSC_VER
#pragma warning( disable : 4127 ) 
#endif
			while ( true )    
			{
			
				if ( input < *( current->item ) )
				{
					if ( current->left == 0 )
					{
						current->left = new typename BinarySearchTree::node;
						current->left->item = new BinarySearchTreeType;
						current = current->left;
						current->left = 0;
						current->right = 0;
						*( current->item ) = input;
						
						BinarySearchTree_size++;
						return current;
					}
					
					else
					{
						parent = current;
						current = current->left;
					}
				}
				
				else
					if ( input > *( current->item ) )
					{
						if ( current->right == 0 )
						{
							current->right = new typename BinarySearchTree::node;
							current->right->item = new BinarySearchTreeType;
							current = current->right;
							current->left = 0;
							current->right = 0;
							*( current->item ) = input;
							
							BinarySearchTree_size++;
							return current;
						}
						
						else
						{
							parent = current;
							current = current->right;
						}
					}
					
					else
						return 0; 
			}
		}
	}
	
	template <class BinarySearchTreeType>
	bool BinarySearchTree<BinarySearchTreeType>::is_in( const BinarySearchTreeType& input )
	{
		typename BinarySearchTree::node * parent;
		find( input, &parent );
		
		if ( direction != NOT_FOUND )
			return true;
		else
			return false;
	}
	
	
	template <class BinarySearchTreeType>
	void BinarySearchTree<BinarySearchTreeType>::display_inorder( BinarySearchTreeType* return_array )
	{
		typename BinarySearchTree::node * current, *parent;
		bool just_printed = false;
		
		unsigned int index = 0;
		
		current = root;
		
		if ( BinarySearchTree_size == 0 )
			return ; 
			
		else
			if ( BinarySearchTree_size == 1 )
			{
				return_array[ 0 ] = *( root->item );
				return ;
			}
			
			
		direction = ROOT;  
		
		while ( index != BinarySearchTree_size )
		{
			
			
			if ( ( current->left != 0 ) && ( direction != LEFT ) && ( direction != RIGHT ) )
			{
				
				
				
				
				
				current = current->left;
				direction = ROOT;  
			}
			
			else
				if ( ( direction != RIGHT ) && ( just_printed == false ) )
				{
					
					
					
					
					return_array[ index++ ] = *( current->item );
					just_printed = true;
				}
				
				else
					if ( ( current->right != 0 ) && ( direction != RIGHT ) )
					{
						
						
						
						
						current = current->right;
						direction = ROOT;  
						just_printed = false;
					}
					
					else
					{
						
						parent = find_parent( *( current->item ) );
						current = parent;
						just_printed = false;
					}
		}
	}
	
	template <class BinarySearchTreeType>
	void BinarySearchTree<BinarySearchTreeType>::display_preorder( BinarySearchTreeType* return_array )
	{
		typename BinarySearchTree::node * current, *parent;
		
		unsigned int index = 0;
		
		current = root;
		
		if ( BinarySearchTree_size == 0 )
			return ; 
			
		else
			if ( BinarySearchTree_size == 1 )
			{
				return_array[ 0 ] = *( root->item );
				return ;
			}
			
			
		direction = ROOT;  
		return_array[ index++ ] = *( current->item );
		
		while ( index != BinarySearchTree_size )
		{
			
			
			if ( ( current->left != 0 ) && ( direction != LEFT ) && ( direction != RIGHT ) )
			{
			
				current = current->left;
				direction = ROOT;
				
				
				return_array[ index++ ] = *( current->item );
			}
			
			else
				if ( ( current->right != 0 ) && ( direction != RIGHT ) )
				{
					current = current->right;
					direction = ROOT;
					
					
					return_array[ index++ ] = *( current->item );
				}
				
				else
				{
					
					parent = find_parent( *( current->item ) );
					current = parent;
				}
		}
	}
	
	template <class BinarySearchTreeType>
	inline void BinarySearchTree<BinarySearchTreeType>::display_postorder( BinarySearchTreeType* return_array )
	{
		unsigned int index = 0;
		
		if ( BinarySearchTree_size == 0 )
			return ; 
			
		else
			if ( BinarySearchTree_size == 1 )
			{
				return_array[ 0 ] = *( root->item );
				return ;
			}
			
		display_postorder_recursive( root, return_array, index );
	}
	
	
	
	template <class BinarySearchTreeType>
	void BinarySearchTree<BinarySearchTreeType>::display_postorder_recursive( typename BinarySearchTree::node* current, BinarySearchTreeType* return_array, unsigned int& index )
	{
		if ( current->left != 0 )
			display_postorder_recursive( current->left, return_array, index );
			
		if ( current->right != 0 )
			display_postorder_recursive( current->right, return_array, index );
			
		return_array[ index++ ] = *( current->item );
		
	}
	
	
	template <class BinarySearchTreeType>
	void BinarySearchTree<BinarySearchTreeType>::display_breadth_first_search( BinarySearchTreeType* return_array )
	{
		typename BinarySearchTree::node * current;
		unsigned int index = 0;
		
		
		
		
		
		if ( BinarySearchTree_size == 0 )
			return ; 
			
		else
			if ( BinarySearchTree_size == 1 )
			{
				return_array[ 0 ] = *( root->item );
				return ;
			}
			
			else
			{
				BasicDataStructures::QueueLinkedList<node *> tree_queue;
				
				
				tree_queue.push( root );
				
				do
				{
					current = tree_queue.pop();
					return_array[ index++ ] = *( current->item );
					
					
					
					if ( current->left != 0 )
						tree_queue.push( current->left );
						
					if ( current->right != 0 )
						tree_queue.push( current->right );
						
				}
				
				while ( tree_queue.size() > 0 );
			}
	}
	
	
	template <class BinarySearchTreeType>
	BinarySearchTree<BinarySearchTreeType>::BinarySearchTree( const BinarySearchTree& original_copy )
	{
		typename BinarySearchTree::node * current;
		
		
		
		
		
		BinarySearchTree_size = 0;
		root = 0;
		
		if ( original_copy.BinarySearchTree_size == 0 )
		{
			BinarySearchTree_size = 0;
		}
		
		else
		{
			BasicDataStructures::QueueLinkedList<node *> tree_queue;
			
			
			tree_queue.push( original_copy.root );
			
			do
			{
				current = tree_queue.pop();
				
				add ( *( current->item ) )
				
				;
				
				
				if ( current->left != 0 )
					tree_queue.push( current->left );
					
				if ( current->right != 0 )
					tree_queue.push( current->right );
					
			}
			
			while ( tree_queue.size() > 0 );
		}
	}
	
	template <class BinarySearchTreeType>
	BinarySearchTree<BinarySearchTreeType>& BinarySearchTree<BinarySearchTreeType>::operator= ( const BinarySearchTree& original_copy )
	{
		typename BinarySearchTree::node * current;
		
		if ( ( &original_copy ) == this )
			return *this;
			
		clear();  
		
		
		BinarySearchTree_size = 0;
		
		root = 0;
		
		
		
		
		
		if ( original_copy.BinarySearchTree_size == 0 )
		{
			BinarySearchTree_size = 0;
		}
		
		else
		{
			BasicDataStructures::QueueLinkedList<node *> tree_queue;
			
			
			tree_queue.push( original_copy.root );
			
			do
			{
				current = tree_queue.pop();
				
				add ( *( current->item ) )
				
				;
				
				
				if ( current->left != 0 )
					tree_queue.push( current->left );
					
				if ( current->right != 0 )
					tree_queue.push( current->right );
					
			}
			
			while ( tree_queue.size() > 0 );
		}
		
		return *this;
	}
	
	template <class BinarySearchTreeType>
	inline void BinarySearchTree<BinarySearchTreeType>::clear ( void )
	{
		typename BinarySearchTree::node * current, *parent;
		
		current = root;
		
		while ( BinarySearchTree_size > 0 )
		{
			if ( BinarySearchTree_size == 1 )
			{
				delete root->item;
				delete root;
				root = 0;
				BinarySearchTree_size = 0;
			}
			
			else
			{
				if ( current->left != 0 )
				{
					current = current->left;
				}
				
				else
					if ( current->right != 0 )
					{
						current = current->right;
					}
					
					else 
					{
						
						parent = find_parent( *( current->item ) );
						
						if ( ( parent->left ) == current )
							parent->left = 0;
						else
							parent->right = 0;
							
						delete current->item;
						
						delete current;
						
						current = parent;
						
						BinarySearchTree_size--;
					}
			}
		}
	}
	
} 

#endif
