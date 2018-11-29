/* ----------------------------------------------------------------------------
 * Copyright &copy; 2016 Ben Blazak <bblazak@fullerton.edu>
 * Released under the [MIT License] (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */

/**
 * A demonstration of selection sort and merge sort.
 *
 * From assignment-04
 */

#include <iostream>
#include <vector>

using std::cout;
using std::endl;

using std::vector;

// ----------------------------------------------------------------------------

void print_vector(const vector<int> & v) {
    for (int e : v)
        cout << e << " ";
    cout << endl;
}

// ----------------------------------------------------------------------------

// SECTION BEGIN selection-sort
void selection_sort(vector<int> & v) {
    // for the index of each element in the array (the "current index")
    for ( vector<int>::iterator first_unsorted = v.begin();
          first_unsorted != v.end();
          first_unsorted++ ) {

        // find the index of the minimum element at or after the current index
        vector<int>::iterator min = first_unsorted;

        for ( vector<int>::iterator first_uncompared = first_unsorted;
              first_uncompared != v.end();
              first_uncompared++ ) {

            if ( *min > *first_uncompared )
                min = first_uncompared;
        }

        // swap the element at the current index with the smallest element
        // found
        int temp = *first_unsorted;
        *first_unsorted = *min;
        *min = temp;
    }
}
// SECTION END selection-sort

vector<int> merge_sort(const vector<int> & v) {
    // base case
    if (v.size() < 2)
        return v;

    // split
    vector<int> left{ v.begin(), v.begin()+v.size()/2 };
    vector<int> right{ v.begin()+v.size()/2, v.end() };

    // recursively sort each side
    left = merge_sort(left);
    right = merge_sort(right);

    // merge
    vector<int> sorted;
    vector<int>::iterator l = left.begin();
    vector<int>::iterator r = right.begin();
    while( l != left.end() && r != right.end() )
        if (*l < *r)
            sorted.push_back(*(l++));
        else
            sorted.push_back(*(r++));
    while( l != left.end() )
        sorted.push_back(*(l++));
    while( r != right.end() )
        sorted.push_back(*(r++));

    return sorted;
}

// ----------------------------------------------------------------------------

int main() {
    vector<int> vectors[] = {
       vector<int>{ 1, 2, 3, 4, 5, 6, 7, },
       vector<int>{ 22, 1, 63, 67, 11, 17, 12, },
       vector<int>{ 45, 53, 64, 7, 25, 79, 54, },
       vector<int>{ 34, 21, 35, 84, 16, 10, 36, },
       vector<int>{ 41, 2, 85, 94, 69, 9, 92, },
    };

    for (vector<int> & v : vectors) {
        {
            print_vector(v);

            vector<int>temp = v;
            selection_sort(temp);
            print_vector(temp);
        }

        print_vector(v);
        print_vector(merge_sort(v));

        cout << endl;
    }

    return 0;
}

