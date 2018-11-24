#include<iostream>
#include<math.h>
using namespace std;
int isPalin(int n)
{int is=1;
  int copyn=n;
  int i=0;int sum=0,rem=0;
  while(copyn>0)
  {
      rem=copyn%10;
      sum=sum*10+rem;
      copyn=copyn/10;
      i++;
  }

  if(sum!=n)
    is=0;

return is;
}
int main()
{
  int x,y;
 int i,j;
for(i=700;i<1000;i++)
  {
    for(j=700;j<1000;j++)
     { x=i*j;

      if(isPalin(x))
        {
            cout<<x;
            y=x;
        }

     }
}
cout<<y;
return 0;
}
