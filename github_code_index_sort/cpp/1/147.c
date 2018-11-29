#include<bits/stdc++.h>

using namespace std;

void read()
{
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);

}

int main(){

    //read();
    int a[100000];
    int temp,count=0;
    int t;
    cin>>t;
    for(int cc = 0;cc<t;cc++){
      int n;
      cin>>n;
      count =0;
    for(int i=0;i<n;i++)
        cin>>a[i];

    for(int j=1;j<n;j++){
       temp=a[j];
       int i=j-1;
       while(i>=0&&a[i]>temp){
        a[i+1]=a[i];
        a[i]=temp;
        i--;
        count++;
       }

    }
    
    cout<<count<<endl;
  }


    return 0;
}
