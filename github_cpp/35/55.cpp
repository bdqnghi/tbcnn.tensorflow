#include "common.h"

// Singly Linked List

class ListNode {
public:
    int val;
    ListNode *next;
    ListNode(int val) {
       this->val = val;
       this->next = NULL;
    }
};

// Doubly Linked List

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

}
