/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:     RodCutting.cpp
* @version:
* @Time:          2015-12-29 08:50:54
* @Description:  CLRS 15
*
+----------------------------------------------------------
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#pragma warning(disable:4996)
using namespace std;

void init(vector<int> &price) {
    int temp;

    while (cin >> temp) {
        price.push_back(temp);
    }
}
void print(vector<int> &path, int n) {
    if (n > 0) {
        cout << path[n - 1] << (path[n - 1] < n ? "->" : "\n");
        print(path, n - path[n - 1]);
    }
}
int cutRod(vector<int> &price, int n, vector<int> &path) {
    if (n == 0) {
        return 0;
    }

    int maxProfit = INT_MIN;

    for (int i = 0; i < n; ++i) {
        int temp = price[i] + cutRod(price, n - i - 1, path);

        if (temp > maxProfit) {
            maxProfit = temp;
            path[n - 1] = i + 1;
        }
    }

    return maxProfit;
}
int cutRod(vector<int> &price) {
    int n = price.size();
    vector<int> path(n);
    int result = cutRod(price, n, path);
    print(path, path.size());
    return result;
}
int memorizedCutRod(vector<int> &price, int n, vector<int> &r) {
    if (r[n] >= 0) {//r[n] is the result of length n(n=0,1,2,....price.size())
        return r[n];
    }

    int maxProfit;

    if (n == 0) {
        maxProfit = 0;
    } else {
        maxProfit = INT_MIN;

        for (int i = 0; i < n; ++i) {
            int temp = price[i] + memorizedCutRod(price, n - 1 - i, r);

            if (temp > maxProfit) {
                maxProfit = temp;
            }
        }
    }

    return r[n] = maxProfit;
}
int memorizedCutRod(vector <int> &price) {
    vector<int> r(price.size() + 1, INT_MIN);
    return memorizedCutRod(price, price.size(), r);
}
int bottomUpCutRod(vector<int> &price) {
    //price[i] is the i+1 th rod's price, r[j] is the result of length j
    int n = price.size();
    vector<int> r(n + 1, INT_MIN);
    r[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j)
            if (price[j] + r[i - j - 1] > r[i]) {
                r[i] = price[j] + r[i - j - 1];
            }
    }

    return r[n];
}

int main() {
    #pragma region START_CODE
#ifdef ONLINE_JUDGE
#else
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    #pragma endregion
    vector<int> price;
    init(price);
    cout << cutRod(price) << endl;
    cout << memorizedCutRod(price) << endl;
    cout << bottomUpCutRod(price) << endl;
    #pragma region END_CODE
#ifdef ONLINE_JUDGE
#else
    cout << endl;
    system("pause");
#endif
    return 0;
    #pragma endregion
}


