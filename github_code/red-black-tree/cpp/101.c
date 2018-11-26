//
//  RedBlackTree.cpp
//  RedBlackTree
//
//  Created by RogerChen on 14-9-6.
//  Copyright (c) 2014年 RogerChen. All rights reserved.
//

#include "RedBlackTree.h"

inline bool RedBlackTree::isRed(const pNode &x)
{
    if(x == nullptr)
    {
        return BLACK;
    }
    else
    {
        return x -> isRed();
    }
}

void RedBlackTree::set(string key, int value)
{
    root = set(std::move(root), key, value);
    root -> color_ = BLACK;
}

auto RedBlackTree::set(pNode n, string key, int value) -> pNode
{
    if(n == nullptr)
    {
        //make_unique takes universal reference of the parameters passed.
        return make_unique<Node>(key, value, 1, +RED);
    }
    
    if(key < n -> key_)
    {
        n -> left_ = set(std::move(n -> left_), key, value);
    }
    else if(key > n -> key_)
    {
        n -> right_ = set(std::move(n -> right_), key, value);
    }
    else
    {
        n -> value_ = value;
    }
    
    if(isRed(n -> right_) && !isRed(n -> left_))
    {
        n = rotateLeft(std::move(n));
    }
    if(isRed(n -> left_) && isRed(n -> left_ -> left_))
    {
        n = rotateRight(std::move(n));
    }
    if(isRed(n -> left_) && isRed(n -> right_))
    {
        flipColor(n);
    }
    n -> N_ = size(n -> left_) + size(n -> right_) + 1;
    
    return n;
}

int& RedBlackTree::get(const string &key)
{
    return get(root, key);
}

int& RedBlackTree::get(const pNode &n, const string &key)
{
    if(key < n -> key_)
    {
        return get(n -> left_, key);
    }
    else if(key > n -> key_)
    {
        return get(n -> right_, key);
    }
    
    return n -> value_;
}

auto RedBlackTree::rotateLeft(pNode n) -> pNode
{
    pNode x                = std::move(n -> right_);
    n -> right_            = std::move(x -> left_);
    x -> left_             = std::move(n);
    x -> color_            = x -> left_ -> color_;
    x -> left_ -> color_   = RED;
    x -> N_                = x -> left_ -> N_;
    x -> left_ -> N_       = size(x -> left_ -> left_) + size(x -> left_ -> right_) + 1;
    return x;
}

auto RedBlackTree::rotateRight(pNode n) -> pNode
{
    pNode x                = std::move(n -> left_);
    n -> left_             = std::move(x -> right_);
    x -> right_            = std::move(n);
    x -> color_            = x -> left_ -> color_;
    x -> right_ -> color_  = RED;
    x -> N_                = x->right_->N_;
    x -> right_ -> N_      = size(x -> right_ -> left_) + size(x -> right_ -> right_) + 1;
    return x;
}

void RedBlackTree::flipColor(pNode &n)
{
    n -> color_            = !n -> color_;
    n -> left_ -> color_   = !n -> left_ -> color_;
    n -> right_ -> color_  = !n -> right_ -> color_;
}

int RedBlackTree::size(const pNode &n)
{
    if(n == nullptr)
    {
        return 0;
    }
    
    return n -> N_;
}

int RedBlackTree::size()
{
    return this -> size(root);
}
