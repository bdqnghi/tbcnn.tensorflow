//print permutations of abcd
#include<iostream>
#include<stack>
#define N 5
using namespace std;
int ct=0;
void permutation(char *s,char *stk,int *used,int level)
{
 if(level==N){
 	cout<<stk<<' ';
 	(ct+1)%10?' ':cout<<endl;
 	ct++;
 	return;}
 for (int i=0;i<N;i++){
 	if(used[i])
 		continue;
 	stk[level]=s[i];
 	used[i]=1;	
 	permutation(s,stk,used,level+1);
 	used[i]=0;//key to the solution
 	}
}

void perm2(char *s,stack<char> stk,int tag,int level){
	if(level==N){
		while(!stk.empty()){
			cout<<stk.top();
			stk.pop();
		}
		cout<<" ";
		(ct+1)%10?' ':cout<<endl;
		ct++;
		return;
	}
	for(int i=0;i<N;i++){
		if((1<<(s[i]-'a'))&tag){
			if((1<<i)&tag);	//the bit has been used before
			else level++;	//the bit has not been used, but has duplicated symbol.
			continue;
		}
			
		int local_tag=tag;
		stack<char> local_stk=stk;
		tag|=(1<<(s[i]-'a'));
		stk.push(s[i]);
		perm2(s,stk,tag,level+1);
		tag=local_tag;
		stk=local_stk;
		
	}
}

int main()
{
 char *s=new char[N];
 int *used=new int[N];
 char *stk=new char[N];
 for(int i=0;i<N;i++){
 	s[i]=char('a'+i);
 	used[i]=0;
 	}
 s[3]='c';
 cout<<endl<<s<<endl;
 permutation(s,stk,used,0);
 cout<<endl<<ct<<endl;
 stack<char> k;
 int tag=0;ct=0;
 perm2(s,k,0,0);
 
}
