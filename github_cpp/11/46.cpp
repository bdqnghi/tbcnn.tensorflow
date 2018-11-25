void heap_sort(int* arr, int len)
{
    heapify(arr, len/2-1, len);
    max_heap(arr, len);
}
void heapify(int* ptr, int now, int last)
{
    if(now >= last/2 || now < 0)  return;
    sub_heapify(ptr, now, last);
    heapify(ptr, now-1, last);
}
void sub_heapify(int* ptr, int now, int last)
{
    if(now*2+2 < last && !(ptr[now] >= ptr[now*2+1] && ptr[now] >= ptr[now*2+2])) {
        int max = (ptr[now*2+1] > ptr[now*2+2]) ? now*2+1 : now*2+2;
        swap(ptr, now, max, 1); 
        if(max < last/2)  sub_heapify(ptr, max, last);
    }
    else if(now*2+1 < last && ptr[now] < ptr[now*2+1]){
        swap(ptr, now, now*2+1, 1);
        if(now*2+1 < last/2)sub_heapify(ptr, now*2+1, last);
    }
}
void max_heap(int* ptr, int len)
{
    if(len <= 1) return;
    swap(ptr, 0, len-1, 2);
    sub_heapify(ptr, 0, len-1);
    max_heap(ptr, len-1);
}
