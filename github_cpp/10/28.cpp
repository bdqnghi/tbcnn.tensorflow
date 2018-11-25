

#include<iostream>
#include<string>
using namespace std;



int EditDistanceRecursive(const string &x, int i, const string &y, int j){
    if(i==0) return j;
    if(j==0) return i;

    int diag = EditDistanceRecursive(x, i-1, y, j-1) + (x[i]!=y[j]?1:0);
    int vert = EditDistanceRecursive(x, i-1, y, j)+1;

    int horz = EditDistanceRecursive(x, i, y, j-1)+1;

    return min(diag, min(vert, horz));
}

int main(){

    string x = "TEST-STRINGS";
    string y = "TEST*STRING";
    cout<<"Minimum Edit Distance is:"<<EditDistanceRecursive(x, x.length(), y, y.length())<<endl;
    return 0;
}
