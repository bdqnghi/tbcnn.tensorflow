#include<stdio.h>
#include<conio.h>
void towers(int ,char ,char ,char);

int main()
{
    int num;
    printf("enter number of discs");
    scanf("%d",&num);
    printf("\n the tower of hanoi are");
    towers(num,'A','B','C');
    getch();
    return 0;
}

 void towers(int num,char a,char b,char c)
 {
      if(num==1)
      {
        printf("\n %c,%c,%c",a,b,c);
        return;
        }
       else
       { 
        
        towers(num-1,a,c,b);
        towers(num-1,c,b,a);
        }
        
        }        
