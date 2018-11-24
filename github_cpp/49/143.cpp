//gradient descent is cool so I'm using this to test out code
//I should have probably used Python here bc of matplotlib
//https://towardsdatascience.com/linear-regression-using-gradient-descent-in-10-lines-of-code-642f995339c0
/*
Constraints:
 - 2 dimension
*/
#include <bits/stdc++.h>
#define VI vector<int>
#define US (unsigned)
using namespace std;



VI x = {4,8,12,16,1,4,9,16};
VI y = {1,4,9,16,4,8,12,3};


//start with a random line
double curM = 1;
double curB = 0;
int n = 0;

double meanSquareError(){
  double totAns = 0;
  for(int i = 0; i < n;i++){ // y
    totAns += pow((curM*x[i] + curB) - y[i],2);
  }
  return totAns/n;
}

int main(){
  n = 8;
  int cycles = 1000;
  double learnRate = 0.001;
  for(int a = 1; a <=cycles;a++){
    double diffM = 0;
    double diffB = 0;
    for(int i = 0; i < n;i++){
      diffM-=x[i]*(y[i] - (curM*x[i] + curB));
    }
    for(int i = 0; i < n;i++){
      diffB-=(y[i] - (curM*x[i] + curB));
    }
    double gradientM = (diffM* 2)/n;
    double gradientB = (diffB* 2)/n;
    curM = curM - (learnRate * gradientM);
    curB = curB - (learnRate * gradientB);
  }
}
