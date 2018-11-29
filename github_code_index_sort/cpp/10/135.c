#include <iostream>
#include <vector>

using namespace std;
 
void InsertSort(vector<int> &R)
{
	int tmp,j,n=R.size();
	for (int i=1;i<n;i++)
	{
		tmp=R[i];
		j=i-1;
		while (j>=0 && tmp<R[j])
		{
			R[j+1]=R[j];
			j--;
		}
		R[j+1]=tmp;
	}
}


void BUCKETSORT(int A[],int n,int k)
{
	int m=10;
	int i,j,count;
	vector<vector<int> > v(k+1);
	for (i=0;i<n;i++)//·ÖÍ° 
		for (j=1;j<=k+1;j++)
			if (A[i]<=m*j/k)
			{ 
				v[j-1].push_back(A[i]);
				break;
			}
	for (count=0;count<=k;count++)
		InsertSort(v[count]);
	for (count=0;count<k;count++)
		{
			cout<<"bucket"<<count+1<<':';
			for (int t=0;t<v[count].size();t++)
				cout<<v[count][t]<<' ';
			cout<<endl;
		}
	i=0;
	while (i<n)
	{
		for (j=0;j<=k;j++)
		 for (count=0;count<v[j].size();count++)
		    {
		    	A[i]=v[j][count];
		    	i++;
		    }
			
	}
}

void test()
{
	int a[50]={7,7,7,7,7,
				2,2,2,2,2,
				9,9,9,9,9,
				4,4,4,4,4,
				5,5,5,5,5,
				8,8,8,8,8,
				1,1,1,1,1,
				6,6,6,6,6,
				3,3,3,3,3,
				10,10,10,10,10};
	for (int j=5;j!=1;j--)
	{
		cout<<"k="<<j<<endl;
		BUCKETSORT(a,50,j);
		cout<<"result:"<<endl;
	for (int i=0;i<sizeof(a)/sizeof(a[0]);i++)
		cout<<a[i]<<"\t";
		cout<<endl; 
	}	
}


int main()
{
	test();
	return 0;
}
