//Rod-cutting puzzle
#include <bits/stdc++.h>
using namespace std;

int rodcut(int rods[], int cost[],int size, int n){
    int table[size+1][n+1];
    for(int i = 0;i<=size;i++){
        for(int j = 0;j<=n;j++){
            if(i==0 || j ==0){
                table[i][j] = 0;
                continue;
            }
                
            if(j<i)
                table[i][j] = table[i-1][j];
            else
                table[i][j] = max(table[i-1][j], table[i][j-i]+cost[i-1]);
        }
    }
    //Uncomment to print the table
    /*for(int i=0;i<=size;i++){
        for(int j = 0; j<=n;j++){
            cout<<table[i][j]<<" ";
        }
        cout<<endl;
    }*/
    int i,j;
    j = n,i  = size;
    
    while(j!=0){
        while(table[i-1][j] == table[i][j]){
            i--;        
        }
        cout<<rods[i-1]<<" ";
        j-=i;
    }
    cout<<endl;
    return table[size][n];
}

int main(){
    int rods[4] = {1,2,3,4};
    int cost[4] = {2,5,7,8};
    int size = 4;
    int req = 5;
    cout<<rodcut(rods,cost,size,req)<<endl;
    return 0;
}
