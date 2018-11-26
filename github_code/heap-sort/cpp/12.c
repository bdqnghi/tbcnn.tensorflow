#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<string.h>
#include<windows.h>

double t[6];
char str1[531441][17];

int cmp(char a[],char b[])//a<=b return 1 a>b return 0
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

void AdjustDown(char a[][17], long int len, long int root) 
{
    long int parent = root;  
    long int child = 2*root + 1;  

    while(child < len)
    {
        if(child+1 < len && !(cmp(a[child+1] , a[child])))  
            ++child;    
        if(cmp(a[parent],a[child])) 
        {
        	char s[17];
        	strcpy(s,a[child]);
        	strcpy(a[child],a[parent]);
        	strcpy(a[parent],s);
            parent = child;          
            child = 2*parent + 1;
        }
        else
            break;
    }
}

void HeapSort(char a[][17], int n)
{
	long int len;
	len = pow(3,n);
    
    
    LARGE_INTEGER t1,t2,tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);

    for(long int root = len/2-1; root >= 0; --root)  
    {
        AdjustDown(a, len, root);  
    }
    for(long int i = 0; i < len-1; ++i)  
    {
    	char s[17];
    
        	strcpy(s,a[0]);
        	strcpy(a[0],a[len-1-i]);
        	strcpy(a[len-1-i],s); 
        AdjustDown(a,len-1-i,0);    
    }
    QueryPerformanceCounter(&t2);
    FILE *fp;  
	switch (n){
		case 2:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\heap-sort\\result_2.txt", "wb")) == NULL) exit(0);
		  t[0] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart; break;
		case 4:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\heap-sort\\result_4.txt", "wb")) == NULL)  exit(0);
		 t[1] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart;  break;
		case 6:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\heap-sort\\result_6.txt", "wb")) == NULL)  exit(0);
		 t[2] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart;  break;
		case 8:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\heap-sort\\result_8.txt", "wb")) == NULL)  exit(0); 
		 t[3] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart; break;
		case 10:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\heap-sort\\result_10.txt", "wb")) == NULL)  exit(0);
		 t[4] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart;  break;
		case 12:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\heap-sort\\result_12.txt", "wb")) == NULL)  exit(0); 
		 t[5] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart; break;
		default:break;
	} 
	
	for(long int i = 0;i < len; i++)
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
	//	char str1[n1][17];
		long int k = 0;
		while(!feof(fp1) && k < n1)
		{
			fscanf(fp1,"%s",str1[k]);
			k++;
		}
		fclose(fp1);
		HeapSort(str1,n);
	}
	FILE *fp2;
		if ((fp2 = fopen("F:\\PB14011025-project1\\ex1\\output\\heap-sort\\time.txt", "wb")) == NULL) exit(0);
		int k;
		for(k = 0; k<6; k++)
		{
			fseek(fp2, 0, SEEK_END); 
		fprintf(fp2,"%f",t[k]);
		fprintf(fp2,"%c",'\n');
		}
		fclose (fp2);
		
}
