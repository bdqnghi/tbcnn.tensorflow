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

void shellsort(char a[][17],int m)  
{  
long int n;
n = pow(3,m);
long int gap, i, j,k;
char temp[17];  

LARGE_INTEGER t1,t2,tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);

for(k=0;k<5;k++)  
{
	switch(k){
	
		case 0:gap = 21;break;
		case 1:gap = 15;break;
		case 2:gap = 7;break;
		case 3:gap = 3;break;
		case 4:gap = 1;break;
		default:break;
	}
    for(i=gap;i<n;++i) 
        for(j=i-gap; j>=0&&!cmp(a[j],a[j+gap]); j=j-gap) 
      {   
            strcpy(temp,a[j]);  
            strcpy(a[j],a[j+gap]);  
            strcpy(a[j+gap],temp);  
       }  
}
QueryPerformanceCounter(&t2);
    FILE *fp;  
	switch (m){
		case 2:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\shell-sort\\result_2.txt", "wb")) == NULL) exit(0);
		  t[0] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart; break;
		case 4:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\shell-sort\\result_4.txt", "wb")) == NULL)  exit(0);
		 t[1] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart;  break;
		case 6:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\shell-sort\\result_6.txt", "wb")) == NULL)  exit(0);
		 t[2] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart;  break;
		case 8:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\shell-sort\\result_8.txt", "wb")) == NULL)  exit(0); 
		 t[3] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart; break;
		case 10:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\shell-sort\\result_10.txt", "wb")) == NULL)  exit(0);
		 t[4] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart;  break;
		case 12:if ((fp = fopen("F:\\PB14011025-project1\\ex1\\output\\shell-sort\\result_12.txt", "wb")) == NULL)  exit(0); 
		 t[5] = (t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart; break;
		default:break;
	} 
	
	for(i = 0;i < n; i++)
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
		shellsort(str1,n);
	}
	FILE *fp2;
		if ((fp2 = fopen("F:\\PB14011025-project1\\ex1\\output\\shell-sort\\time.txt", "wb")) == NULL) exit(0);
		int k;
		for(k = 0; k<6; k++)
		{
			fseek(fp2, 0, SEEK_END); 
		fprintf(fp2,"%f",t[k]);
		fprintf(fp2,"%c",'\n');
		}
		fclose (fp2);
		
}
