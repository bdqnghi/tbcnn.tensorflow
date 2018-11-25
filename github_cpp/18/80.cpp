#include <iostream>
#include <vector>


using namespace std;
int rodCutting(int rod_length, vector<int> prices){
    vector<int> best_price(rod_length+1, 0);
    best_price[0] = 0;
    for (int i = 1; i <= rod_length; ++i){
        int maximum_price = INT8_MIN;
        for (int j = 1; j <= i; ++j){
            maximum_price = max(maximum_price, prices[j-1] + best_price[i-j]);
        }
        best_price[i] = maximum_price;
    }
    return best_price[rod_length];
}

int main() {
    cout << rodCutting(8, {1,5,8,9,10,17,17,20,24,30}) << endl; 
    cout << rodCutting(10, {1,5,8,9,10,17,17,20,24,30}) << endl; 
    return 0;
}
