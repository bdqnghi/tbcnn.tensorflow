



#include <iostream>
#include <vector>

using std::cout;
using std::endl;

using std::vector;



void print_vector(const vector<int> & v) {
    for (int e : v)
        cout << e << " ";
    cout << endl;
}




void selection_sort(vector<int> & v) {
    
    for ( vector<int>::iterator first_unsorted = v.begin();
          first_unsorted != v.end();
          first_unsorted++ ) {

        
        vector<int>::iterator min = first_unsorted;

        for ( vector<int>::iterator first_uncompared = first_unsorted;
              first_uncompared != v.end();
              first_uncompared++ ) {

            if ( *min > *first_uncompared )
                min = first_uncompared;
        }

        
        
        int temp = *first_unsorted;
        *first_unsorted = *min;
        *min = temp;
    }
}


vector<int> merge_sort(const vector<int> & v) {
    
    if (v.size() < 2)
        return v;

    
    vector<int> left{ v.begin(), v.begin()+v.size()/2 };
    vector<int> right{ v.begin()+v.size()/2, v.end() };

    
    left = merge_sort(left);
    right = merge_sort(right);

    
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

