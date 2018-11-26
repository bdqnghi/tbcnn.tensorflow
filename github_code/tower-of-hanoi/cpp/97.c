#include<stdio.h>
int main()
{
	int i,choice,num,quit=0,top=-1,number,value,j,k;
	printf("\t\t\t\t\tTower of Hanoi problem\n\n");
	printf("Enter the number of disks you want to keep\n");
	scanf("%d",&num);
	int source[num],aux[num],destination[num+3];
	for(i=0;i<num;i++)
	{
		source[i]=0;
		aux[i]=0;
	}
	for(i=0;i<num+3;i++)
	{
		destination[i]=0;
	}
	do
	{
	printf("\t\t\t\t\t\t OPTION MENU\n");
	printf("Enter 1: Theory of Tower of Hanoi problem\n");
	printf("Enter 2: Fill the source tower\n");
	printf("Enter 3: Shift n disks to destination tower\n");
	printf("Enter 4: Display all the towers\n");
	printf("Enter 5: Quit\n");
	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1: printf("Theory of Tower of Hanoi\n\n");
		printf("Some General Rules\n");
		printf("1: Only one element can be moved at a time\n");
		printf("2: At no point, A smaller element can be placed below a larger one\n");
		printf("3: Movement can be done only of TOP which implies we work on a STACK\n\n\n\n\n");
			break;
		case 2: if(top!=-1)
		{
			printf("Cannot create new stack you idiot\n");
		}
		else
		{
		printf("Enter the source tower completely\n");
		for(i=0;i<num;i++)
		{
		printf("Enter the %d element of the source stack\n",i+1);
		scanf("%d",&source[i]);
		}
		top=num-1;
		}
			printf("\n\n\n\n");
			break;
		case 3: printf("Lets shift the disks from the Source tower to destination tower\n\n");
		printf("Enter the position where you want to put your new disk\n");
			scanf("%d",&number);
			k=num-number;
			for(i=num-1,j=0;i>=number-1;i--,j++)
			{
				aux[j]=source[i];
				source[i]=0;
			}
			printf("The source stack is following\n");
			for(i=0;i<num;i++)
			{
				printf("%d element of source tower is %d\n",i+1,source[i]);
			}
			printf("The aux stack is following\n");
			for(i=0;i<num;i++)
			{
				printf("%d element of aux tower is %d\n",i+1,aux[i]);
			}
			printf("The destination stack is following\n");
			for(i=0;i<num;i++)
			{
				printf("%d element of destination tower is %d\n",i+1,destination[i]);
			}
			for(i=0;i<number;i++)
			{
				destination[i]=source[i];
				source[i]=0;
			}
			printf("\n\n\nAfter putting source elements to destination elements\n");
			printf("The source stack is following\n");
			for(i=0;i<num;i++)
			{
				printf("%d element of source tower is %d\n",i+1,source[i]);
			}
			printf("The aux stack is following\n");
			for(i=0;i<num;i++)
			{
				printf("%d element of aux tower is %d\n",i+1,aux[i]);
			}
			printf("The destination stack is following\n");
			for(i=0;i<num;i++)
			{
				printf("%d element of destination tower is %d\n",i+1,destination[i]);
			}
			printf("Enter the value of disk you want to insert\n");
			scanf("%d",&value);
			destination[number-1]=value;
			for(i=number,j=0;j<k;j++,i++)
			{
				destination[i]=aux[j];
				aux[j]=0;
			}
			printf("\n\n\n\n");
			break;
			printf("\n\n\n\n");
		case 4:
			printf("The source stack is following\n");
			for(i=0;i<num;i++)
			{
				printf("%d element of source tower is %d\n",i+1,source[i]);
			}
			printf("The aux stack is following\n");
			for(i=0;i<num;i++)
			{
				printf("%d element of aux tower is %d\n",i+1,aux[i]);
			}
			printf("The destination stack is following\n");
			i=0;
			for(i=0;i<num+3;i++)
				printf("%d element of destination tower is %d\n",i+1,destination[i]);
			
			printf("\n\n\n\n");
			break;
		case 5: quit=1;
		printf("\n\n\n\n");
			break;
		default: printf("Hey human! Even I can read better than you!\n");
	}
	}while(quit!=1);

}
