

#include<bits/stdc++.h>
using namespace std;


int profit = 0;

void rodCuttingProblem(int* prices, int lengthOfRod,int n, int sum){

    if(lengthOfRod == 0){
        profit = max(sum,profit);
        return;
    }
    if(lengthOfRod < 0 || n<0){
        return;
    }

    
    rodCuttingProblem(prices,lengthOfRod-(n+1),n,sum+prices[n]);
    
    rodCuttingProblem(prices,lengthOfRod,n-1,sum);

}

int main(){

int prices[] = {1, 5, 8, 9, 10, 17, 17, 20};
int n = sizeof prices/sizeof prices[0];
rodCuttingProblem(prices,n,n-1,0);
cout<<"Maximum profit in cutting the rod is : "<<profit;

return 0;
}
