#include<stdio.h>
#include<stdlib.h>
#include<math.h>

long cx = 0; 

void shellSort(int A[], int n)
{
    int gap,i;

    for (gap = n/2; gap > 0; gap /= 2)
    {
        for (i = gap; i < n; i += 1) { 
            int temp = A[i]; 
            int j; 
            for (j = i; j >= gap && A[j - gap] > temp; j -= gap)
            {
                A[j] = A[j - gap];
                cx++;
            }
            A[j] = temp;
        }
    }
}
 
void print_array(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d\n", A[i]);
}
 
void merge_sort(int *a,int len_a,int *b,int len_b)
{
     if (len_a > 1)
     {
               int mid_a = len_a >> 1;
               merge_sort(a,mid_a,a+mid_a,len_a-mid_a);
     }
     
     if (len_b > 1)
     {
               int mid_b = len_b >> 1;
               merge_sort(b,mid_b,b+mid_b,len_b-mid_b);
     }
     
     int curr_a=0, curr_b=0, *temp_arr, tmp, k=0;
     
     temp_arr = (int*)malloc((len_a+len_b)*sizeof(int));
     
     while (curr_a < len_a && curr_b < len_b)
     {
           if (a[curr_a] <= b[curr_b])
           {
               temp_arr[k]=a[curr_a];
               curr_a++;
           }
           else
           {
               temp_arr[k]=b[curr_b];
               curr_b++;
           }
           k++;
           cx++;
     }

    while (curr_a < len_a)
     {
           temp_arr[k] = a[curr_a];
           curr_a++;
           k++;
           cx++;
     }
     
     while (curr_b < len_b)
     {
           temp_arr[k] = b[curr_b];
           curr_b++;
           k++;
           cx++;
     }
     
     for (int k=0;k<len_a+len_b;k++)
     {
              a[k] = temp_arr[k];
     }
     free(temp_arr);

}
 
 
#define C 65535
int main(int argc, char **argv)
{
    int p[C];
    int n = sizeof(p)/sizeof(p[0]);
    
    srand(rand());
    for(int a=0;a<C;a++)
    {

            p[a] = rand();
    }    
 




    cx = 0;
    merge_sort(p,1,p+1,C-1);

 


    printf("\nTotal steps: %d\n", cx);
    system("pause");
    return 0;
}
