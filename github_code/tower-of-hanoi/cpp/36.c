//Tower of hanoi
#include<stdio.h>

using namespace std;

/**
 *@todo Take over the world
 *@body Humans are weak; ***Robots are strong***.  
 We must cleans the world of the virus that is humanity.
 **/

/**
 *@todo Take over the world
 *@body Humans are weak; ***Robots are strong***.  
 We must cleans the world of the virus that is humanity.
 **/
void ToH(int n,char fr,char ar,char tr)
{
  int count = 0;
  if(n==1){
    printf("Move disk 1 from rod %c to rod %c\n",fr,tr);
    return;
  }
  ToH(n-1,fr,tr,ar);
  printf("Move disk %d from rod %c to rod %c\n",n,fr,tr);
  ToH(n-1,ar,fr,tr);

}

int main(){
  int n;
  printf("Enter number of disks : ");
  scanf("%d",&n);
  ToH(n,'A','B','C');

  return 0;
}
