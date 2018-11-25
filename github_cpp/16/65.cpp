







#include "sort.h"


void shellSort(int a[], int n){
    
    int sortItem;
    
    
    for (int increasement = n / 2; increasement >=1; increasement /= 2) {
        
        
        for (int i = increasement; i < n; i++) {
            sortItem = a[i];
            
            int j;
            for (j = i - increasement; j >= 0 && a[j] > sortItem; j -= increasement) {
                a[j + increasement] = a[j];
            }
            
            a[j + increasement] = sortItem;
        }
    }
}
