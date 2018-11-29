#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void sort(int X[], int right, int left)
{
     int i, j, x, w;
     i=left; j=right;
     x = X[i];
     while(i <= j){
             while(X[i] < x)
               i++;
             while(x < X[j])
               j--;
             if(i<=j){
                  w=X[i];
                  X[i]=X[j];
                  X[j]=w;
                  i++;
                  j--;
             }
     }
    
    if(left < j)
      sort(X, j, left);
    if(i < right)
      sort(X, right, i);

}

void print(int X[], int n){
     for(int i=0; i<=n-1; i++)
       printf("%d ", X[i]);
     printf("\n");
}

main()
{
     int X[9], n;
     printf("enter N :\n");
     scanf("%d", &n);     
     printf("enter %d data :\n", n);
     for(int i=0; i<n; i++){
       printf("%d> ",i+1);
       scanf("%d", &X[i]);
     }

     printf("Unsorted data : ");
     print(X, n);
     
     sort(X, n-1, 0);
     
     printf("Sorted data   : ");
     print(X, n);
     
     getch();
}
