#include <iostream>
#include <cstdio>
#include <vector>
#include <iostream>
#include <climits>

using namespace std; 

class Heap {
private:
std::vector<int> heap;
int hpsz;
public:

Heap(){
        hpsz=0; 
        heap.push_back(0);  
}

Heap(std::vector<int>& array){
        int n = array.size();
        heap.push_back(100);  
        heap.insert(heap.end(),array.begin(),array.end());  
        hpsz=n; 
        for (int i = n / 2; i > 0; i--) combine(i);
}

void insert(int elmnt) {
        heap.push_back(elmnt);
        hpsz++;
        int i = hpsz, parent = i / 2;
        while ((i > 1) && (heap[parent] < heap[i]))
        {
                iter_swap(heap.begin() + parent, heap.begin() + i);
                i = parent; parent = i / 2;
        }
}


int peek_max(){
        return heap[1];
}

void combine (int i){
        int mp=i,left=2*i,right=(2*i)+1;
        if((left<=hpsz) && (heap[left]>heap[mp])) {
                mp = left;
        }
        if((right<=hpsz) && (heap[right]>heap[mp])) {
                mp = right;
        }
        if(mp!=i) {
                iter_swap(heap.begin() + i, heap.begin() + mp);
                combine(mp);
        }
}

int deletemax(){
        if(isEmpty()) return -1;
        int max = heap[1];

        heap[1] = heap[hpsz--];
        combine(1);
        return max;
}

bool isEmpty(){
        return (hpsz==0);
}

int getHeapSize(){
        return (hpsz);
}

void heapSort(){
        int temp = hpsz;
        for (int i = hpsz; i > 1; i--)  {
                iter_swap(heap.begin() + 1, heap.begin() + i);
                hpsz--;
                combine(1);
        }
        hpsz = temp;
}

void printHeap(){
        for (int i = 1; i <= hpsz; i++) {
                printf("%d ", heap[i] );
        }
        printf("\n");
}
};

int main(){
        
        int a[] = {3,4,10,8,15,16,17,12,11,20};
        vector<int> heapin (a, a + sizeof(a) / sizeof(a[0]) ); 
        
        
        Heap test(heapin);
        

        test.printHeap(); 
        test.heapSort();  
        test.printHeap(); 

        



}
