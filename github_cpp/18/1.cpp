#include <iostream>
#include <vector>
#include <algorithm>



using std::cout;
using std::endl;


int CutRod(const std::vector<int> &p, const int &n)
{
    if (n == 0)
    {
        return 0;
    }

    int q = INT8_MIN;

    for (auto i = 1; i <= n; ++i)
    {
        q = std::max(q, p.at(i) + CutRod(p, n - i));
    }

    return q;
}


int MemoizedCutRodAux(const std::vector<int> &p, const int &n, std::vector<int> &r)
{
    if (r.at(n) >= 0)
    {
        return r.at(n);
    }

    int q = 0;
    if (n == 0)
    {}
    else
    {
        q = INT8_MIN;
        for (auto i = 1; i <= n; ++i)
        {
            q = std::max(q, p.at(i) + MemoizedCutRodAux(p, n - i, r));
        }
    }

    r.at(n) = q;

    return q;
}

int MemoizedCutRod(const std::vector<int> &p, const int &n)
{
    std::vector<int> r(n + 1, INT8_MIN);
    return MemoizedCutRodAux(p, n, r);
}


int BottomUpCutRod(const std::vector<int> &p, const int &n)
{
    std::vector<int> r{0};
    for (auto j = 1; j <= n; ++j)
    {
        int q = INT8_MIN;
        for (auto i = 1; i <= j; ++i)
        {
            q = std::max(q, p.at(i) + r.at(j - i));
        }
        r.push_back(q);
    }
    return r.at(n);
}

int main()
{
    vector<int> p{0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

#ifdef DEBUG
    cout << "When n = 1, r = " << MemoizedCutRod(p, 1) << "." << endl; 
    cout << "When n = 2, r = " << MemoizedCutRod(p, 2) << "." << endl; 
    cout << "When n = 3, r = " << MemoizedCutRod(p, 3) << "." << endl; 
    cout << "When n = 4, r = " << MemoizedCutRod(p, 4) << "." << endl; 
    cout << "When n = 5, r = " << MemoizedCutRod(p, 5) << "." << endl; 
    cout << "When n = 6, r = " << MemoizedCutRod(p, 6) << "." << endl; 
    cout << "When n = 7, r = " << MemoizedCutRod(p, 7) << "." << endl; 
    cout << "When n = 8, r = " << MemoizedCutRod(p, 8) << "." << endl; 
    cout << "When n = 9, r = " << MemoizedCutRod(p, 9) << "." << endl; 
    cout << "When n = 10, r = " << MemoizedCutRod(p, 10) << "." << endl; 
#endif

    cout << "When n = 9, r = " << MemoizedCutRod(p, 9) << "." << endl; 

    return 0;
}