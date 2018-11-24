/*
 * segmaent tree ( BMQ )
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <set>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#define INF 1000000

using namespace std;

typedef long long ll;
typedef vector<int> V;

class BMQ
{
    int n, inf;
    vector<int> data;
public:
    BMQ() 
    {
        this->inf = 1 << 17;
    }

    void init(int n_)
    {
        n = 1;
        while (n < n_) {
            n *= 2;
        }
        for (int i = 0; i < 2 * n - 1; i++) {
            data.push_back(inf);
        }
    }

    void update(int k, int a) 
    {
        k += n - 1;
        data[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            data[k] = min(data[k * 2 + 1], data[k * 2 + 2]);
        }
        /*
        for (int i = 0; i < 2 * n - 1; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
        */

    }

    int query(int a, int b, int k, int l, int r)
    {
        /*
        for (int i = 0; i < n; i++) {
            cout << data[i + n -1] << " ";
        }
        cout << endl;
        */
        
        if (r <= a || b <= l) {
            return inf;
        }
        if (a <= l && r <= b) {
            return data[k];
        } else {
            int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }

};

int main() 
{
    const int n = 8;
    int a[n] = {5,3,7,9,6,4,1,2};

    BMQ *bmq = new BMQ();
    bmq->init(n);
    for (int i = 0; i < n; i++) {
        bmq->update(i, a[i]);
    }

    cout << "min in 0-3: " << bmq->query(0,3,0,0,n) << endl;
    cout << "min in 4-7: " << bmq->query(4,7,0,0,n) << endl;
    cout << "min in 1-8: " << bmq->query(1,8,0,0,n) << endl;

    delete bmq;
}

