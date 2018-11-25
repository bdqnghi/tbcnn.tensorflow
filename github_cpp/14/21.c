
 
void countSort(int* arr, int n, int exp) {
    int output[n]; 
    int i, count[10] = {0};
 
    
    for (i = 0; i < n; i++)
        count[ (arr[i] / exp) % 10 ]++;
 
    
    
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    
    int indx;
    for (i = n - 1; i >= 0; i--) {
        indx = (arr[i] / exp) % 10;
        output[count[indx] - 1] = arr[i];
        count[indx]--;
    }
 
    
    
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
 

void radixsort(int* arr, int n) {
    
    int m = *max_element(arr, arr + n);
 
    
    
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}