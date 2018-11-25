#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MAXE 20			
#define MAXR 10			
#define MAXD 8			
typedef struct node
{	
	char data[MAXD];	
    struct node *next;
} RecType;
void CreaLink(RecType *&p,char *a[],int n);
void DispLink(RecType *p);
void RadixSort(RecType *&p,int r,int d) 
{
	RecType *head[MAXR],*tail[MAXR],*t;	
	int i,j,k;
	for (i=0;i<=d-1;i++)           		
	{	
		for (j=0;j<r;j++) 				
			head[j]=tail[j]=NULL;
		while (p!=NULL)          		
		{	
			k=p->data[i]-'0';   		
			if (head[k]==NULL)   		
			{
				head[k]=p;
				tail[k]=p;
			}
          	else
			{
              	tail[k]->next=p;
				tail[k]=p;
			}
            p=p->next;             		
		}
		p=NULL;							
       	for (j=0;j<r;j++)        		
        	if (head[j]!=NULL)         	
			{	
				if (p==NULL)
				{
					p=head[j];
					t=tail[j];
				}
				else
				{
					t->next=head[j];
					t=tail[j];
				}
			}
		t->next=NULL;					
		printf("  按%s位排序\t",(i==0?"个":"十"));
		DispLink(p);
	}
}
void CreateLink(RecType *&p,char a[MAXE][MAXD],int n)	
{
	int i;
	RecType *s,*t;
	for (i=0;i<n;i++)
	{
		s=(RecType *)malloc(sizeof(RecType));
		strcpy(s->data,a[i]);
		if (i==0)
		{
			p=s;t=s;
		}
		else
		{
			t->next=s;t=s;
		}
	}
	t->next=NULL;
}
void DispLink(RecType *p)	
{
	while (p!=NULL)
	{
		printf("%c%c ",p->data[1],p->data[0]);
		p=p->next;
	}
	printf("\n");
}
int main(){
	int n=10,r=10,d=2;
	int i,j,k;
	RecType *p;
	char a[MAXE][MAXD];
	int b[]={75,23,98,44,57,12,29,64,38,82};
	for (i=0;i<n;i++)		
	{
		k=b[i];
		for (j=0;j<d;j++)	
		{
			a[i][j]=k%10+'0';
			k=k/10;
		}
		a[i][j]='\0';
	}
	CreateLink(p,a,n);
	printf("\n");
	printf("  初始关键字\t");		
	DispLink(p);
	RadixSort(p,10,2);
	printf("  最终结果\t");			
	DispLink(p);
	printf("\n");
return 0;
}