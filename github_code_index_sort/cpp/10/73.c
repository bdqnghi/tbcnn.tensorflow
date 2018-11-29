/**
 * This program uses STDIN and STDOUT. It represents Hollerith's version of Radix Sort. Instead of 
 * regular radix sort (starting from the least significant digit to the most significant digit), this sort
 * starts from the most significant digit.
 * @author Dushan Terzikj
 * @since 18.03.2018 
*/
#include <bits/stdc++.h>
using namespace std;

typedef unsigned int ui;

/**
 * This is a bucket-sort subroutine, but it is a little bit different then
 * usual bucket-sort algorithm. Since it uses exponent ex to regulate the elements
 * into buckets, when a bucket size is more than 1, it does not call any comparison sorting 
 * algorithm, but it calls bucket-sort on that bucket but with exponent ex/10. Base case is 0,
 * i.e., when all the elements in one bucket are the same elements. 
 * @param a the array to be sorted
 * @param ex the exponent
*/
void bucket_sort(vector<int>& a, int ex){

    /* If exponent is 0, then we came to a bucket with all the same elements */
    if(ex == 0){
        return;
    }

    /* Put the integers in buckets according to the digit on the current exponent */
    vector<int> b[10];
    for(ui i = 0; i < a.size(); i++){
        int idx = (a[i]/ex)%10;
        b[idx].push_back(a[i]);
    }

    /* Sort buckets individually. If the bucket size is < 1, that means
    that the bucket is currently sorted. Otherwise sort the bucket again with bucket-sort
    but with exponent ex/10 */
    for(int i = 0; i < 10; i++){
        if(b[i].size() > 1){
            bucket_sort(b[i], ex/10);
        }
    }

    /* Fill in the sorted array */
    int idx = 0;
    for(int i = 0; i < 10; i++){
        for(ui j = 0; j < b[i].size(); j++){
            a[idx++] = b[i][j];
        }
    }
}

/**
 * Holleirth's version of bucket-sort. Finds the maximum exponent ex and calls 
 * bucket-sort on the elements. First iteration sorts them according to the most significant
 * digit. If necessary, it propagates to the least significant digit (that can be seen in bucket_sort())
 * @param a the array to be sorted
*/
void radix_sort(vector<int>& a){

    int maxx = 0;
    for(ui i = 0; i < a.size(); i++){
        maxx = max(maxx, a[i]);
    }

    /* maxx = 10^ex + x, find ex */
    int ex = 1;
    while(maxx/ex > 0) ex *= 10;
    ex /= 10;

    bucket_sort(a, ex);
}

int main(){

    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    radix_sort(a);

    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}