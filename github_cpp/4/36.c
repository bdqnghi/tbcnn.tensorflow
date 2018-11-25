
#include<stdio.h>

using namespace std;




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
