
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

	
	cout <<"Enter size of array : "<<endl;
	cin >> size;

	cout <<"Enter elements : "<<endl;
	for(int i=0; i<size; i++)
	{
		cin >> arr[i];
	}


	
	for(int pass=1; pass<=ndigit; pass++)
	{ 
		
		for(int j=0; j<size;j++)
		{     
             
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

			if(ans[index*pass] != 0) 
			{ 						
				int temp = index*pass;
				while(ans[temp] != 0)   
				{  
					temp+=1;
				}
				ans[temp]=arr[j];            
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
			ans[i]=0;        
			
		}
	}

	
	for(int i=0; i<size;i++){
		cout <<arr[i] << " ";
	}


}
