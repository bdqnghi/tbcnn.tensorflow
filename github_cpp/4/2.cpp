#include<iostream>
using namespace std;

/*ALGORITHM

START
Procedure Hanoi(disk, source_tower, dest_tower, aux_tower)

   IF disk == 0, THEN
      move disk from source to dest             
   ELSE
      Hanoi(disk - 1, source_tower, aux_tower, dest_tower)     // Step 1
      move disk from source to dest          // Step 2
      Hanoi(disk - 1, aux_tower, dest_tower, source_tower)     // Step 3
   END IF
   
END Procedure
STOP
*/

void TowerOfHanoi(int n,char source_tower,char dest_tower,char aux_tower)
{
	
	if(n==1)
	{
		cout<<endl<<"Move "<<n<<" from "<<source_tower<<" to "<<dest_tower;
		return;
	}
	else
	{
		
		TowerOfHanoi(n-1,source_tower,aux_tower,dest_tower); //Recursive Call
        
        
		cout<<endl<<"Move "<<n<<" from "<<source_tower<<" to "<<dest_tower;
		
		
		TowerOfHanoi(n-1,aux_tower,dest_tower,source_tower);  //Recursive Call
	}


};

int main()
{
	int n;
	cout<<"enter number of disk";
	cin>>n;
	TowerOfHanoi(n,'A','C','B');

	return 0;
}

/*
Compile:
g++ 2.TowerofHanoi.cpp
Output:
enter number of disk 3

Move 1 from A to C
Move 2 from A to B
Move 1 from C to B
Move 3 from A to C
Move 1 from B to A
Move 2 from B to C
Move 1 from A to C
*/
