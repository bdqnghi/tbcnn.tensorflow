#include <stdio.h>
#define MaxSize 100
typedef int KeyType;        
typedef char ElemType[10];  
typedef struct {
    KeyType key;            
    ElemType data;          
} LineList;                 
void BubbleSort(LineList R[], int n)
{
    int i, j, exchange;
    LineList tmp;

    for (i = 0; i < n - 1; i++) {
        exchange = 0;

        for (j = n - 1; j > i; j--) 
            if (R[j].key < R[j - 1].key) {
                tmp = R[j]; 
                R[j] = R[j - 1];
                R[j - 1] = tmp;
                exchange = 1;
            }

        if (exchange == 0)  
            return;
    }
}

void main()
{
    LineList R[MaxSize];
    KeyType a[] = {75, 87, 68, 92, 88, 61, 77, 96, 80, 72};
    int n = 10, i;

    for (i = 0; i < n; i++)
        R[i].key = a[i];

    printf("����ǰ:");

    for (i = 0; i < n; i++)
        printf("%3d", R[i].key);

    printf("\n");
    BubbleSort(R, n);
    printf("�����:");

    for (i = 0; i < n; i++)
        printf("%3d", R[i].key);

    printf("\n");
}
