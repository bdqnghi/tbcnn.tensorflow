#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int p1[100],p2[100],p3[100],top1=0,top2=0,top3=0;

 void pushp1(int a)
{
	if(a!=0)
	p1[top1++]=a;
}

int popp1(void)
{
	if(top1==0)
		return 0;
	else
		return p1[--top1];
}

void displayp1(void)
{
	int i;
	printf("\nTower 1 ->> ");
	if(top1==0)
		printf("Empty");
	else
	for(i=0;i<top1;i++)
	{
		printf("%d ",p1[i]);
	}
	printf("\n");
}

void pushp2(int a)
{
	if(a!=0)
	p2[top2++]=a;
}
int popp2(void)
{
	if(top2==0)
		return 0;
	else
		return p2[--top2];
}

void displayp2(void)
{
	int i;
	printf("Tower 2->> ");
	if(top2==0)
		printf("Empty");
	else
	for(i=0;i<top2;i++)
	{
		printf("%d ",p2[i]);
	}
	printf("\n");
}

void pushp3(int a)
{
	if(a!=0)
	p3[top3++]=a;
}
int popp3(void)
{
	if(top3==0)
		return 0;
	else
		return p3[--top3];
}

void displayp3(void)
{
	int i;
	printf("Tower 3 ->> ");
	if(top3==0)
		printf("Empty");
	else
	for(i=0;i<top3;i++)
	{
		printf("%d ",p3[i]);
	}
	printf("\n");
}

int main()
{
	int n,i,x,a,b;
	printf("\nEnter the no. of Disks: ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
	    pushp1(n-i);
	}
	x=pow(2,n)-1;
	displayp1();
	displayp2();
	displayp3();
	for(i=1;i<=x;i++)
	{
		if(i%3==1)
		{
	    	a=popp1();
	 	    b=popp3();
		    if(a==0)
			{
				pushp1(b);
			}
			else if(b==0)
			{
			    pushp3(a);
			}
			else if(a>b)
			{
				pushp1(a);
				pushp1(b);
			}
			else
			{
				pushp3(b);
				pushp3(a);
			}
			displayp1();
			displayp2();
			displayp3();
			continue;
		}
        else if(i%3==2)
		{
		a=popp1();
		b=popp2();
		if(a==0)
        {
            pushp1(b);
        }
        else if(b==0)
        pushp2(a);
        else if(a>b)
        {
            pushp1(a);
            pushp1(b);
        }
        else
        {
            pushp2(b);
            pushp2(a);
        }
        displayp1();
        displayp2();
        displayp3();
        continue;
    }
    else if(i%3==0)
    {
		a=popp2();
		b=popp3();
		if(a==0)
        {
            pushp2(b);
        }
        else if(b==0)
            pushp3(a);
        else if(a>b)
        {
            pushp2(a);
            pushp2(b);
        }
        else
        {
            pushp3(b);
            pushp3(a);
        }
        displayp1();
        displayp2();
        displayp3();
        continue;
    }
  }
  printf("\nCompleted\nFinal Position\n");
  displayp1();
  displayp2();
  displayp3();
  return 0;
}
