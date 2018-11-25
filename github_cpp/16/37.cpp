


#include<iostream>
using namespace std;


class ShellSort{
private:
	int *pnum; 							
	int *d;								
	int max;
	int row;
public:
	void Size(int n);					
	void Delete();						
	void Value(int* value, int n);		
	void Output(int n);					
	int DValue(int n);					
	void Shellsort(int n, int numOfD);	
};




void ShellSort::Size(int n)
{
	pnum = new int[n];
	max=n;
	row=0;
}



void ShellSort::Delete()
{
	delete [] pnum;
	delete [] d;
}



void ShellSort::Value(int* value, int n)
{
	int max=sizeof(pnum)/sizeof(int);
	for(int i=0; i<n; i++)
		pnum[i]=value[i];
}



void ShellSort::Output(int n)
{
	for(int i=0; i<n; i++)
	{
		cout<<pnum[i]<<" ";
	}
	cout<<endl;
}


int ShellSort::DValue(int n) 
{
	int flag=0; 
	int max=n; 

	while(n != 1) 
	{
		n=n/2;
		flag++;
	}
	d = new int[flag]; 

	for(int i=0; i<flag; i++) 
	{
		max=max/2;
		d[i]=max; 
	}
	return flag; 
}



void ShellSort::Shellsort(int n, int numOfD)


{
	int i, j, k, m; 
	int gap,row=0;	
	long temp;

	for(m = 0; m < numOfD; m++)
	{
		gap = d[m];              
		for(k = 0; k < gap; k++) 
		{
			for(i = k; i < n-gap; i = i+gap) 
			{
				temp = pnum[i+gap];			 
				j = i;						 
				while(j >= 0 && temp <= pnum[j]) 
				{
					pnum[j+gap] = pnum[j];	
					j = j-gap;				
				}
				pnum[j+gap] = temp;			
			}
		}
		row++;								
		if( row ==1) { Output(max);}      
	}
}

int main()
{
	int numOfD = 0;				
	int aprime;					
	int x;						
	ShellSort text;				
	cin>>x;						
	for(int j=0; j<x; j++)
	{
		int flag=0;
		cin >> aprime;						

		int numOfD=text.DValue(aprime);		

		text.Size(aprime);

		int *num = new int[aprime];
		for(int i=0; i<aprime; i++)			
			cin>>num[i];

		text.Value(num,aprime);				
		text.Shellsort(aprime, numOfD);		
		text.Output(aprime);				

		text.Delete();						
		delete [] num;
	}
	return 0;
}