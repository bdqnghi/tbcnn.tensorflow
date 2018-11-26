//Incomplete

#include<iostream>
#include<stdlib.h>
using namespace std;
void toh(int n,char frompeg,char topeg,char auxpeg)
{
 if(n==1)
 {
   cout<<"Move Disk 1 from "<<frompeg<<" to "<<topeg<<"\n";
   return ;
 } 
 
 //Move n-1 top elements to auxilliary pillar
 toh(n-1,frompeg,auxpeg,topeg);
 
//Move the nth disk to the destination
cout<<"Move the "<<n<<" disk from "<<frompeg<<" to "<<topeg<<"\n";

//Move the disks from auxilliary peg to starting peg
toh(n-1,auxpeg,frompeg,topeg);
 
}
int main(int argc,char **argv)
{
 int n;
 //cout<<"Enter the number of disks\n";
 //cin>>n;
 n=atoi(argv[argc-1]);
 toh(n,'A','C','B');
return 0;
}
