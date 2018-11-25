/* 

EXPLANATION:: 

Take the example of 2. Firstly you will move the 1st block to auxillary, then 2nd to destination and then auxillary one to destination.

Now with more than 2, like take the all above the last as 1 block(doesnt it leave you with 2 blocks only).
so again with this the first block(the combination) move to auxillary, the last to destination and then auxilary to destination..


1. So with this the first move to auxilalry (means for this destination is auxillary and aux- destination)

2. the print what happened, source last has moved to destination that move written 

3. Now the first block(combination) which we moved to auxuilary in 1, for that now source will be that only (i.e auxiallry) and aux is source.. 


*/

void towerOfHanoi(int n, char source, char auxiliary, char destination) {
    // Write your code here
  
  if(n==0)
    return ;
	towerOfHanoi(n-1, source, destination, auxiliary);
  
  cout<< source <<" "<< destination<<endl;
  
  towerOfHanoi(n-1, auxiliary, source, destination);
 
}

