#include <queue>
#include <vector>
#include "avl_tree.h"
#include "utils.h"

using namespace std;
using namespace utils;

namespace data_structures {

avl_tree::avl_tree()
{

}

int avl_tree::height(const avl_tree_node *t)
{
    return t == nullptr ? -1 : t->height;
}

static void rotate_right(binary_tree_node *& t)
{
    auto l = t->left;
    t->left = l->right;
    l->right = t;
    ((avl_tree_node*)t)->height = 1 + max(avl_tree::height((avl_tree_node*)t->left), avl_tree::height((avl_tree_node*)t->right));
    ((avl_tree_node*)l)->height = 1 + max(avl_tree::height((avl_tree_node*)l->left), ((avl_tree_node*)t)->height);
    t = l;
}

static void rotate_left(binary_tree_node *& t)
{
    auto r = t->right;
    t->right = r->left;
    r->left = t;
    ((avl_tree_node*)t)->height = 1 + max(avl_tree::height((avl_tree_node*)t->right), avl_tree::height((avl_tree_node*)t->left));
    ((avl_tree_node*)r)->height = 1 + max(avl_tree::height((avl_tree_node*)r->right), ((avl_tree_node*)t)->height);
    t = r;
}

static void rotate_left_right(binary_tree_node *& t)
{
    rotate_left(t->left);
    rotate_right(t);
}

static void rotate_left_right_single_call(binary_tree_node *& t)
{
    auto p1 = t;
    auto p2 = t->left;
    auto p3 = p2->right;
    p1->left = p3->right;
    p3->right = p1;
    p2->right = p3->left;
    p3->left = p2;
    t = p3;
    ((avl_tree_node*)p2)->height = 1 + max(avl_tree::height((avl_tree_node*)p2->right), avl_tree::height((avl_tree_node*)p2->left));
    ((avl_tree_node*)p1)->height = 1 + max(avl_tree::height((avl_tree_node*)p1->right), avl_tree::height((avl_tree_node*)p1->left));
    ((avl_tree_node*)t)->height = 1 + max(((avl_tree_node*)p1)->height, ((avl_tree_node*)p2)->height);
}

static void rotate_right_left_single_call(binary_tree_node *& t)
{
    auto p1 = t;
    auto p2 = t->right;
    auto p3 = p2->left;
    p1->right = p3->left;
    p3->left = p1;
    p2->left = p3->right;
    p3->right = p2;
    t = p3;
    ((avl_tree_node*)p2)->height = 1 + max(avl_tree::height((avl_tree_node*)p2->right), avl_tree::height((avl_tree_node*)p2->left));
    ((avl_tree_node*)p1)->height = 1 + max(avl_tree::height((avl_tree_node*)p1->right), avl_tree::height((avl_tree_node*)p1->left));
    ((avl_tree_node*)t)->height = 1 + max(((avl_tree_node*)p1)->height, ((avl_tree_node*)p2)->height);
}

static void rotate_right_left(binary_tree_node *& t)
{
    rotate_right(t->right);
    rotate_left(t);
}

void avl_tree::insert(binary_tree_node *&t, int v)
{
    if (t == nullptr)
    {
        t = new avl_tree_node(v);
        return;
    }
    if (v < t->value)
    {
        insert(t->left, v);
        if (height((const avl_tree_node*)t->left) - height((const avl_tree_node*)t->right) == 2)
        {
            if (v < t->left->value)
                data_structures::rotate_right(t);
            else
                data_structures::rotate_left_right_single_call(t);
        }
    } else if (v > t->value)
    {
        insert(t->right, v);
        if (height((const avl_tree_node*)t->right) - height((const avl_tree_node*)t->left) == 2)
        {
            if (v > t->right->value)
                data_structures::rotate_left(t);
            else
                data_structures::rotate_right_left_single_call(t);
        }
    }
    dynamic_cast<avl_tree_node*>(t)->height =
            1 + max(height((const avl_tree_node*)t->right), height((const avl_tree_node*)t->left));
}

static void rebalance_after_insert(binary_tree_node*& t, vector<binary_tree_node*>& stack, int v, int pv)
{
    binary_tree_node* p = nullptr;
    while (!stack.empty())
    {
        p = stack.back();
        stack.pop_back();
        int hl = avl_tree::height((const avl_tree_node*)p->left);
        int hr = avl_tree::height((const avl_tree_node*)p->right);
        if (hl > hr + 1)
        {
            if (v < pv && v < p->value)
                data_structures::rotate_right(stack.empty() ? p : (stack.back()->left == p ? stack.back()->left : stack.back()->right));
            else
                data_structures::rotate_left_right_single_call(stack.empty() ? p : (stack.back()->left == p ? stack.back()->left : stack.back()->right));
        }
        else if (hr > hl + 1)
        {
            if (v > p->value && v > p->right->value)
                data_structures::rotate_left(stack.empty() ? p : (stack.back()->left == p ? stack.back()->left : stack.back()->right));
            else
                data_structures::rotate_right_left_single_call(stack.empty() ? p : (stack.back()->left == p ? stack.back()->left : stack.back()->right));
        }
        ((avl_tree_node*)p)->height = 1 + max(avl_tree::height((const avl_tree_node*)p->left), avl_tree::height((const avl_tree_node*)p->right));
    }
    t = p;
}

void avl_tree::insert_iterative(binary_tree_node *&t, int v)
{
    auto n = new avl_tree_node(v);
    if (t == nullptr)
    {
        t = n;
        return;
    }
    binary_tree_node* curr = t;
    auto stack = vector<binary_tree_node*>();
    while (curr != nullptr)
    {
        if (v == curr->value) return;
        stack.push_back(curr);
        if (v < curr->value)
        {
            if (curr->left == nullptr)
            {
                curr->left = n;
                break;
            }
            curr = curr->left;
        }
        else
        {
            if (curr->right == nullptr)
            {
                curr->right = n;
                break;
            }
            curr = curr->right;
        }
    }
    data_structures::rebalance_after_insert(t, stack, v, curr->value);
}

bool validate_with_height(const avl_tree_node* t, int& h)
{
    if (t == nullptr)
    {
        h = -1;
        return true;
    }
    int hl = 0, hr = 0;
    if (!validate_with_height((const avl_tree_node*)t->left, hl)) return false;
    if (!validate_with_height((const avl_tree_node*)t->right, hr)) return false;
    if (abs(hl - hr) > 1) return false;
    h = 1 + max(hl, hr);
    return true;
}

bool avl_tree::validate(const avl_tree_node *t)
{
    if (t == nullptr) return true;
    int h = -1;
    if (!data_structures::validate_with_height(t, h)) return false;
    return h == avl_tree::height(t);
}

bool avl_tree::validate_iterative(const avl_tree_node *t)
{
    if (t == nullptr) return true;
    auto q = queue<const binary_tree_node*>();
    q.push(t);
    int h = avl_tree::height(t);
    while (!q.empty())
    {
        auto sz = q.size();
        for (auto i = 0; i < sz; ++i)
        {
            auto p = (const avl_tree_node*)q.front();
            q.pop();
            if (abs(height(p) - h) > 1) return false;
            if (p->left != nullptr) q.push(p->left);
            if (p->right != nullptr) q.push(p->right);
        }
        --h;
    }
    return h == -1 && q.empty();
}

static void rebalance_after_remove(binary_tree_node*& t)
{
    if (t == nullptr) return;
    int hl = avl_tree::height((const avl_tree_node*)t->left);
    int hr = avl_tree::height((const avl_tree_node*)t->right);
    if (hl > hr + 1)
    {
        auto p = t->left;
        if (p->left == nullptr || avl_tree::height((const avl_tree_node*)p->left) < avl_tree::height((const avl_tree_node*)p->right))
            data_structures::rotate_left_right(t);
        else
            data_structures::rotate_right(t);
    }
    if (hl < hr - 1)
    {
        auto p = t->right;
        if (p->right == nullptr || avl_tree::height((const avl_tree_node*)p->right) < avl_tree::height((const avl_tree_node*)p->left))
            data_structures::rotate_right_left(t);
        else
            data_structures::rotate_left(t);
    }
    ((avl_tree_node*)t)->height = 1 + max(avl_tree::height((const avl_tree_node*)t->left), avl_tree::height((const avl_tree_node*)t->right));
}

void avl_tree::remove(binary_tree_node *&t, int v)
{
    if (t == nullptr) return;
    if (v < t->value)
        remove(t->left, v);
    else if (v > t->value)
        remove(t->right, v);
    else
    {
        if (t->left != nullptr && t->right != nullptr)
            t->value = remove_min(t->right);
        else
        {
            binary_tree_node* p = t;
            t = t->left != nullptr ? t->left : t->right;
            delete p;
        }
    }
    data_structures::rebalance_after_remove(t);
}

}
