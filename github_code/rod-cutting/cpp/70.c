/*
 * Problem:
 * Enterprises buys long steel rods and cuts them into short rods, which it then sells.
 * Each cut is free. The management of the enterprise wants to know the best way to cut 
 * up the rods.
 *
 * Assume we know for i = 1, 2, ..., the price p[i] in dollars that enterprise charges
 * for a rod of length i inches. Rod lengths are always an integral number of inches.
 *
 * Given a rod of length n inches and a table of prices p[i] for i = 1, 2, ... n, determine
 * the maximum revenue r[n] obtainable by cutting up the rod and selling the pieces.
 *
 * Example:
 * length i   |  1   2   3   4   5   6   7   8   9   10
 * ------------------------------------------------------
 * price p[i] |  1   5   8   9   10  17  17  20  24  30
 * 
 * We can cut up a rod of length n in 2^(n-1) different ways, since we have an independent
 * option of cutting, or not cutting, at distance i inches from the left end, for i = 1, 2, 
 * ... n-1.
 *
 * More generally, we can frame the values r[n] for n >= 1 in terms of optimal revenues from
 * shorter rods:
 *      r[n] = max(p[n], r[1]+r[n-1], r[2]+r[n-2], ... , r[n-1]+r[1])  --------------(15.1)
 * 15.1 can be re-written to:      
 *      r[n] = max(p[i] + r[n-i])         for 1 <= i <= n              --------------(15.2)
 *
 * r[1]: p[1]
 * r[2]: p[1]+r[1], p[2]
 * r[3]: p[1]+r[2], p[2]+r[1], p[3]
 *       p[3], r[1]+r[2], r[2]+r[1]
 *
 * This is because we can easily make an assertion:
 * ....There must be some value i (1<=i<=n), that makes the optimal solution of r[n], that left 
 * half is of size i, right half is n-i. And left half can not be further divided, which is p[i];
 * ....This assertion can be easily proved: if p[i] is not the optimal value for size i, then 
 * it means that the left half can be further divided, then we keep dividing until we get a left 
 * half that can'be divided further. 
 * ....This way we deduce the solution to rely on one subproblem (r[n-i]), instead of two as is in 15.1.
 * */

#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
using namespace std;

class RodCutting {
public:
    RodCutting(vector<int>& xp) { p = xp; t = p.size()-1;}
    // Top-Down way: O(2^n)
    int TopDownCutRod(size_t n);
    // Top-Down with memoization way 
    int MemoizedCutRod(size_t n);
    // Bottom-up: O(n^2)
    int BottomUpCutRod(size_t n);
    // Build the optimal cutting solution
    int ExtendedBottomUpCutRod(vector<int>& s, size_t n);
    void PrintCutRodSolution(size_t n);
private:
    int MemoizedCutRodAux(vector<int>& r, size_t n);
    int BottomUpCutRodAux(size_t n);
private:
    vector<int>   p;
    size_t        t;  // size of the maximum length that have the price, size larger than t will be cut to n/t and n%t;
};

// Time Complexity is 2^n, which literally visit every possible way of cutting up the rod.
int RodCutting::TopDownCutRod(size_t n) {
    if (n > t) { 
        cout << "Not supported for size: " << n << "larger than " << t << endl;
        cout << "Pls call BottomUpCutRodAux instead."<< endl;
        return -1;
    }
    if (n == 0) return 0;
    int q = INT_MIN;
    for (int i = 1; i <= n; i++) {
        q = max(q, p[i] + TopDownCutRod(n-i));  // Many repeated calling of sub ptroblems of same size; 
    }
    return q;
}
    
int RodCutting::MemoizedCutRodAux(vector<int>& r, size_t n) {
    // if r[n] has already been computed, just return;
    if (r[n] >= 0) return r[n]; 
    int q = INT_MIN;
    if (n == 0) q = 0;
    else {
        for (int i = 1; i <= n; i++)
            q = max(q, p[i] + MemoizedCutRodAux(r, n-i));
    }
    r[n] = q;
    return q;
}

int RodCutting::MemoizedCutRod(size_t n) {
    if (n > t) { 
        cout << "Not supported for size: " << n << "larger than " << t << endl;
        cout << "Pls call BottomUpCutRodAux instead."<< endl;
        return -1;
    }
    if (n == 0) return 0;
    vector<int>  r(n+1, INT_MIN);
    return  MemoizedCutRodAux(r, n);
}

// n must be <= t;
int RodCutting::BottomUpCutRodAux(size_t n) {
    vector<int> r(n+1, INT_MIN);
    r[0] = 0;
    for (int i = 1; i <= n; i++) {
        // compute r[i]
        for (int j = 1; j <= i; j++) {
            r[i] = max(r[i], p[j]+r[i-j]);
        }
    }
    return r[n];
}
// Bottom-up 
// r[n] = max(p[i] + r[n-i])   for 1 <= i <= n              
int RodCutting::BottomUpCutRod(size_t n) {
    if (n <= t)
        return BottomUpCutRodAux(n);
    else
        return (n/t)*BottomUpCutRodAux(t) + BottomUpCutRodAux(n%t);;
}

void RodCutting::PrintCutRodSolution(size_t n) {
    vector<int> s;
    if (n > t) {
        vector<int> s1(t+1, 0);
        s.resize(n%t+1, 0);
        cout << "Revenue: " << setw(5) << (n/t)*ExtendedBottomUpCutRod(s1, t) + ExtendedBottomUpCutRod(s, n%t);
        cout << ", Solution: ";
        for (int i = 0, k = t; i < n/t; i++, k = t) {
            while (k > 0) {
                cout << s1[k] << ", ";
                k = k - s1[k];
            }
        }
        n = n%t;
    } else {
        s.resize(n+1, 0);
        cout << "Revenue: " << setw(5) << ExtendedBottomUpCutRod(s, n);
        cout << ", Solution: ";
    }
    while (n > 0) {
        cout << s[n] << ", ";
        n = n - s[n];
    }
}

// build cutting solution in s;
// s[i]: the size of first/left piece that doesn't need further divide;
int RodCutting::ExtendedBottomUpCutRod(vector<int>& s, size_t n) {
    vector<int> r(n+1, INT_MIN);
    r[0] = 0;
    for (int i = 1; i <= n; i++) {
        // compute r[i]
        int q = INT_MIN;
        for (int j = 1; j <= i; j++) {
            // r[i] = max(p[j]+r[i-j]) for 1 <= j <= i
            if (q < (p[j] + r[i-j])) {
                q = p[j] + r[i-j];
                s[i] = j;
            }
        }
        r[i] = q;
    }
    return r[n];
}

int main() {
    vector<int> p = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    RodCutting rc(p);

    cout << "------PrintCutRodSolution--------" << endl;
    for (int i = 0; i <= 30; i++) {
        cout << "Rod Cut " << setw(3) << i << ": ";
        rc.PrintCutRodSolution(i);
        cout << endl;
    }

    cout << "------BottomUpCutRod--------" << endl;
    for (int i = 0; i <= 30; i++) {
        cout << "Rod Cut " << setw(3) << i << ": ";
        cout << rc.BottomUpCutRod(i) << endl;
    }

    cout << "------MemoizedCutRod--------" << endl;
    for (int i = 0; i <= 10; i++) {
        cout << "Rod Cut " << setw(3) << i << ": ";
        cout << rc.MemoizedCutRod(i) << endl;
    }
    return 0;
}
