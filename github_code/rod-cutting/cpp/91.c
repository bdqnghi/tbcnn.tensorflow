#include<iostream>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<cmath>
#include<fstream>
#include<cstring>
using namespace std;

#define in(a,low,high) for(int i=0;i<high;i++)cin>>a[i]
#define out(a,low,high) for(int i = low;i<high;i++)cout<<a[i]<<" "

int gcd(int a,int b) // Euclid's Algorithm
{ int t;
  while(b != 0){t = b;
                b = a%b;//b works as remainder
                a = t;}
  return a;
}

int lcm(int a,int b)
{
  return (a*b)/gcd(a,b);
}

int Memory_cut_rod(int*,int );
int Memorized_top_down(int*,int ,int*,int*);

int main()
{
  int n;
  cin>>n;
  int p[n+1];
  in(p,0,n+1);
  
 int x = Memory_cut_rod(p,n);
 
 cout<<"Optimal Price: "<<x<<endl;
 
 /*
 cout<<"Optimal Price using Memorized_bottom_up_dp : "<<Memorized_bottom_up(p,n)<<endl;
 Print_bottom_up(p,n);
 */ 

  system("pause");
  return 0;
}

int Memory_cut_rod(int*p,int n){
                         int r[n+1],s[n+1];
                         r[0] = 0;
                         s[0]=0;
                         for(int i=1;i<n+1;i++)
                         r[i] = -1;
                        int x = Memorized_top_down(p,n,r,s);
                        cout<<"Cuts: ";
                        for(int i=0;i<n+1;i++) cout<<s[i]<<" ";
                        cout<<endl;
                        return x;
}

int Memorized_top_down(int*p,int n,int*r,int*s)
{ if(r[n]!=-1)
  return r[n];
  
  int q = p[n];
  s[n]=0;
  for(int i=1;i<n+1;i++){
          if(q < p[i]+Memorized_top_down(p,n-i,r,s)){
               q = p[i]+Memorized_top_down(p,n-i,r,s);
               s[n]=i;
               }
  }
  r[n] = q;
  
  return q;
}
               

                                                   
  
