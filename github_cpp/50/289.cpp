#include<iostream>
using namespace std;

// a utility function that returns maximum of two numbers
int max (int a ,int b ){return (a>b) ?a: b;}

//returns the maximum value that can be put in a knapsack of capacity W
int Knapsack(int W,int wt[],int val[],int n ){

  // base case
  if (n==0 || W==0)
  return 0;
  // if weight of n th itemis more than the Knapsack capacity W,
  // then this item is not included in the optimal solution
  if (wt[n-1]>W){
    return Knapsack(W,wt,val,n-1);

  }

  //return maximum of two cases :
  //(1) nth item included
  //(2) not included
  else return max(val[n-1] + Knapsack(W-wt[n-1],wt,val,n-1), Knapsack(W,wt,val,n-1));

}

// program to implement the knapsack problem
int main(){
  int val[]={60,100,120};
  int wt[]={10,20,30};
  int W=50;
  int n sizeof(val)/sizeof(val[0]);
  cout<<Knapsack(W,wt,val,n);
  
  return 0;
}
