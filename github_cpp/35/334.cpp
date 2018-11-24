#include "common.h"

// Singly Linked List

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// Doubly Linked List

#ifdef P_0426
#ifndef NODE
#define NODE

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node() {}
    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

#endif
#endif

namespace linked_list
{

ListNode* construct(const vector<int>& v) {
    ListNode dum(0), *p = &dum;
    for (auto& i : v) p = p->next = new ListNode(i);
    return dum.next;
}

ListNode* constructCircular(const vector<int>& v) {
    ListNode dum(0), *p = &dum;
    for (auto& i : v) p = p->next = new ListNode(i);
    p->next = dum.next; // connect
    return dum.next;
}

ListNode* tail(ListNode* l) {
    for (; l && l->next; l = l->next);
    return l;
}

bool equal(ListNode* l1, ListNode* l2) {
    for (; l1 && l2; l1 = l1->next, l2 = l2->next)
        if (l1->val != l2->val) return false;
    if (l1 || l2) return false;
    return true;
}

#ifdef P_0426

Node* constructDoubly(const vector<int>& v) {
    Node dum(0, nullptr, nullptr), *p = &dum;
    for (auto& i : v) p = p->right = new Node(i, p, nullptr);
    p = dum.right;
    if (p) p->left = nullptr;
    return p;
}

bool equal(Node* l1, Node* l2) {
    for (; l1 && l2; l1 = l1->right, l2 = l2->right)
        if (l1->val != l2->val) return false;
    if (l1 || l2) return false;
    return true;
}

#endif

}
