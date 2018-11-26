/**
 *
 * @file RedBlackNode.cpp
 *
 * @brief Red-black node class implementation.
 *
 * @author Josh Wiley
 *
 * @details Implements the RedBlackNode class.
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef RED_BLACK_NODE_CPP_
#define RED_BLACK_NODE_CPP_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include "RedBlackNode.h"
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Default initializes empty (red) node
 *
 */
template<typename T>
RedBlackNode<T>::RedBlackNode(std::shared_ptr< RedBlackNode< T > > parent_ptr, bool is_red)
    : parent_ptr_(parent_ptr),
      value_ptr_(nullptr),
      is_red_(is_red),
      left_child_ptr_(nullptr),
      right_child_ptr_(nullptr) {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Copy-initializes node
 *
 */
template<typename T>
RedBlackNode<T>::RedBlackNode(const RedBlackNode<T>& origin)
    : parent_ptr_(origin.parent_ptr_),
      value_ptr_(origin.value_ptr_),
      is_red_(origin.is_red_),
      left_child_ptr_(origin.left_child_ptr_),
      right_child_ptr_(origin.right_child_ptr_) {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Destructor
 *
 */
template<typename T>
RedBlackNode<T>::~RedBlackNode() {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a boolean value indicating if the node is empty
 *
 * @return Boolean value indicating if the tree is empty
 *
 */
template<typename T>
bool RedBlackNode<T>::empty() const
{
    // Empty if no value.
    return !value_ptr_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a boolean value indicating whether or not the node has a
 *          parent (is the root node)
 *
 * @return Boolean value indicating whether or not the node has a parent
 *
 */
template<typename T>
bool RedBlackNode< T >::is_root() const
{
    // Return boolean indicating whether or not the node has a parent.
    return (bool) parent_ptr_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a smart pointer to parent node
 *
 * @return Smart pointer to parent node
 *
 */
template<typename T>
std::shared_ptr< RedBlackNode< T > > RedBlackNode< T >::parent() const
{
    // Return pointer to parent.
    return parent_ptr_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a number indicating the current height of the tree
 *
 * @return Integer indicating the current height of the tree
 *
 */
template<typename T>
unsigned int RedBlackNode<T>::height() const
{
    // Empty?
    if (empty())
    {
        // Return 0.
        return 0;
    }

    // Return.
    return 1 + std::max(
        left_child_ptr_->height(),
        right_child_ptr_->height()
    );
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a number indicating the current number of nodes in the tree
 *
 * @return Integer indicating the current number of nodes in the tree
 *
 */
template<typename T>
unsigned int RedBlackNode<T>::total_nodes() const
{
    // Empty?
    if (empty())
    {
        // Return 0.
        return 0;
    }

    // Return.
    return 1 + left_child_ptr_->total_nodes() + right_child_ptr_->total_nodes();
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns the value of the node
 *
 * @return Returns the value of the node
 *
 */
template<typename T>
T RedBlackNode<T>::value() const
{
    // Return root value.
    return *value_ptr_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Clears the tree
 *
 */
template<typename T>
void RedBlackNode<T>::clear()
{
    // Reset all pointers.
    value_ptr_ = nullptr;
    left_child_ptr_ = nullptr;
    right_child_ptr_ = nullptr;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Searches the tree for the value and returns a boolean value that
 *          represents the results of the search.
 *
 * @param[in] key
 *            Value used for comparison in search.
 *
 * @return Boolean value that represents the results of the search.
 *
 */
template<typename T>
bool RedBlackNode<T>::contains(T key) const
{
    // Return search result.
    return fetch_descendant(key);
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Iterates over the tree in preorder and executes the iteratee on each
 *          item.
 *
 * @param[in] iteratee
 *            Function to execute with each item.
 *
 */
template<typename T>
void RedBlackNode<T>::each_preorder(std::function< void(std::shared_ptr< T >) > iteratee)
{
    // Empty?
    if (empty())
    {
        // Abort.
        return;
    }

    // Process.
    iteratee(value_ptr_);

    // Forward.
    left_child_ptr_->each_preorder(iteratee);
    right_child_ptr_->each_preorder(iteratee);
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Iterates over the tree in order and executes the iteratee on each
 *          item.
 *
 * @param[in] iteratee
 *            Function to execute with each item.
 *
 */
template<typename T>
void RedBlackNode<T>::each_inorder(std::function< void(std::shared_ptr< T >) > iteratee)
{
    // Empty?
    if (empty())
    {
        // Abort.
        return;
    }

    // Forward.
    left_child_ptr_->each_inorder(iteratee);

    // Process.
    iteratee(value_ptr_);

    // Forward.
    right_child_ptr_->each_inorder(iteratee);
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Iterates over the tree in postorder and executes the iteratee on each
 *          item.
 *
 * @param[in] iteratee
 *            Function to execute with each item.
 *
 */
template<typename T>
void RedBlackNode<T>::each_postorder(std::function< void(std::shared_ptr< T >) > iteratee)
{
    // Empty?
    if (empty())
    {
        // Abort.
        return;
    }

    // Forward.
    left_child_ptr_->each_postorder(iteratee);
    right_child_ptr_->each_postorder(iteratee);

    // Process.
    iteratee(value_ptr_);
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Adds item with the value of the key parameter to the correct
 *          position in the tree and restructures/repaints the tree to maintain
 *          balance.
 *
 * @param[in] key
 *            Item to add to tree.
 *
 */
template<typename T>
bool RedBlackNode<T>::add(const T& key)
{
    // Empty?
    if (empty())
    {
        // Add node.
        value_ptr_ = std::make_shared< T >(key);

        // Make red.
        is_red_ = true;

        // Default-initialize child nodes.
        left_child_ptr_ = std::make_shared< RedBlackNode< T > >(this->shared_from_this(), false);
        right_child_ptr_ = std::make_shared< RedBlackNode< T > >(this->shared_from_this(), false);

        // Fix-up.
        fixup();

        // Return success.
        return true;
    }

    // Left sub-tree?
    else if (key <= *value_ptr_)
    {
        // Add left.
        return left_child_ptr_->add(key);
    }
    
    // Right sub-tree.
    else
    {
        // Add right.
        return right_child_ptr_->add(key);
    }
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Removes item specified by the value of key from the tree.
 *          (TODO: IMPLEMENT)
 *
 * @param[in] key
 *            Item to remove from the tree.
 *
 */
template<typename T>
bool RedBlackNode<T>::remove(const T& key) { return false; }
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Searches for node with specified value in tree and returns a smart
 *          pointer to it.
 *
 * @param[in] key
 *            Item to search for in the tree.
 *
 */
template<typename T>
std::shared_ptr< RedBlackNode< T > > RedBlackNode<T>::fetch_descendant(T key)
{
    // Is empty or equal?
    if (empty())
    {
        // No match.
        return nullptr;
    }
    else if (key == *value_ptr_)
    {
        // Return this.
        return this;
    }
    // Is in left tree?
    else if (key < *value_ptr_)
    {
        // Return result from left tree.
        return left_child_ptr_->value() == key ? left_child_ptr_->value() : left_child_ptr_->fetch_descendant(key);
    }
    // In right tree.
    else
    {
        // Return result from right tree.
        return right_child_ptr_->value() == key ? right_child_ptr_->value() : right_child_ptr_->fetch_descendant(key);
    }
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Balances tree (after recolor).
 *
 */
template<typename T>
void RedBlackNode<T>::fixup()
{
    // Root?
    if (!parent_ptr_)
    {
        // Make black.
        is_red_ = false;
    }

    // "Red" violation (node and parent are both red).
    else if (is_red_ && parent_ptr_->is_red_)
    {
        // Get grandparent.
        auto grandparent_ptr = parent_ptr_->parent_ptr_;

        // Get uncle.
        auto uncle_ptr = grandparent_ptr->left_child_ptr_ == parent_ptr_ ? grandparent_ptr->right_child_ptr_ : grandparent_ptr->left_child_ptr_;

        // Left child?
        auto is_left_child = parent_ptr_->left_child_ptr_.get() == this;

        // Red uncle?
        if (uncle_ptr && uncle_ptr->is_red_)
        {
            // Push "red" violation up the tree.
            parent_ptr_->is_red_ = false;
            uncle_ptr->is_red_ = false;
            grandparent_ptr->is_red_ = true;

            // Fixup at grandparent.
            grandparent_ptr->fixup();
        }

        // No uncle or uncle is black.
        else
        {
            // Outer child (left child of left child or right child of right child)?
            if (
                (is_left_child && grandparent_ptr->left_child_ptr_ == parent_ptr_) ||
                (!is_left_child && grandparent_ptr->right_child_ptr_ == parent_ptr_)
            )
            {
                // Color parent black and grandparent red.
                parent_ptr_->is_red_ = false;
                grandparent_ptr->is_red_ = true;

                // Rotate inward.
                is_left_child ? parent_ptr_->rotate_right() : parent_ptr_->rotate_left();
            }

            // Inner child.
            else
            {
                // Rotate outward about this node.
                is_left_child ? rotate_right() : rotate_left();

                // Fix as if case #2.
                is_red_ = false;
                parent_ptr_->is_red_ = true;

                // Rotate inward about this node.
                parent_ptr_->left_child_ptr_.get() == this ? rotate_right() : rotate_left();
            }
        }

    }
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Rotate left about this node.
 *
 */
template<typename T>
void RedBlackNode<T>::rotate_left()
{
    // Save grandparent.
    auto grandparent_ptr = parent_ptr_->parent_ptr_;

    // Is parent left child?
    auto is_parent_left_child = grandparent_ptr && grandparent_ptr->left_child_ptr_ == parent_ptr_;

    // Parent adopts (left) child as its right.
    parent_ptr_->right_child_ptr_ = left_child_ptr_;
    parent_ptr_->right_child_ptr_->parent_ptr_ = parent_ptr_;

    // Parent becomes (left) child.
    left_child_ptr_ = parent_ptr_;
    parent_ptr_ = grandparent_ptr;
    left_child_ptr_->parent_ptr_ = this->shared_from_this();

    // New parent?
    if (parent_ptr_)
    {
        // Bind granparent to new child.
        (is_parent_left_child ? parent_ptr_->left_child_ptr_ : parent_ptr_->right_child_ptr_) = this->shared_from_this();
    }
}
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Rotate right about this node.
 *
 */
template<typename T>
void RedBlackNode<T>::rotate_right()
{
    // Save grandparent.
    auto grandparent_ptr = parent_ptr_->parent_ptr_;

    // Is parent left child?
    auto is_parent_left_child = grandparent_ptr && grandparent_ptr->left_child_ptr_ == parent_ptr_;

    // Parent adopts (right) child as its left.
    parent_ptr_->left_child_ptr_ = right_child_ptr_;
    parent_ptr_->left_child_ptr_->parent_ptr_ = parent_ptr_;

    // Parent becomes (right) child.
    right_child_ptr_ = parent_ptr_;
    parent_ptr_ = grandparent_ptr;
    right_child_ptr_->parent_ptr_ = this->shared_from_this();

    // New parent?
    if (parent_ptr_)
    {
        // Bind granparent to new child.
        (is_parent_left_child ? parent_ptr_->left_child_ptr_ : parent_ptr_->right_child_ptr_) = this->shared_from_this();
    }
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // RED_BLACK_NODE_CPP_
//