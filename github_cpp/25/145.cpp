#include <iostream>
#include <numeric> 
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Version 1 : get next permutation, same with STL next_permutaion
//
//      Step1: from right to left, find the first one(i) smaller than its right neighbour(i1)
//      Step2: from right to i, find the rightest one(i2) larger than i
//      Step3: swap i and i2, then reverse from i1 to the last
//      Step4: check if i is first one, which means permutation ends, return
// would ignore duplicates, e.g. {1, 1, 2} -> {1, 1, 2}, {1, 2, 1}, {2, 1, 1}
bool nextPermutation(int *first, int *last) {
    if (first == last || first == last - 1)
        return false;

    int *i = last - 1;
    while (true) {
        int *i1, *i2;
        i1 = i;
        if (*--i < *i1) {
            i2 = last;
            while (*i >= *--i2);
            iter_swap(i, i2);
            reverse(i1, last);
            return true;
        }
        if (i == first) {
            reverse(first, last);
            return false;
        }
    }
}


// Version 2 : generate all permutations
//
// Solution 2.1 : dfs, generate
void dfs(vector<vector<int>>& result, vector<int>& path, vector<bool>& used, vector<int>& nums, size_t steps) {
    if (steps == nums.size()) {
        result.push_back(path);
        return;
    }
    for (int i = 0; i < (int)nums.size(); ++i) {
        if (!used[i]) {
            used[i] = true;
            path.push_back(nums[i]);
            dfs(result, path, used, nums, steps+1);
            path.pop_back();
            used[i] = false;
        }
    }
}

vector<vector<int>> permutation_dfs(vector<int> nums) {
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used(nums.size(), false);
    dfs(result, path, used, nums, 0);
    return result;
}


// Solution 2.2 : dfs, swap
void dfs(vector<vector<int>>& result, vector<int>& nums, size_t cur) {
    if (cur == nums.size()-1) {
        result.push_back(nums);
        return;
    }
    for (int i = cur; i < (int)nums.size(); ++i) {
        swap(nums[cur], nums[i]);
        dfs(result, nums, cur+1);
        swap(nums[cur], nums[i]);
    }
}

vector<vector<int>> permutation_dfs_swap(vector<int>& nums) {
    vector<vector<int>> result;
    dfs(result, nums, 0);
    return result;
}


// Version 3 : get k-th permutation, academic solution from Combinatorial - Canton Expression
// 康拓展开逆过程，中介数
// k = an*(n-1)! + an-1*(n-2)! + ... + ai*(i-1)! + ... + a2*1! + a1*0!
string get_kth_permutation(int n, int k) {
    // initialize a dictionary that stores 1, 2, ..., n
    string dict(n, '0');
    iota(dict.begin(), dict.end(), '1');

    // build up a look-up factorial table, which stores (n-1)!, (n-2)!, ..., 1!, 0!
    vector<int> fact(n, 1);
    for (int i = n-3; i >= 0; --i)
        fact[i] = fact[i+1] * (n-i-1);

    // let k be zero based
    --k;

    string res(n, '0');
    for (int i = 0; i < n; ++i) {
        int select = k / fact[i];
        k %= fact[i];
        res[i] = dict[select];
        dict.erase(dict.begin()+select);
    }
    return res;
}

int main() {
    cout << "solution 1" << endl;
    int s[] = {1, 2, 3};
    for (auto & i : s) cout << i << " ";
    cout << endl;
    while (nextPermutation(s, s+3)) {
        for (auto & i : s) cout << i << " ";
        cout << endl;
    }

    cout << "solution 2" << endl;
    vector<int> nums = {1, 2, 3};
    for (auto & v : permutation_dfs(nums)) {
        for (auto & i : v)
            cout << i << " ";
        cout << endl;
    }

    cout << "solution 3" << endl;
    for (auto & v : permutation_dfs_swap(nums)) {
        for (auto & i : v)
            cout << i << " ";
        cout << endl;
    }

    cout << "solution 4" << endl;
    cout << get_kth_permutation(8, 1000) << endl;
    return 0;
}
