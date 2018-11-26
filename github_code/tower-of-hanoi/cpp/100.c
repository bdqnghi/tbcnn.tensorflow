#include<iostream>
#include<stack>
using namespace std;
/*
1) Only one disk can be moved at a time.
2) Each move consists of taking the upper disk from one of the stacks and placing it on top of another stack i.e. a disk can only be moved if it is the uppermost disk on a stack.
3) No disk may be placed on top of a smaller disk.
 
 Approach :
 
 Take an example for 2 disks :
 Let rod 1 = 'A', rod 2 = 'B', rod 3 = 'C'.
 
 Step 1 : Shift first disk from 'A' to 'B'.
 Step 2 : Shift second disk from 'A' to 'C'.
 Step 3 : Shift first disk from 'B' to 'C'.
 
 The pattern here is :
 Shift 'n-1' disks from 'A' to 'B'.
 Shift last disk from 'A' to 'C'.
 Shift 'n-1' disks from 'B' to 'C'.
 P B D
 P D B
 B P D
 
 Image for illustration: http://mathforum.org/dr.math/faq/faq.disk3.gif
*/

void towerOfHanoi(stack<int> *pri, stack<int> *buff, stack<int> *dest, int n){
    if(n == 0){
        return;
    }
  
    towerOfHanoi(pri, dest, buff, n-1);
    (*dest).push((*a).top());
    (*a).pop();
    towerOfHanoi(buff, a, dest, n-1);
}

int main(){
    stack<int> primary, buffer, destination;
  
    int n = 10;
    for(int i = n; i > 0; i--)
        primary.push(i); //push numbers in first stack
  
    towerOfHanoi(&primary, &buffer, &destination, 10);
  
    while(!destination.empty()){
        cout << destination.top() << " ";
        destination.pop();
    }
}



