



#ifndef RED_BLACK_NODE_CPP_
#define RED_BLACK_NODE_CPP_



#include "RedBlackNode.h"




template<typename T>
RedBlackNode<T>::RedBlackNode(std::shared_ptr< RedBlackNode< T > > parent_ptr, bool is_red)
    : parent_ptr_(parent_ptr),
      value_ptr_(nullptr),
      is_red_(is_red),
      left_child_ptr_(nullptr),
      right_child_ptr_(nullptr) {}




template<typename T>
RedBlackNode<T>::RedBlackNode(const RedBlackNode<T>& origin)
    : parent_ptr_(origin.parent_ptr_),
      value_ptr_(origin.value_ptr_),
      is_red_(origin.is_red_),
      left_child_ptr_(origin.left_child_ptr_),
      right_child_ptr_(origin.right_child_ptr_) {}




template<typename T>
RedBlackNode<T>::~RedBlackNode() {}




template<typename T>
bool RedBlackNode<T>::empty() const
{
    
    return !value_ptr_;
}




template<typename T>
bool RedBlackNode< T >::is_root() const
{
    
    return (bool) parent_ptr_;
}




template<typename T>
std::shared_ptr< RedBlackNode< T > > RedBlackNode< T >::parent() const
{
    
    return parent_ptr_;
}




template<typename T>
unsigned int RedBlackNode<T>::height() const
{
    
    if (empty())
    {
        
        return 0;
    }

    
    return 1 + std::max(
        left_child_ptr_->height(),
        right_child_ptr_->height()
    );
}




template<typename T>
unsigned int RedBlackNode<T>::total_nodes() const
{
    
    if (empty())
    {
        
        return 0;
    }

    
    return 1 + left_child_ptr_->total_nodes() + right_child_ptr_->total_nodes();
}




template<typename T>
T RedBlackNode<T>::value() const
{
    
    return *value_ptr_;
}




template<typename T>
void RedBlackNode<T>::clear()
{
    
    value_ptr_ = nullptr;
    left_child_ptr_ = nullptr;
    right_child_ptr_ = nullptr;
}




template<typename T>
bool RedBlackNode<T>::contains(T key) const
{
    
    return fetch_descendant(key);
}




template<typename T>
void RedBlackNode<T>::each_preorder(std::function< void(std::shared_ptr< T >) > iteratee)
{
    
    if (empty())
    {
        
        return;
    }

    
    iteratee(value_ptr_);

    
    left_child_ptr_->each_preorder(iteratee);
    right_child_ptr_->each_preorder(iteratee);
}




template<typename T>
void RedBlackNode<T>::each_inorder(std::function< void(std::shared_ptr< T >) > iteratee)
{
    
    if (empty())
    {
        
        return;
    }

    
    left_child_ptr_->each_inorder(iteratee);

    
    iteratee(value_ptr_);

    
    right_child_ptr_->each_inorder(iteratee);
}




template<typename T>
void RedBlackNode<T>::each_postorder(std::function< void(std::shared_ptr< T >) > iteratee)
{
    
    if (empty())
    {
        
        return;
    }

    
    left_child_ptr_->each_postorder(iteratee);
    right_child_ptr_->each_postorder(iteratee);

    
    iteratee(value_ptr_);
}




template<typename T>
bool RedBlackNode<T>::add(const T& key)
{
    
    if (empty())
    {
        
        value_ptr_ = std::make_shared< T >(key);

        
        is_red_ = true;

        
        left_child_ptr_ = std::make_shared< RedBlackNode< T > >(this->shared_from_this(), false);
        right_child_ptr_ = std::make_shared< RedBlackNode< T > >(this->shared_from_this(), false);

        
        fixup();

        
        return true;
    }

    
    else if (key <= *value_ptr_)
    {
        
        return left_child_ptr_->add(key);
    }
    
    
    else
    {
        
        return right_child_ptr_->add(key);
    }
}




