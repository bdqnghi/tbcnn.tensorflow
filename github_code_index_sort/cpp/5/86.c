#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

int main() {
	
	//declare the array
	
	int array[5];
	cout<<"Enter 5 numbers into the array: " <<endl<<endl;
	for (int i=0; i<5; i++)
		{
			cin>>array[i];
		}
		cout<<endl;
		
		//Begin clock
		clock_t begin=clock();
		
		//Bubble sort
		
	int hold;
	for (int j=0; j<=4; j++)
		{
			for (int k=0; k<4; k++)
				{
					if(array[k]>array[k+1])
					{
						hold=array[k];
						array[k]=array[k+1];
						array[k+1]=hold;
					}
				}
		}
		
		//Displaying results of the bubble sort
		
		cout<<"The sorted array is: "<<endl<<endl;
		for (int m=0; m<5; m++)
			{
				cout<<array[m];
			}
			cout<<endl;
			
			//End clock
			
		clock_t end=clock();
		cout<<"total time is "<<double(end-begin);
		cout<<endl<<endl;
			
			system("PAUSE");
			return 0;
}
