

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void print(vector<int> &v)
{
    for(unsigned i = 0; i < v.size(); ++i){
        cout << v[i] << " ";
    }
    cout << endl;
}


int main()
{
    int ia[9] = {1, 5, 0, 2, 3, 4, 9, 8, 6};
    vector<int> v(ia, ia+9);

    cout << "v: ";
    print(v);

    make_heap(v.begin(), v.end());
    cout << "after make_heap v: ";
    print(v);


    v.push_back(7);
    cout << "after push_back v: ";
    print(v);

    push_heap(v.begin(), v.end());
    cout << "after push_heap v: ";
    print(v);



    sort_heap(v.begin(), v.end());
    cout << "after sort_heap v: ";
    print(v);



    return 0;
}

