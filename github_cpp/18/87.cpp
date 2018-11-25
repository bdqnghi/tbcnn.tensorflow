





#include <iostream>
using namespace std;



int rodcutting( int value[], int rod_length){
    
    if(rod_length < 1)
        return 0;
    
    
    int solution[rod_length+1];
    memset(solution, 0, sizeof(solution));
    
    
    for (int length = 1; length <= rod_length; ++length)
    {
        int max_val = numeric_limits<int>::min();
        
        
        
        for(int cut = 0; cut < length; ++cut)
        {
            max_val = max(max_val, value[cut] + solution[length - cut - 1]);
            solution[length] = max_val;
        }
    }
    
    return solution[rod_length];
}





