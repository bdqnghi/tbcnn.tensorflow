

#include <iostream>
#include <cassert>

using namespace std;




void towers ( unsigned int discs, unsigned int from, unsigned int to )
{
    assert ( 1 <= from && from <= 3 );
    assert ( 1 <= to   && to   <= 3 );
    assert ( 0 < discs );

    
    
    

    unsigned int temp = 6 - from - to;

    
    static unsigned int steps = 0;

    if ( discs > 1 )
    {
        towers ( discs-1, from, temp );
        cout << "#" << ++steps << " " << from << " to " << to << endl;
        towers ( discs-1, temp, to );
    }
    else
        cout << "#" << ++steps << " " << from << " to " << to << endl;

    return;
}

int main ( int argc, char *argv[] )
{
    unsigned int discs = 0;

    if ( 2 == argc )
        discs = atoi(argv[1]);
    else
    {
        cout << "How many discs has your tower? ";
        cin >> discs;
    }

    
    towers ( discs, 1, 2 );

    return 0;
}
