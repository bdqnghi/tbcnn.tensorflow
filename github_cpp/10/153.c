/*

 * EditDistance.cpp
 *
 *  Created on: Aug 11, 2015
 *      Author: user

#include<iostream>
#include<cstring>
using namespace std;
void editDistance(char X[],char Y[],int m,int n){
	int edit[m+1][n+1];
	int delcost,inscost,samecost;
	//Initialize table
	for(int i=0;i<=m;i++){
		for(int j=0;j<=n;j++){
			edit[i][j]=-1;
		}
	}
	for(int i=0;i<=m;i++){
		edit[i][0]=i;
	}
	for(int j=0;j<=n;j++){
			edit[0][j]=j;
	}

	for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				delcost=edit[i-1][j]+1;
				inscost=edit[i][j-1]+1;
				samecost=edit[i-1][j-1];
				samecost+=(X[i-1]!=Y[j-1]);
				edit[i][j]=min(delcost,min(inscost,samecost));
			}
		}
	cout<<"Minimum no. of edits are "<<edit[m][n]<<endl;
	//Printing edit distance table
	for(int i=0;i<=m;i++){
				for(int j=0;j<=n;j++){
					cout<<edit[i][j]<<" ";
				}
				cout<<endl;
	}
}

int main(){
	char X[]="SUNDAY";
	char Y[]="SATURDAY";
	editDistance(X,Y,strlen(X),strlen(Y));
}

*/
