#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int num=0;
stack <int> s,s1,s2;
void toh(int sz,stack <int> &s, stack <int> &s1,stack <int> &s2)
{
	num++;
	/* s:2345, s1:, s2:1 */

	if(sz==1)
	{
		if(s.empty())
		{
			cout<<" caught \n";
			return;
		}
		s2.push(s.top());
		s.pop();
		return;
	}


	toh(sz-1,s,s2,s1);//1  s,s2,s1
	stack<int> st=s,st1=s1,st2=s2;
	// cout<<"\n s11 : ";
	// while(!st1.empty())
	// {
	// 	cout<<st1.top()<<' ';
	// 	st1.pop();
	// }

	// cout<<"\n s21 : ";
	// while(!st2.empty())
	// {
	// 	cout<<st2.top()<<' ';
	// 	st2.pop();
	// }
	// cout<<endl;
	s2.push(s.top());//op1
	s.pop();
	// cout<<"\n s12 : ";
	// while(!st1.empty())
	// {
	// 	cout<<st1.top()<<' ';
	// 	st1.pop();
	// }

	// cout<<"\n s22 : ";
	// while(!st2.empty())
	// {
	// 	cout<<st2.top()<<' ';
	// 	st2.pop();
	// }
	// cout<<endl;

	toh(sz-1,s1,s,s2);
	// s2.push(s1.top());
	// s1.pop();
	// stack<int> st=s,st1=s1,st2=s2;
	// cout<<" s : ";
	// while(!st.empty())
	// {
	// 	cout<<st.top()<<' ';
	// 	st.pop();
	// }
	// cout<<"\n s1 : ";
	// while(!st1.empty())
	// {
	// 	cout<<st1.top()<<' ';
	// 	st1.pop();
	// }

	// cout<<"\n s2 : ";
	// while(!st2.empty())
	// {
	// 	cout<<st2.top()<<' ';
	// 	st2.pop();
	// }
	// cout<<endl;
	

}


int main(int argc, char const *argv[])
{
	
	s.push(5);
	s.push(4);
	s.push(3);
	s.push(2);
	s.push(1);
	// s.push(6);
	// s.push(7);
	// s.push(8);
	// s.push(9);
	// s.push(10);
	
	
	

	toh(5,s,s1,s2);

	
	cout<<num<<endl;
	return 0;
}
