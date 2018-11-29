/* Merge Sort 
 * 
 */
#include <iostream>
#include <climits>

#include "sort.hpp"
#include "reddit_info.hpp"

using namespace std;

typedef vector<RedditInfo>::iterator RedditInfoPtr;

/**
 * Merge(A, p, q, r)
 *     n1 = q - p + 1
 *     n2 = r - q
 *     let L[1.. n1 + 1] and R[1..n2 + 1] be new arrays
 *     for i = 1 to n1
 *         L[i] = A[p + i - 1]
 *     for j = 1 to n2
 *         R[j] = A[q + j]
 *     L[n1 + 1] = infinity
 *     R[n2 + 1] = infinity
 *     i = 1
 *     j = 1
 *     for k = p to r
 *         if L[i] <= R[j]
 *             A[k] = L[i]
 *             i = i + 1
 *         else A[k] = R[j]
 *             j = j + 1
 * 
 */
void merge(vector<RedditInfo> &A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
//    for(vector<RedditInfo>::iterator it = A.begin(); it != A.end(); it++)
//        cout << (*it).total_votes << ' ';
//    cout << " -> " << endl;
                
    vector<RedditInfo> L(A.begin() + p, A.begin() + p + n1);
    vector<RedditInfo> R(A.begin() + q + 1, A.begin() + q + 1 + n2);
    
    RedditInfo inf1;
    inf1.total_votes = INT_MAX;
    L.push_back(inf1);
    
    RedditInfo inf2;
    inf2.total_votes = INT_MAX;
    R.push_back(inf2);
    
    int i = 0;
    int j = 0;
    for(int k = p; k <= r ; k++) {
        if(L[i] <= R[j]) {
            iter_swap(A.begin() + k, L.begin() + i);
            i++;
        }
        else {
            iter_swap(A.begin() + k, R.begin() + j);
            j++;
        }
//        cout << "  ";
//        for(vector<RedditInfo>::iterator it = A.begin(); it != A.end(); it++)
//            cout << (*it).total_votes << ' ';
//            cout << endl;
    }
}

/**
 * Merge-Sort(A, p, r)
 *     if p < r
 *         q = [(p + r)/2]
 *         Merge-Sort(A, p, q)
 *         Merge-Sort(A, q + 1, r)
 *         Merge(A, p, q, r)
 */

void merge_sort(vector<RedditInfo> &A, int p, int r) {
    if(p < r) {
        //cout << "MergeSort " << p << " " << r << endl;
        int q = (p + r)/2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

int main(int argc, const char* argv[]) {
    // Command Line Arguments
    if (argc != 2) {
        cout << "Usage: sort1 example.csv" << endl;
        return 0;
    }
    
    // Imports the data
    vector<RedditInfo> data = import_data(argv[1]);
    cout << "Unsorted: " << endl;
    RedditInfo::print_header();
    print(data);
    
    // Does Insertion Sort
    merge_sort(data, 0, data.size()-1);
    
    // Prints the data
    cout << "Sorted: " << endl;
    RedditInfo::print_header();
    print(data);
}