//babykiss4ever
//to.be.impressive@gmail.com
//rod_cut.cpp
//rod cutting with cost
#include <iostream>

using namespace std;

int cut_rod_cost( int p[ ], const int &n ) {
    int r[ n + 1 ];
    r[0] = 0;

    for ( int i = 1; i <= n; ++i ) {
        int maxi = -1;

        for ( int j = 1; j < i ; ++j ) {
            int cost = i;//cost each cutting

            if ( maxi < p[j] + r[i - j] - cost )
                maxi = p[j] + r[i - j] - cost;
        }

        if ( maxi < p[i] )
            maxi = p[i];

        r[i] = maxi;
    }

    return r[n];
}

int main() {
    int p[11] = {0, 2, 25, 39, 42, 59, 69, 70, 89, 99, 100};
    cout << cut_rod_cost( p, 10 );
    return 0;
}


