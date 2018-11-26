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
 *      r[n] = max(p[n], r[1]+r[n-1], r[2]+r[n-2], ... , r[n-1]+r[1])  ----------------------(15.1)
 * 15.1 can be re-written to:      
 *      r[n] = max(p[i] + r[n-i])         for 1 <= i <= n              ----------------------(15.2)   
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
using namespace std;

// 
// TODO: how to compute revenue of rod size 15, and limits to princes given by p;
// e.g. prices in p[] only gives prices from p[0], p[1] ... p[10], no p[11], p[12], p[13 , p[14] and p[15].
// size 11, 12, 13, 14, 15 need to be further cut into size <= 10. 
// so that we can get revenue for rod size 40?
//
// Solution:
// it should be easy, size n > 10. then max revenus should be (n/10) * r[10] + r[n%10];
// solution could be printed accordingly;
//
class RodCutting {
private:
    int MemoizedCutRodAux(const vector<int>& p, vector<int>& r, size_t n);
public:
    // Top-Down way: O(2^n)
    int TopDownCutRod(const vector<int>& p, size_t n);
    // Top-Down with memoization way 
    int MemoizedCutRod(const vector<int>& p, size_t n);
    // Bottom-up: O(n^2)
    int BottomUpCutRod(const vector<int>& p, size_t n);
    // Build the optimal cutting solution
    int ExtendedBottomUpCutRod(const vector<int>& p, vector<int>& s, size_t n);
   
    void PrintCutRodSolution(const vector<int>& p, size_t n);
};

// Time Complexity is 2^n, which literally visit every possible way of cutting up the rod.
int RodCutting::TopDownCutRod(const vector<int>& p, size_t n) {
    if (n == 0) return 0;
    int q = INT_MIN;
    for (int i = 1; i <= n; i++) {
        q = max(q, p[i] + TopDownCutRod(p, n-i));  // Many repeated calling of sub ptroblems of same size; 
    }
    return q;
}
    
int RodCutting::MemoizedCutRodAux(const vector<int>& p, vector<int>& r, size_t n) {
    // if r[n] has already been computed, just return;
    if (r[n] >= 0) return r[n]; 
    int q = INT_MIN;
    if (n == 0) q = 0;
    else {
        for (int i = 1; i <= n; i++)
            q = max(q, p[i] + MemoizedCutRodAux(p, r, n-i));
    }
    r[n] = q;
    return q;
}

int RodCutting::MemoizedCutRod(const vector<int>& p, size_t n) {
    if (n == 0) return 0;
    vector<int>  r(n+1, INT_MIN);
    return  MemoizedCutRodAux(p, r, n);
}

// Bottom-up 
// r[n] = max(p[i] + r[n-i])   for 1 <= i <= n              
int RodCutting::BottomUpCutRod(const vector<int>& p, size_t n) {
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

void RodCutting::PrintCutRodSolution(const vector<int>& p, size_t n) {
    vector<int> s(n+1, 0);
    cout << "Val: " << ExtendedBottomUpCutRod(p, s, n);
    cout << ", Solution: ";
    while (n > 0) {
        cout << s[n] << ", ";
        n = n - s[n];
    }

}
// build cutting solution in s;
// s[i]: the size of first piece that doesn't need further divide;
int RodCutting::ExtendedBottomUpCutRod(const vector<int>& p, vector<int>& s, size_t n) {
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
    RodCutting rc;

    cout << "------PrintCutRodSolution--------" << endl;
# if 0
    cout << "Rod Cut 4: ";
    rc.PrintCutRodSolution(p, 4);
    cout << endl;
    cout << "Rod Cut 5: ";
    rc.PrintCutRodSolution(p, 5);
    cout << endl;
    cout << "Rod Cut 6: ";
    rc.PrintCutRodSolution(p, 6);
    cout << endl;
    cout << "Rod Cut 7: ";
    rc.PrintCutRodSolution(p, 7);
    cout << endl;
    cout << "Rod Cut 8: ";
    rc.PrintCutRodSolution(p, 8);
    cout << endl;
    cout << "Rod Cut 9: ";
    rc.PrintCutRodSolution(p, 9);
    cout << endl;
#endif
    cout << "Rod Cut 15: ";
    rc.PrintCutRodSolution(p, 15); 
    cout << endl;
    cout << "Rod Cut 40: ";
    rc.PrintCutRodSolution(p, 40); 
    cout << endl;
    cout << "Rod Cut 100: ";
    rc.PrintCutRodSolution(p, 100);
    cout << endl;
   
    cout << "------BottomUpCutRod--------" << endl;
#if 0
    cout << rc.BottomUpCutRod(p, 4) << endl;
    cout << rc.BottomUpCutRod(p, 5) << endl;
    cout << rc.BottomUpCutRod(p, 6) << endl;
    cout << rc.BottomUpCutRod(p, 7) << endl;
    cout << rc.BottomUpCutRod(p, 8) << endl;
    cout << rc.BottomUpCutRod(p, 9) << endl;
#endif
    cout << rc.BottomUpCutRod(p, 40) << endl;
    cout << rc.MemoizedCutRod(p, 100) << endl;
#if 0
    cout << "------MemoizedCutRod--------" << endl;
    cout << rc.MemoizedCutRod(p, 4) << endl;
    cout << rc.MemoizedCutRod(p, 5) << endl;
    cout << rc.MemoizedCutRod(p, 6) << endl;
    cout << rc.MemoizedCutRod(p, 7) << endl;
    cout << rc.MemoizedCutRod(p, 8) << endl;
    cout << rc.MemoizedCutRod(p, 9) << endl;
    cout << rc.MemoizedCutRod(p, 40) << endl;
    cout << rc.MemoizedCutRod(p, 100) << endl;
#endif
    return 0;
}
