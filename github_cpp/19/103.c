#include <iostream>
#include <cstdlib>
using namespace std;

void quicksort(int *start,int *end)
{
	if(start >= end )
		return;

	int t = *start;
	int *s = start, *e = end-1 ;
	while(s < e)
	{
		while(s < e && t <= *e )
			e --;
		*s = *e ;
		while(s < e && t >= *s)
			s ++;
		*e = *s;
	}
	
	*s = t;

	quicksort(start,s);
	quicksort(s+1,end);
};

void test1(){
	int a[] = {1,4,2,6,7,10,0};
	quicksort(a,a+7);
	for(int i:a)
		cout << i << ' ';
	cout << endl;
}

void test2(){
	int num = 1000*1000*10;
	int *p = new int[num];
	for(int i=0;i<num;i++)
		p[i] = rand();

	quicksort(p,p+num);

	for(int i=0;i<num-1;i++){
		if(p[i] > p[i+1])
			cout << "error orcer" << endl;
	}
	cout << "over" << endl;
}

int main(){
	test1();
	test2();
};
