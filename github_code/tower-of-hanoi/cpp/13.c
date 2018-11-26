#include<iostream>
using namespace std;

int pow(int a, int b){
    //base
    if(b==0){
        return 1;
    }
    //reccurssive
    else{
    int ans= a*pow(a,b-1);
    return ans;
    }
}

int stepcalculator(int n){
    return pow(2,n)-1;
}

void toh(int n, char source[], char helper[], char destination[]){
    //base
    if(n==1){
         cout<<"Move "<<n<<"th disc from "<<source<<" to "<<destination<<endl;
        return;
    }

    //recurrsive
    toh(n-1,source,destination,helper);
    cout<<"Move "<<n<<"th disk from "<<source<<" to "<<destination<<endl;
    toh(n-1, helper, source, destination);

}

int main(){
    int n;
    cin>>n;
    toh(n,"T1","T3","T2");
    cout<<stepcalculator(n);
}