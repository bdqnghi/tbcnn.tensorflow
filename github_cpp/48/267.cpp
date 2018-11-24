#include <bits/stdc++.h>
using namespace std;

int case1(string s,int N){

	for (int i = 0; i < N; ++i)
	{
		if (s[i])
		{
			/* code */
		}
	}



}

void call(){

	string s;
	cin >> s;

	int i=0;

	while(s[i]!='\0'){

		i++;
	}

	int N=i,mid=N/2;

	if (N==1)
	{
		cout << s<< endl;
		return;
	}

	if (case1(s,N)==1)
	{
		cout << '1';

		for (int i = 1; i < N-1 ; ++i)
			cout << '0';
		

		cout << '1' << endl;

		return;		
	}
	else if (case2()==1)
	{
		
	}
	else{

	}

	// char new1[N];

	// for (int i = 0; i < N; ++i)
	// {
	// 	new1[i]='0';
	// }

	// int l,r;
	// int flag=0;

	// // for (int i = 0; i <= mid; ++i)
	// // {
	// // 	l=s[i]-'0';
	// // 	r=s[N-1-i]-'0';

	// // 	if (l==r)
	// // 	{
	// // 		new1[i]=s[i];
	// // 		new1[N-1-i]=s[N-1-i];
			
	// // 		cout <<"first" << endl;
	// // 		continue;
	// // 	}
	// // 	else if (l > r)
	// // 	{
	// // 		new1[i]=s[i];
	// // 		new1[N-1-i]=s[i];
			
	// // 		cout <<"second" << endl;

	// // 	}
	// // 	else
	// // 	{
	// // 		new1[i]=s[i]+1;
	// // 		new1[N-1-i]=s[i]+1;

	// // 		cout <<"third" << endl;
	// // 	}

	// // 	flag=1;
	// // }

	// // if (flag==0)
	// // {
	// // 	new1[s[mid]-'0']=new1[s[N-1-mid]-'0']=s[mid]+1;
	// // }

	// int carry=0,change=0;

	// for (int i = N-1; i > mid ; --i)
	// {
	// 	r=s[i]-'0';
	// 	l=s[N-1-i]-'0';

	// 	if (l==r)
	// 	{
	// 		new1[i]=s[i];
	// 		new1[N-1-i]=s[N-1-i];

	// 		if (carry==1)
	// 		{
				
	// 		}

	// 		carry=0;

	// 		continue;			
	// 	}
	// 	else if (l > r)
	// 	{
	// 		new1[i]=s[N-1-i];
	// 		new1[N-1-i]=s[N-1-i];

	// 		carry=0;
	// 	}
	// 	else
	// 	{



	// 	}

	// 	change=1;
	// }


	// for (int i = 0; i < N; ++i)
	// {
	// 	cout << new1[i];
	// }

	// cout << endl;

	// return;
}

int main(){

	int t;
	cin >> t;

	for (int i = 0; i < t; ++i)
	{
		call();
	}

	return 0;
}