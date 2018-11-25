#include <iostream>

using namespace std;

void show(int arr[], int s){
    cout<<"Sorted Array"<<endl;
    for(int i=0; i<s; i++)
        cout<<arr[i]<<endl;
}


class heapSort{
    int *a;
    int length;

public:
    heapSort(int *arr, int s){
        a=arr;
        length=s;
    }

    void sort()
    {
        buildheap();
        int heapsize, i, temp;
        heapsize = length - 1;
        for( i=heapsize; i >= 0; i--)
        {
            temp = a[0];
            a[0] = a[heapsize];
            a[heapsize] = temp;
            heapsize--;
            satisfyheap(0, heapsize);
        }
    }

    void buildheap()
    {
        int i, heapsize;
        heapsize = length - 1;
        for( i=(length/2); i >= 0; i--)
        {
            satisfyheap(i, heapsize);
        }
    }

    void satisfyheap(int i, int heapsize)
    {
        int l, r, largest, temp;
        l = 2*i;
        r = 2*i + 1;
        if(l <= heapsize && a[l] > a[i])
        {
            largest = l;
        }
        else
        {
            largest = i;
        }
        if( r <= heapsize && a[r] > a[largest])
        {
            largest = r;
        }
        if(largest != i)
        {
            temp = a[i];
            a[i] = a[largest];
            a[largest] = temp;
            satisfyheap(largest, heapsize);
        }
    }
};


void quickSort(int *arr, int left, int right){
    int i = left;
    int j = right;
    int pivot = arr[(left+right)/2];

    while(left<j || i<right)
    {
        while(arr[i]<pivot)
            i++;
        while(arr[j]>pivot)
            j--;

        if(i<=j){
            int t=arr[i];   
            arr[i]=arr[j];
            arr[j]=t;
            i++;
            j--;
        }
        else{
            if(left<j)
                quickSort(arr, left, j);
            if(i<right)
                quickSort(arr,i,right);
            return;
        }
    }
}


void radixSort(int *arr, int n) {
    int m = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > m)
            m = arr[i];

    for (int exp = 1; m / exp > 0; exp *= 10){
        int output[n];
        int i, count[10] = {0};
        for (i = 0; i < n; i++)
            count[(arr[i] / exp) % 10]++;
        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];
        for (i = n - 1; i >= 0; i--)
        {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        for (i = 0; i < n; i++)
            arr[i] = output[i];
    }
}


class mergeSort {
    int *a;
public:
    mergeSort(int *arr) {
        a = arr;
    }

    void sort(int low, int high) {
        int mid;
        if (low < high) {
            mid = (low + high) / 2;
            sort(low, mid);
            sort(mid + 1, high);
            merge(low, high, mid);
        }
        return;
    }

    void merge(int low, int high, int mid) {
        int i, j, k, c[50];
        i = low;
        k = low;
        j = mid + 1;
        while (i <= mid && j <= high) {
            if (a[i] < a[j]) {
                c[k] = a[i];
                k++;
                i++;
            } else {
                c[k] = a[j];
                k++;
                j++;
            }
        }
        while (i <= mid) {
            c[k] = a[i];
            k++;
            i++;
        }
        while (j <= high) {
            c[k] = a[j];
            k++;
            j++;
        }
        for (i = low; i < k; i++) {
            a[i] = c[i];
        }
    }
};

int main(){
    int o, s=0;

    cout<<"Enter No. of Elements : ";cin>>s;
    cout<<"Enter the array"<<endl;

    int *arr=new int[s], *fin=new int[s];
    for(int i=0; i<s; i++) {
        cin >> arr[i];
        fin[i] = arr[i];
    }

    do{
        cout<<"1. Heap Sort"<<endl
            <<"2. Radix Sort"<<endl
            <<"3. Merge Sort"<<endl
            <<"4. Quick Sort"<<endl
            <<"5. Exit"<<endl;
        cin>>o;

        cout<<"Initial Array."<<endl;
        for(int i=0; i<s && o!=5; i++) {
            arr[i] = fin[i];
            cout << arr[i] << endl;
        }

        if (o==1){
            heapSort h(arr, s);
            h.sort();
            show(arr, s);
        }
        else if (o==2){
            radixSort(arr, s);
            show(arr, s);
        }
        else if (o==3){
            mergeSort m(arr);
            m.sort(0, s-1);
            show(arr, s);
        }
        else if (o==4){
            quickSort(arr, 0, s-1);
            show(arr, s);
        }
    }while(o!=5);
}