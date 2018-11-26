#include "library.h"
#include "binary_tree.h"
#include "binary_search_tree.h"
#include "b-tree.h"
#include "red-black-tree.h"
#include "digraph.h"
#include "test.h"

using namespace std;

int main() {
//    BinaryTree<int> *binary_tree = new BinaryTree<int>;
//    binary_tree->inorder(process_tree_node<int>);
    BinarySearchTree<char> *bst = new BinarySearchTree<char>;
    bst->insert('c');
    bst->insert('e');
    bst->insert('d');
    bst->insert('b');
    bst->insert('a');
    bst->insert('r');
//    bst->remove(7);
//    bst->inorder(process_tree_node<char>);
    // 获取深度
    cout << bst->depth() << endl;

    // 按层输出
    bst->print_node_by_level();

    B_Tree<char, 5> *b_tree = new B_Tree<char, 5>;
    b_tree->insert('a');
    b_tree->insert('b');
    b_tree->insert('c');
    b_tree->insert('d');
    b_tree->insert('e');
    b_tree->insert('f');
    b_tree->insert('g');
    b_tree->insert('h');
    b_tree->remove('h');

    RB_Tree<char> *rb_tree = new RB_Tree<char>;
    rb_tree->insert('c');
    rb_tree->insert('o');
    rb_tree->insert('r');
    rb_tree->insert('n');
    rb_tree->insert('f');
    rb_tree->insert('l');
    rb_tree->insert('a');
    rb_tree->insert('k');
    rb_tree->insert('e');
    rb_tree->insert('s');

    auto *solution = new Solution;
    vector<int> a;
    a.push_back(0);
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);
    for (int i : a) {
        cout << i;
    }
    solution->sortedArrayToBST(a);

//    Digraph *digraph = new Digraph();
//    digraph->read();
}