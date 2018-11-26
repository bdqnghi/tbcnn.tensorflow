//
//  rodcutting.cpp
//  codeninja_xcode
//


#include <iostream>
using namespace std;

//maximum-sum rod cutting
// returns the maximum value of cut rods, for a rod of a given lenght and the value for each cuts
int rodcutting( int value[], int rod_length){
    //base case, rod length is 0
    if(rod_length < 1)
        return 0;
    
    // solution[i] stores the max value for rod of length [i]
    int solution[rod_length+1];
    memset(solution, 0, sizeof(solution));
    
    // iterate through the length of the rod
    for (int length = 1; length <= rod_length; ++length)
    {
        int max_val = numeric_limits<int>::min();
        // for a length of the rod
        // make a cut, aywhere from 0 to length and calculate
        // the maximum value for each cuts
        for(int cut = 0; cut < length; ++cut)
        {
            max_val = max(max_val, value[cut] + solution[length - cut - 1]);
            solution[length] = max_val;
        }
    }
    //return the solution
    return solution[rod_length];
}



//maximum product rod-cutting
// a variation over above problem, find the maximum product in place of sum
