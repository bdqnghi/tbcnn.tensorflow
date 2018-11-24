
// knuth-morris-pratt ( KMP ) string matching algorithm
//preprocess pattern - find in text

#include<iostream>
#include<vector>
using namespace std;

#define N 100005

vector<int> back_table;

void kmp_preprocess(string pattern){
	back_table.clear();
	int i=0,j=-1;
	back_table.push_back(-1);
	while(i<pattern.size()){
		while(j>=0 && pattern[i]!=pattern[j]){
			j=back_table[j];
		}
		i++;
		j++;
		back_table.push_back(j);
	}
}

void kmp_search(string text,string pattern){
	int i=0,j=0;
	while(i<text.size()){
		while(j>=0 && text[i]!=pattern[j]){
			j=back_table[j];
		}
		i++;
		j++;
		if(j==pattern.size()){
			cout<<"found at index "<<i-j<<endl;
			j=back_table[j];
		}
	}
}

int main(){
	kmp_preprocess("hello");
	kmp_search("who is saying hello to me??","hello");
	kmp_search("hi, hello, hey, hello","hello");
}
