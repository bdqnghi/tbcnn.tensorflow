#include "segment-tree.h"

size_t tree[100] = {0};
size_t lazy[100] = {0};
int size = 10;

int main()
{
    default_random_engine generator;
    uniform_int_distribution<int> dist(1, 3);
    auto r_gen = bind(dist, generator);

    vector<int> x(size, 0);

    for (int i = 0; i < size; i++)
    {
        int g = r_gen();
        x[i] = g;
        cout << x[i] << " ";
    }
    cout << endl;

    build(x, 1, 0, size - 1);
    print_tree();

    // for (int i = 0; i < size; i++)
    // {
    //     int g = r_gen();
    //     update(0, g % size, 0, size - 1, 6);
    // }
    // print_tree();

    int s_range = 0;
    int e_range = 3;
    cout << "Target range:"
         << "[" << s_range << "," << e_range << "]" << endl;
    update(1, 0, size - 1, s_range, e_range, 3);
    print_tree();
    query(1, 0, size - 1, s_range, e_range);

    update_lazy(1, 0, size - 1, s_range, e_range, 10);
    query(1, 0, size - 1, s_range, e_range);
    return 0;
}

#ifndef ONLINE_JUDGE
void print_tree()
{
    for (int i = 0; i < 4 * size; i++)
    {
        if (tree[i] == 0)
        {
            continue;
        }
        cout << "[" << setw(3) << i << "] " << setw(4) << tree[i] << " ";
        if (i % 3 == 0)
        {
            cout << endl;
        }
    }
    cout << endl;
}
#endif

void build(vector<int> &vals, int tree_index, int l, int r)
{
    if (l == r)
    {
        tree[tree_index] = vals[l];
        return;
    }

    int mid = (l + r) / 2;

    build(vals, (tree_index * 2), l, mid);
    build(vals, (tree_index * 2) + 1, mid + 1, r);

    tree[tree_index] = sub_solve(tree[(tree_index * 2)],
                                 tree[(tree_index * 2) + 1]);
}

size_t sub_solve(size_t x, size_t y)
{
    // Do whatever
    return max(x, y);
}

/*
    Update elements in range [i,j]
*/
void update(int tree_index, int low, int high,
            int i, int j, int delta)

{

    if (low > high || low > j || high < i)
    {
        return;
    }

    if (low == high)
    {
        tree[tree_index] += delta;
        return;
    }

    int mid = (low + high) / 2;

    update((2 * tree_index), low, mid, i, j, delta);
    update((2 * tree_index) + 1, mid + 1, high, i, j, delta);

    tree[tree_index] = sub_solve(tree[(tree_index * 2)],
                                 tree[(tree_index * 2) + 1]);
}

void update_lazy(int tree_index, int a, int b,
                 int i, int j, int delta)
{
    if (lazy[tree_index])
    {
        tree[tree_index] += lazy[tree_index];

        if (a != b)
        {
            lazy[(2 * tree_index)] += lazy[tree_index];
            lazy[(2 * tree_index) + 1] += lazy[tree_index];
        }

        lazy[tree_index] = 0;
    }

    if (a > b || a > j || b < i)
    {
        return;
    }

    if (a >= i && b <= j)
    {
        cout << "update:" << a << " " << b << " old:" << tree[tree_index];
        tree[tree_index] += delta + lazy[tree_index];
        cout << " new:" << tree[tree_index] << endl;

        if (a != b)
        {
            lazy[(2 * tree_index)] += (delta + lazy[tree_index]);
            lazy[(2 * tree_index) + 1] += (delta + lazy[tree_index]);
        }
        lazy[tree_index] = 0;
        return;
    }

    int mid = (a + b) / 2;
    update_lazy((2 * tree_index), a, mid, i, j, delta);
    update_lazy((2 * tree_index) + 1, mid + 1, b, i, j, delta);

    tree[tree_index] = sub_solve(tree[(tree_index * 2)],
                                 tree[(tree_index * 2) + 1]);
}

void query(int tree_index, int a, int b, int i, int j)
{

    if (a > b || b < i || a > j)
    {
        return;
    }

    if (lazy[tree_index])
    {
        tree[tree_index] += lazy[tree_index];
        if (a != b)
        {
            lazy[(2 * tree_index)] += lazy[tree_index];
            lazy[(2 * tree_index) + 1] += lazy[tree_index];
        }
    }

    if (a == b)
    {
        tree[tree_index] += lazy[tree_index];
        cout << "[" << a << "] " << tree[tree_index] << endl;
        return;
    }

    int mid = (a + b) / 2;
    query((2 * tree_index), a, mid, i, j);
    query((2 * tree_index) + 1, mid + 1, b, i, j);
}
