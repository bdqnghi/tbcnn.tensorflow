#include <iostream>
#include <vector>

using namespace::std;

int max(int a,int b){
    return a >= b ? a : b;
}

int memoizedRodCuttingAUX(vector<int> price,int number,vector<int> &reminder) {
    if(reminder[number] >= 0)
        return reminder[number];
    int q;
    if (number == 0)
        q = 0;
    else {
        q = -1;
        for(int i = 1; i <= number; i++)
            q = max(q, price[i] + memoizedRodCuttingAUX(price,number - i,reminder));
    }
    reminder[number] = q;
    return q;
}

int memoizedRodCutting(vector<int> price,int number) {
    vector<int> reminder = vector<int>(price.size());
    for(int i = 0; i<reminder.size(); i++)
        reminder[i] = -1;
    return memoizedRodCuttingAUX(price,number,reminder);
}

int bottomUpRodCutting(vector<int> price, int number) {
    vector<int> reminder = vector<int>(price.size());
    reminder[0] = 0;
    for(int j = 1; j <= number; j++){
        int q = -1;
        for(int i = 1; i <= j; i++) {
            q = max(q,price[i] + price[j - i]);
        }
        reminder[j] = q;
    }
    return reminder[number];
}

int main(){
    vector<int> price = {0,1,5,8,9,10,17,17,20,24,30};
    cout<<memoizedRodCutting(price,8)<<endl;
    cout<<bottomUpRodCutting(price,8)<<endl;
}