#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

int main() {
	
	
	
	int array[5];
	cout<<"Enter 5 numbers into the array: " <<endl<<endl;
	for (int i=0; i<5; i++)
		{
			cin>>array[i];
		}
		cout<<endl;
		
		
		clock_t begin=clock();
		
		
		
		
		for (int i = 1; i < 5; i++){
		int j = i;
		
		while (j > 0 && array[j] < array[j-1]){
			  int hold = array[j];
			  array[j] = array[j-1];
			  array[j-1] = hold;
			  j--;
			  }
		}
		
		
		
		
		cout<<"The sorted array is: "<<endl<<endl;
		for (int m=0; m<5; m++)
			{
				cout<<array[m];
			}
			cout<<endl;
			
			
			
		clock_t end=clock();
		cout<<"total time is "<<double(end-begin);
		cout<<endl<<endl;
			
			system("PAUSE");
			return 0;
}

