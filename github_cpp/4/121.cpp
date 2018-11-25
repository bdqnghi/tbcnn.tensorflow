#include <iostream>

using namespace std;

void hanoi(char * source, char * destination, char * intermediate, int disks)
{
if(disks > 0)
{
 //move n - 1 discks to intermediate VIA destination
hanoi(source, intermediate, destination, disks - 1);
//now move the remaining 1 disk to destination from source
cout<<"disk "<<disks<<" moved from "<<source<<" to destination "<<destination<<endl;
//now move rest of the n - 1 disks from intermediate to destination VIA source
hanoi(intermediate, destination, source, disks - 1);
}
}
int main()
{
int disks = 0;
cout<<"enter no of disks\n";
cin>>disks;

hanoi("A", "C", "B", disks);
return 0;
}
