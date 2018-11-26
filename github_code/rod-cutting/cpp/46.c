/*
    Solving the problem of rod cutting wiht/without dynamic programming memoization. 

*/

#include <iostream>
#include <limits> 
#include <algorithm>    
using namespace std;

int rodCutting(int * prices, int rodSize){
    if(rodSize == 0) return 0;

    int m = std::numeric_limits<int>::min();
    for(int i = 1; i <= rodSize; i++) {
        m = max(m, prices[i] + rodCutting(prices, rodSize - i));
    }
    return m;
}

int rodCuttingDPAUX(int * prices, int rodSize, int * results) {
    if(rodSize == 0) 
        return prices[0];

    if(results[rodSize] != -1)
        return results[rodSize];
    
    int m = std::numeric_limits<int>::min();
    for(int i = 1; i <= rodSize; i++) 
        m = max(m, prices[i] + rodCuttingDPAUX(prices, rodSize - i, results)); 
    
    results[rodSize] = m;
    return m;
}

int rodCuttingDP(int * prices, int rodSize)
{
    int results[rodSize+1];
    for (auto &  i : results)
        i = -1;
        
    return rodCuttingDPAUX(prices, rodSize, results);
}

int main() {
    int prices[9] = {0,1,5 ,8 ,9 ,10 ,17 ,17 ,20};
    int prices2[5] = {0,1,5,8,9};
    cout << "Max revenue possible: " << rodCutting(prices, 8) << endl;
    cout << "Max revenue possible: " << rodCuttingDP(prices, 8) << endl;
    cout << "Max revenue possible: " << rodCutting(prices2, 4) << endl;
    cout << "Max revenue possible: " << rodCuttingDP(prices2, 4) << endl;
    return 0;
}