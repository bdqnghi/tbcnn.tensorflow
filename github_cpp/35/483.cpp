#include <iostream>
#include <memory>
using namespace std;

template <typename T> struct ListNode {
    enum class TraverseOrder {PRE, POS};
    T data;
    shared_ptr<ListNode<T>> next;
};

template <typename Key = int, typename List = shared_ptr<ListNode<Key>>>
void linked_list_traverse(List list, typename ListNode<Key>::TraverseOrder order = ListNode<Key>::TraverseOrder::PRE)
{
    if (list == nullptr) return;

    if (order == ListNode<Key>::TraverseOrder::PRE) cout << list->data << " ";
    linked_list_traverse(list->next, order);
    if (order == ListNode<Key>::TraverseOrder::POS) cout << list->data << " ";
}

template <typename Key = int, typename List = shared_ptr<ListNode<Key>>>
List linked_list_search(List list, Key key)
{
    while (list && list->data != key) {
        list = list->next;
    }
    return list;
}

int main()
{
    using LNI = ListNode<int>;
    auto L =
        make_shared<LNI>(LNI{1,
            make_shared<LNI>(LNI{2,
                make_shared<LNI>(LNI{3,
                    make_shared<LNI>(LNI{4,
                        nullptr})})})});

    cout << linked_list_search(L, 3) << endl;
    cout << L->next->next->next << endl;

    cout << "PRE: ";
    linked_list_traverse(L, LNI::TraverseOrder::PRE);
    cout << endl;

    cout << "POS: ";
    linked_list_traverse(L, LNI::TraverseOrder::POS);
    cout << endl;
}

