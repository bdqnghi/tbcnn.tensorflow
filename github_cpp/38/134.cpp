#include<stdio.h>
void EnQueue();
void DeQueue();
void Display();

#define size 5
int queue[size];
int front=-1;
int rear=-1;


int main()
{
	int choice;
	int n;
	printf("\n\tQUEUE SIZE : 5\n\n");
	while(1)
	{
		
		printf("\n\n\t*************************************");
		printf("\n\t\t\tMENU\n");
		printf("\n\t  1) Insert elements in queue ");
		printf("\n\t  2) Delete elements in queue ");
		printf("\n\t  3) Display all elements of queue ");
		printf("\n\t  4) Exit  ");
		printf("\n\nt*************************************");
		printf("\n\n Enter your choice : ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
					
					EnQueue();
					break;
			case 2: 
					DeQueue();
					break;
			case 3:
					Display();
					break;
			case 4:
					return 0;
			default : printf("\nwrong choice");
					break;
		}
	}
}
void EnQueue()
{
	int value;
	if(rear==size-1)
	{
		printf("\n Queue is full");
	}
	else
	{
		if(front==-1)
			front=0;
		printf("\n\n Enter the element : ");
		scanf("%d",&value);	
		rear = rear+1;
		queue[rear] = value;
		printf("\n Insertion successful");
		
	
	}
}
void DeQueue()
{
	if(front==-1)
	{
		printf("\n Queue is empty");
		
	}
	else
	{
		printf("\n %d is deleted ", queue[front]);
		if(front==rear)
		{
			front=rear=-1;
		}
		else
		{
			front++;
		}
		
	}
}
void Display()
{
	if(rear==-1)
	{
		printf("\n Queue is empty");
	}
	else
	{
		printf("\n Queue elements are : \n");
		printf("___________________________________\n ");
		for(int i=front; i<=rear; i++)
		{
			printf("%d	", queue[i]);
		}
		printf("\n___________________________________\n");
	}
}
