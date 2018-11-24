#include<iostream>
using namespace std;

int maxProfit(int lengths[], int prices[], int size, int rod, int *memo){
//Function that returns the max profit

  if(rod<=0) return memo[0]=0;

  if(memo[rod]) return memo[rod]; //if we have already computed the price we'll return

  int res = -1;
  for(int i=0;i<size;i++){
    int newLength = rod - lengths[i];
    if(newLength >=0){
      //If we can cut the rod, we will cut the rod
      int ans = prices[i] + maxProfit(lengths,prices,size,newLength,memo);
      res = max(ans,res);
    }
  }
  memo[rod] = res;
  return res;
}

int main(){
  int l[]={1,2,3,4,5,6,7,8};
  int p[]={1,5,8,9,10,17,17,20};
  int n;
  cin>>n;
  int *memo = new int[n+1]();

  cout<<maxProfit(l,p,8,n,memo);

}
