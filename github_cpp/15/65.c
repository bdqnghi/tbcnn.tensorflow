#include<iostream>
using namespace std;
int main()
{
    int a[4][4],b[4][4],c[4][4],i,j,k,sum=0;
    cout<<"Enter your first matrix"<<endl;
    for(i=0;i<3;i++){
    for(j=0;j<3;j++){
    cin>>a[i][j];
    }
    }
    cout<<"Enter your seceond matrix"<<endl;
    for(i=0;i<3;i++){
    for(j=0;j<3;j++){
    cin>>b[i][j];
    }
    }
    for(i=0;i<3;i++){
    for(j=0;j<3;j++){
    for(k=0;k<3;k++){
    sum=sum+a[i][k]*b[k][j];
    }
    c[i][j]=sum;
    sum=0;
    }
    }
    cout<<"Result "<<endl;
     for(i=0;i<3;i++){
    for(j=0;j<3;j++){
    cout<<c[i][j];
    cout<<" ";
    }
    cout<<"\n";
    }
    return 0;
}