template<typename T>
bool RedBlackNode<T>::remove(const T& key) { return false; }




template<typename T>
std::shared_ptr< RedBlackNode< T > > RedBlackNode<T>::fetch_descendant(T key)
{
    
    if (empty())
    {
        
        return nullptr;
    }
    else if (key == *value_ptr_)
    {
        
        return this;
    }
    
    else if (key < *value_ptr_)
    {
        
        return left_child_ptr_->value() == key ? left_child_ptr_->value() : left_child_ptr_->fetch_descendant(key);
    }
    
    else
    {
        
        return right_child_ptr_->value() == key ? right_child_ptr_->value() : right_child_ptr_->fetch_descendant(key);
    }
}




template<typename T>
void RedBlackNode<T>::fixup()
{
    
    if (!parent_ptr_)
    {
        
        is_red_ = false;
    }

    
    else if (is_red_ && parent_ptr_->is_red_)
    {
        
        auto grandparent_ptr = parent_ptr_->parent_ptr_;

        
        auto uncle_ptr = grandparent_ptr->left_child_ptr_ == parent_ptr_ ? grandparent_ptr->right_child_ptr_ : grandparent_ptr->left_child_ptr_;

        
        auto is_left_child = parent_ptr_->left_child_ptr_.get() == this;

        
        if (uncle_ptr && uncle_ptr->is_red_)
        {
            
            parent_ptr_->is_red_ = false;
            uncle_ptr->is_red_ = false;
            grandparent_ptr->is_red_ = true;

            
            grandparent_ptr->fixup();
        }

        
        else
        {
            
            if (
                (is_left_child && grandparent_ptr->left_child_ptr_ == parent_ptr_) ||
                (!is_left_child && grandparent_ptr->right_child_ptr_ == parent_ptr_)
            )
            {
                
                parent_ptr_->is_red_ = false;
                grandparent_ptr->is_red_ = true;

                
                is_left_child ? parent_ptr_->rotate_right() : parent_ptr_->rotate_left();
            }

            
            else
            {
                
                is_left_child ? rotate_right() : rotate_left();

                
                is_red_ = false;
                parent_ptr_->is_red_ = true;

                
                parent_ptr_->left_child_ptr_.get() == this ? rotate_right() : rotate_left();
            }
        }

    }
}




template<typename T>
void RedBlackNode<T>::rotate_left()
{
    
    auto grandparent_ptr = parent_ptr_->parent_ptr_;

    
    auto is_parent_left_child = grandparent_ptr && grandparent_ptr->left_child_ptr_ == parent_ptr_;

    
    parent_ptr_->right_child_ptr_ = left_child_ptr_;
    parent_ptr_->right_child_ptr_->parent_ptr_ = parent_ptr_;

    
    left_child_ptr_ = parent_ptr_;
    parent_ptr_ = grandparent_ptr;
    left_child_ptr_->parent_ptr_ = this->shared_from_this();

    
    if (parent_ptr_)
    {
        
        (is_parent_left_child ? parent_ptr_->left_child_ptr_ : parent_ptr_->right_child_ptr_) = this->shared_from_this();
    }
}



template<typename T>
void RedBlackNode<T>::rotate_right()
{
    
    auto grandparent_ptr = parent_ptr_->parent_ptr_;

    
    auto is_parent_left_child = grandparent_ptr && grandparent_ptr->left_child_ptr_ == parent_ptr_;

    
    parent_ptr_->left_child_ptr_ = right_child_ptr_;
    parent_ptr_->left_child_ptr_->parent_ptr_ = parent_ptr_;

    
    right_child_ptr_ = parent_ptr_;
    parent_ptr_ = grandparent_ptr;
    right_child_ptr_->parent_ptr_ = this->shared_from_this();

    
    if (parent_ptr_)
    {
        
        (is_parent_left_child ? parent_ptr_->left_child_ptr_ : parent_ptr_->right_child_ptr_) = this->shared_from_this();
    }
}



#endif 
