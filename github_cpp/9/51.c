









#include <iostream>
#include <string>
using namespace std;






int main()
{
	string reverseThis;	
	int check = 1;		
	char left, right;	

	while(check == 1)
	{
		cout << "\nPlease enter a string to be reversed:\n";
		getline(cin, reverseThis);		

		

		cout << "Your string is:\n" << reverseThis << endl;

		int start = 0;				
		int end = reverseThis.length() - 1;	

		for(int count = 0; count < (reverseThis.length() / 2); count++)
		{
			left = reverseThis[start];	
			right = reverseThis[end];	

			
			reverseThis[start] = right;
			reverseThis[end] = left;

			start++;	
			end--;		
		}

		cout << "Your string has been reversed:\n" << reverseThis << endl << endl;

		
		cout << "If you want to continue please enter 1: ";
		cin >> check;
	}
	return 0;
}
