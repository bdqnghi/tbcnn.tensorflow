#include<iostream>

#include<stack>
using namespace std;









stack<pair<int,int> > Stack[3];











void Tower_of_Hanoi(int  A ,int B,int  C,int N)
{	
	if(N==0)
		return;

	Tower_of_Hanoi(A,C,B,N-1);          

	pair<int,int> curr_disk = Stack[A].top();  
	int sz=curr_disk.first;				
	int number=curr_disk.second;		
	Stack[A].pop(); 							
	Stack[C].push(curr_disk);
	cout<<"Transferred Disk : Size "<<sz<<" and Number "<<number<<" from Stack "<<A<<" to "<<C<<endl;
	Tower_of_Hanoi(B,A,C,N-1);

}

int main()
{
	
	int N;

	

	cout<<"Enter the number of disks \n";
	cin>>N;
	cout<<"Enter the size of the disks \n"; 
	cout<<"Note they must be in descending order \n \n"; 
	for(int i=N;i>=1;i--)
	{
		int sz;
		cin>>sz;
		Stack[0].push(make_pair(sz,i));
		cout<<"Disk : Size "<<sz<<" and Number "<<i<<" pushed into the Source Stack \n";
	}

	

	cout<<" \n    Tower of Hanoi    \n";
	cout<<" ----------------------------- \n \n";
	Tower_of_Hanoi(0,1,2,N);

	return 0;
}
