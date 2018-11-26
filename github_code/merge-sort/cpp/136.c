#include <iostream>

using namespace std;


void merge(long list[], long start, long mid, long end){
    long i = start;
    long j = mid + 1;

    while (j <= end && i <= mid){
        if (list[i] < list[j]){
            i++;
        }
        else{
            long temp = list[j];
            for (long k = j; k > i; k--){
                list[k] = list[k-1];
            }
            list[i] = temp;

            mid++;
            i++;
            j++;
        }
    }
}

void sort (long list[], long start, long end){
    if(start < end){
        long mid = (start + end) / 2;

        sort (list, start, mid);
        sort (list, mid+1, end);

        merge (list, start, mid, end);
    }
}


int main(int argc, const char * argv[]) {

	// Get a large array
    const long size = 100000;

    long* list = new long[size];

	// Fill it up with numbers in reverse order
    for (long i = 0; i < size; i++){
        list[i] = size - i;
    }

    // Sort the array
    sort(list, 0, size-1);


    delete[] list;

    return 0;
}
