#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<string.h>
#include<windows.h>

double t[6];
char str1[531441][17];
char L[531441][17];
char R[531441][17];

int cmp(char a[],char b[])
{
	int i,j,k;
	i=strlen(a);
	j=strlen(b);
	if(i>j)
	return 0;
	else if(i<j)
	return 1;
	else
	{
		for(k = 0;k < i;k++)
		{
			if(a[k]<b[k])
			return 1;
			if(a[k]>b[k])
			return 0;
		}
		return 1;
		
	}
}

void Merge(char a[][17], long int p, long int q, long int r)  
{
	long int n1,n2,i,j,k;
	n1 = q-p+1;
	n2 = r-q;
	
	for(i = 0;i <n1;i++)
	strcpy(L[i],a[p+i]);
	for(j = 0;j <n2;j++)
	strcpy(R[j],a[q+j+1]);
	strcpy(L[n1],"zzzzzzzzzzzzzzzz");
	strcpy(R[n2],"zzzzzzzzzzzzzzzz");
	i =0; j= 0;
	for(k = p;k<=r;k++)
	{
		if(cmp(L[i],R[j]))  
		{
			strcpy(a[k],L[i]);
			i++;
		}
		else
		{
			strcpy(a[k] ,R[j]);
			j++;
		}	
	}	
}

void MergeSort(char a[][17], long int p, long int r)   
{
	
    if(r - p< 1)
        return ;

    long int q;
    q = p + (r - p)/2;
    MergeSort(a,p,q);
    MergeSort(a,q+1,r);
    Merge(a,p,q,r);
}

void sort(char a[][17],int m)
{
	long int n;
	n = pow(3,m);
	 LARGE_INTEGER t1,t2,tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
	MergeSort(a,0,n-1);
	
	QueryPerformanceCounter(&t2);
    FILE *fp;  
	switch (m){
		case 2:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\merge-sort\\result_2.txt", "wb")) == NULL) exit(0);
		  t[0] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart;   break;
		case 4:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\merge-sort\\result_4.txt", "wb")) == NULL)  exit(0);
		 t[1] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart; break;
		case 6:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\merge-sort\\result_6.txt", "wb")) == NULL)  exit(0);
		 t[2] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart;  break;
		case 8:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\merge-sort\\result_8.txt", "wb")) == NULL)  exit(0); 
		 t[3] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart; break;
		case 10:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\merge-sort\\result_10.txt", "wb")) == NULL)  exit(0);
		 t[4] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart;  break;
		case 12:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\merge-sort\\result_12.txt", "wb")) == NULL)  exit(0); 
		 t[5] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart; break;
		default:break;
	
}

	for(long int i = 0;i < n; i++)
	{
	    fseek(fp, 0, SEEK_END); 
		fprintf(fp,"%s",a[i]);
		fprintf(fp,"%c",'\n');
	 } 
	 fclose(fp);
}
int main(void)
{
	 FILE *fp1;  

	int n;	
	long int n1;

	for(n = 2;n < 13; n = n+2)
	{
			if ((fp1 = fopen("F:\\PB14011025-project1\\ex1\\input\\input_strings.txt.txt", "rb")) == NULL)  
	       {  
   	           exit(0);  
	       } 
		n1 = pow(3,n);
		
		long int k = 0;
		while(!feof(fp1) && k < n1)
		{
			fscanf(fp1,"%s",str1[k]);
			k++;
		}
		fclose(fp1);
		sort(str1,n);
	}
	FILE *fp2;
		if ((fp2 = fopen("F:\\PB14011025-project1\\ex1\\output\\merge-sort\\time.txt", "wb")) == NULL) exit(0);
		int k;
		for(k = 0; k<6; k++)
		{
			fseek(fp2, 0, SEEK_END); 
		fprintf(fp2,"%f",t[k]);
		fprintf(fp2,"%c",'\n');
		}
		fclose (fp2);
		
}

