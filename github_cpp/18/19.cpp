#include "Steel_Strip_Cutting.h"
#include<limits>
#include<stdio.h>
#include<algorithm>

int Steel_Strip_Cutting::Memoized_Cut_Rod(vector<int> &p, int n) {

	vector<int> r(n+1,0);  
	for (int i = 0;i <= n;++i) {
		r[i]=INT_MIN;
	}
	return Steel_Strip_Cutting::Memoized_Cut_Rod_Aux(p,n,r);
}

int Steel_Strip_Cutting::Memoized_Cut_Rod_Aux(vector<int> &p, int n, vector<int> &r) {
	
	if (r[n] >= 0) {
		return r[n]; 
	}
	int q=0;
	if (n == 0);
	else {
		q=INT_MIN;
		for (int i = 1;i <= n;++i) {
			q=max(q,Steel_Strip_Cutting::Memoized_Cut_Rod_Aux(p,n-i,r)+p[i]);
		}
	}
	r[n]=q;
	return q; 
}

int Steel_Strip_Cutting::Bottom_Up_Cut_Rod(vector<int> &p, int n) {

	vector<int> r(n+1,0);
	for (int j = 1;j <= n;++j) {
		int q=INT_MIN;
		for (int i = 1;i <= j;++i) {
			q=max(q,p[i]+p[j-i]);
		}
		r[j]=q;
	}
	return r[n]; 
}

Steel_Strip_Cutting::Steel_Strip_Cutting()
{

	init();
}

void Steel_Strip_Cutting::init()
{
	int num1, num2;
	printf( "����������۸������Ӧ���и\n");
	while (cin >> num1 >> num2) {
		p.push_back(num1);
		val.push_back(num2);
	}
	cout << "��������Ҫ�и�ĸ������ȣ�\n";
	cin >> n;
}
