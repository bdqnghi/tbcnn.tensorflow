

#include <string>
#include <iostream>
#include <vector>
#include <cmath>
 
using namespace std;

int min(int x,int y,int z){
	return x<((y<z)?y:z)?x:((y<z)?y:z);
}

int edit(vector< vector<int> > &table, string input1,string input2){
		
		for(int k=0;k<=input2.length();k++)
				table[0][k]=k;
		for(int k=0;k<=input1.length();k++)
				table[k][0]=k;	
		for(int k=1;k<=input1.length();k++){
			for(int r=1;r<=input2.length();r++){
				
				
				if(input1.at(k-1)==input2.at(r-1))
						table[k][r]=table[k-1][r-1];
				else
						
						
						
						table[k][r]=min(table[k][r-1],table[k-1][r-1],table[k-1][r])+1;
			}
		}
		return table[input1.length()][input2.length()];
}

int main(){
	string input1,input2;
	cin>>input1>>input2;
	vector< vector<int> > table(input1.size()+1, vector<int>(input2.length()+1,0));
	int editDistance = edit(table,input1,input2);
	cout<<"Min Edit Distance: "<<editDistance<<endl;
	
	int r=input2.length();
	int c=input1.length();
 	if(editDistance==1){
 		 if(1==table[r-1][c-1]+1){
			cout<<"replace"<<endl;
		}
		else if(1==table[r-1][c]+1){
			cout<<"delete"<<endl;
 		}
		else if(1==table[r][c-1]+1){
			cout<<"insertion"<<endl;
  	}
  }
 	else{
		while(c!=0 && r!=0){
			if(input1[c-1]==input2[r-1]){
				c--;
				r--;
			}
			else if(table[r][c]==table[r-1][c-1]+1){
				cout<<"replace"<<endl;
				c--;
				r--;
			}
			else if(table[r][c]==table[r-1][c]+1){
				cout<<"delete"<<endl;
				r--;
			}
			else if(table[r][c]==table[r][c-1]+1){
				cout<<"insertion"<<endl;
				c--;
			}
		}
	}	
}
