#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<windows.h>

double t[6];
int num[1594323];
int L[1594323];
int R[1594323];

void Merge(int a[], long int p, long int q, long int r)   
{
	long int n1,n2,i,j,k;
	n1 = q-p+1;
	n2 = r-q;
	
	for(i = 0;i <n1;i++)
	L[i]=a[p+i];
	for(j = 0;j <n2;j++)
	R[j]=a[q+j+1];
	L[n1] = 65535;
	R[n2] = 65535;
	i =0; j= 0;
	for(k = p;k<=r;k++)
	{
		if(L[i]<=R[j])
		{
			a[k] = L[i];
			i++;
		}
		else
		{
			a[k] = R[j];
			j++;
		}
		
	}
	
	
	
	
}

void MergeSort(int a[], long int p, long int r)   
{
	
    if(r - p< 1)
        return ;

    long int q;
    q = p + (r - p)/2;
    MergeSort(a,p,q);
    MergeSort(a,q+1,r);
    Merge(a,p,q,r);
}

void sort(int a[],int m)
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
	
		case 3:if ((fp = fopen("F:\\PB14011025-project1\\ex2\\output\\merge-sort\\result_3.txt", "wb")) == NULL) exit(0);
		  t[0] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart; break;
		case 5:if ((fp = fopen("F:\\PB14011025-project1\\ex2\\output\\merge-sort\\result_5.txt", "wb")) == NULL)  exit(0);
		 t[1] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart;  break;
		case 7:if ((fp = fopen("F:\\PB14011025-project1\\ex2\\output\\merge-sort\\result_7.txt", "wb")) == NULL)  exit(0);
		 t[2] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart;  break;
		case 9:if ((fp = fopen("F:\\PB14011025-project1\\ex2\\output\\merge-sort\\result_9.txt", "wb")) == NULL)  exit(0); 
		 t[3] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart; break;
		case 11:if ((fp = fopen("F:\\PB14011025-project1\\ex2\\output\\merge-sort\\result_11.txt", "wb")) == NULL)  exit(0);
		 t[4] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart;  break;
		case 13:if ((fp = fopen("F:\\PB14011025-project1\\ex2\\output\\merge-sort\\result_13.txt", "wb")) == NULL)  exit(0); 
		 t[5] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart; break;
		default:break;
	} 
	long int i;
	for(i = 0;i < n; i++)
	{
	    fseek(fp, 0, SEEK_END); 
		fprintf(fp,"%d\n",a[i]);
	 } 
	 fclose(fp);
}
int main(void)
{
	 FILE *fp1;  

	int n;	
	long int n1;

	for(n =3;n<14; n=n+2)
	{
		
			if ((fp1 = fopen("F:\\PB14011025-project1\\ex2\\input\\input_strings.txt", "rb")) == NULL)  
	       {  
   	           exit(0);  
	       } 
		n1 = pow(3,n);
		
		long int k = 0;
		while(!feof(fp1) && k < n1)
		{
			fscanf(fp1,"%d",&num[k]);
			
			k++;
		}
		fclose(fp1);
		sort(num,n);
	}
	FILE *fp2;
		if ((fp2 = fopen("F:\\PB14011025-project1\\ex2\\output\\merge-sort\\time.txt", "wb")) == NULL) exit(0);
		int k;
		for(k = 0; k<6; k++)
		{
			fseek(fp2, 0, SEEK_END); 
		fprintf(fp2,"%f",t[k]);
		fprintf(fp2,"%c",'\n');
		}
		fclose (fp2);
		
}
