/*************************************************************************
    > File Name: edit_distance.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Sat 01 Oct 2016 12:28:15 PM SGT
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;

/*
 * solution here: http://www.cs.jhu.edu/~langmea/resources/lecture_notes/dp_and_edit_dist.pdf
 *
 * D[i, j]: edit distance between length-i pre"x of x and length-j prefix of y
 * In order to change x to y, optimal transcript for D[i, j] can be built
 * by extending a shorter one by 1 operation. Only 3 options: 
 * Append Deletion to transcript for D[i-1, j]
 * Append Insertion to transcript for D[i-1, j]
 * Append Match or Replacement to transcript for D[i-1, j-1]
*/

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
