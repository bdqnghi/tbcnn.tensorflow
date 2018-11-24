// Radix Sort , Iterative using array Implementation 
#include <iostream>
#include <math.h>
using namespace std;
int main()
{
	long int arr[100],size;
	long int ans[100]={0};


	cout<<" input how many digit number you want to sort  "<<endl;
	int ndigit;
	cin >> ndigit;

	// I/P array
	cout <<"Enter size of array : "<<endl;
	cin >> size;

	cout <<"Enter elements : "<<endl;
	for(int i=0; i<size; i++)
	{
		cin >> arr[i];
	}


	// Since number of digits = no. of passes =3
	for(int pass=1; pass<=ndigit; pass++)
	{ 
		
		for(int j=0; j<size;j++)
		{     // Picking up each element of given array
             //      index at that particular pass
			int index;
			if(pass==1){
				index = arr[j]%10;	
			} 
			if(pass==2){
				index = (arr[j]/10)%10;
			} 
			else if(pass==3){
				index = (arr[j]/100)%10;
			}

			if(ans[index*pass] != 0) // Concept similar to that of hashing function applied.
			{ 						// means space already occupied.
				int temp = index*pass;
				while(ans[temp] != 0)   // Finding an empty space.
				{  
					temp+=1;
				}
				ans[temp]=arr[j];            // Element sucessfully placed.
			}
			else{
				ans[index*pass] = arr[j];
			}
		}
		 
		

		int count = 0;
		for(int i=0;i<100; i++)
		{
			if(ans[i] !=0)
			{
				arr[count] = ans[i];
				count++;	
			} 
			ans[i]=0;        // Resetting ans[] array again to zero.
			
		}
	}

	// Output of final array
	for(int i=0; i<size;i++){
		cout <<arr[i] << " ";
	}


}
