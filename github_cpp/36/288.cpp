/**
    COS: FDS
    b-tree.cpp
    Purpose:    Create a B-Tree implementation holding integers

    @author:    Martin Nestorov
    @version:   0.1.0 10/10/2017
*/

#include <iostream>
#include "b-tree.h"

node::node(int t, bool leaf) : t(t), is_leaf(leaf), keys(new int[2 * t - 1]), C(new node *[2 * t]), num_keys(0)
{

}

void node::traverse()
{
    int i;
    for (i = 0; i < num_keys; i++)
    {
        // If this isn't a leaf, then first go to the subtree.
        if (!is_leaf)
        {
            C[i]->traverse();
        }

        std::cout << " " << keys[i];
    }

    // Print the subtree rooted with last child
    if (!is_leaf)
    {
        C[i]->traverse();
    }
}

node *node::search(int k)
{
    int i = 0;
    while (i < num_keys && k > keys[i])
    {
        i++;
    }

    if (keys[i] == k)
    {
        return this;
    }

    if (!is_leaf)
    {
        return nullptr;
    }

    return C[i]->search(k);
}

void node::insertNonFull(int k)
{
    int i = num_keys - 1;

    if (is_leaf)
    {
        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        num_keys = num_keys + 1;
    }
    else
    {
        while (i >= 0 && keys[i] > k)
            i--;

        if (C[i + 1]->num_keys == 2 * t - 1)
        {
            splitChild(i + 1, C[i + 1]);

            // After split, the middle key of C[i] goes up and
            // C[i] is split into two.  See which of the two
            // is going to have the new key
            if (keys[i + 1] < k)
            {
                i++;
            }
        }

        C[i + 1]->insertNonFull(k);
    }
}

void node::splitChild(int i, node *y)
{
    auto *z = new node(y->t, y->is_leaf);
    z->num_keys = t - 1;

    for (int j = 0; j < t - 1; j++)
    {
        z->keys[j] = y->keys[j + t];
    }

    if (!y->is_leaf)
    {
        for (int j = 0; j < t; j++)
        {
            z->C[j] = y->C[j + t];
        }
    }

    y->num_keys = t - 1;

    for (int j = num_keys; j >= i + 1; j--)
    {
        C[j + 1] = C[j];
    }

    C[i + 1] = z;

    for (int j = num_keys - 1; j >= i; j--)
    {
        keys[j + 1] = keys[j];
    }

    keys[i] = y->keys[t - 1];

    num_keys = num_keys + 1;
}

BTree::BTree(int t) : t(t), root(nullptr)
{

}

void BTree::insert(int k)
{
    if (root == nullptr)
    {
        root = new node(t, true);
        root->keys[0] = k;
        root->num_keys = 1;
    }
    else
    {
        if (root->num_keys == 2 * t - 1)
        {
            auto *s = new node(t, false);

            // Make old root as child of new root.
            s->C[0] = root;

            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);

            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->keys[0] < k)
            {
                i++;
            }

            s->C[i]->insertNonFull(k);

            root = s;
        }
        else
        {
            root->insertNonFull(k);
        }
    }
}

void BTree::traverse()
{
    if (root != nullptr)
    {
        root->traverse();
    }
}

node *BTree::search(int k)
{
    return (root == nullptr) ? nullptr : root->search(k);
}

int main()
{
    BTree tree(3);

    int answer = 0, elem = 0;

    std::cout << "----- B-Tree Menu -----\n";

    std::cout << "1. Insert element to the tree.\n";
    std::cout << "2. Find element from the tree.\n";
    std::cout << "3. Display contents of the tree.\n";
    std::cout << "4. Quit.\n";

    do
    {
        std::cout << "\nTake action: ";
        std::cin >> answer;

        switch (answer)
        {
            case 1:
                std::cout << "Enter an element: ";
                std::cin >> elem;

                tree.insert(elem);
                break;

            case 2:
                std::cout << "Enter an element: ";
                std::cin >> elem;

                (tree.search(elem) != nullptr) ? std::cout << "Found element!" : std::cout << "Didn't find element.\n";
                break;

            case 3:
                tree.traverse();

                break;

            case 4:
                exit(0);

            default:
                continue;
        }

    } while ((bool) answer);

    return 0;
}
