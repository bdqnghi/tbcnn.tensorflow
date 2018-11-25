
#include <iostream>
#include <climits>

#include "sort.hpp"
#include "reddit_info.hpp"

using namespace std;

typedef vector<RedditInfo>::iterator RedditInfoPtr;


void merge(vector<RedditInfo> &A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;



                
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




    }
}



void merge_sort(vector<RedditInfo> &A, int p, int r) {
    if(p < r) {
        
        int q = (p + r)/2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

int main(int argc, const char* argv[]) {
    
    if (argc != 2) {
        cout << "Usage: sort1 example.csv" << endl;
        return 0;
    }
    
    
    vector<RedditInfo> data = import_data(argv[1]);
    cout << "Unsorted: " << endl;
    RedditInfo::print_header();
    print(data);
    
    
    merge_sort(data, 0, data.size()-1);
    
    
    cout << "Sorted: " << endl;
    RedditInfo::print_header();
    print(data);
}